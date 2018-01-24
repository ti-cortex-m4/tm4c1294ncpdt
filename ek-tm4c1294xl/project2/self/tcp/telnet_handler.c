/*------------------------------------------------------------------------------
telnet_handler.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/sys.h"
#include "../uart/serial.h"
#include "../uart/serial_send.h"
#include "../uart/serial_receive.h"
#include "../uart/io_mode.h"
#include "../uart/customer_settings_1.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "telnet.h"
#include "telnet_handler.h"



//*****************************************************************************
//
//! Processes a character received from the telnet port.
//!
//! \param ucChar is the character in question.
//! \param pState is the telnet state data for this connection.
//!
//! This function processes a character received from the telnet port, handling
//! the interpretation of telnet commands (as indicated by the telnet interpret
//! as command (IAC) byte).
//!
//! \return None.
//
//*****************************************************************************
static void TelnetProcessCharacter(uint8_t ucChar, tState *pState)
{
    pState->ulConnectionTimeout = 0;

    OutMode(pState->ucSerialPort);
    SerialSend(pState->ucSerialPort, ucChar);
}



//*****************************************************************************
//! Handles periodic task for telnet sessions.
//!
//! This function is called periodically from the lwIP timer thread context.
//! This function will handle transferring data between the UART and the
//! the telnet sockets.  The time period for this should be tuned to the UART
//! ring buffer sizes to maintain optimal throughput.
//!
//! \return None.
//*****************************************************************************
void TelnetHandler(void)
{
    static uint8_t pucTemp[PBUF_POOL_BUFSIZE];
    SYS_ARCH_DECL_PROTECT(lev);

    uint8_t u;
    for(u = 0; u < UART_COUNT; u++)
    {
        // Initialize the state pointer.
        tState *pState = &g_sState[u];

        // If the telnet session is not connected, skip this port.
        if(pState->eTCPState != STATE_TCP_CONNECTED)
        {
            continue;
        }

#if defined(CONFIG_RFC2217_ENABLED)
        // Check to see if modem state options have changed.
        if(pState->ucLastModemState != pState->ucModemState)
        {
            // Save the current state for the next comparison.
            pState->ucLastModemState = pState->ucModemState;

            // Check to see if the modem state options have been negotiated,
            // and if they have changed.
            if((HWREGBITB(&pState->ucFlags, OPT_FLAG_WILL_RFC2217) == 1) &&
               (HWREGBITB(&pState->ucFlags, OPT_FLAG_DO_RFC2217) == 1))
            {
                // Check to see if the state change has been enabled.
                if(pState->ucModemState & pState->ucRFC2217ModemMask)
                {
                    lIndex = 0;
                    pucTemp[lIndex++] = TELNET_IAC;
                    pucTemp[lIndex++] = TELNET_SB;
                    pucTemp[lIndex++] = TELNET_OPT_RFC2217;

                    // Use the "Server to Client" notification value.
                    pucTemp[lIndex++] = (TELNET_C2S_NOTIFY_MODEMSTATE + 100);

                    pucTemp[lIndex++] = (pState->ucModemState &
                            pState->ucRFC2217ModemMask);
                    if((pState->ucModemState & pState->ucRFC2217ModemMask) ==
                            TELNET_IAC)
                    {
                        pucTemp[lIndex++] = TELNET_IAC;
                    }
                    pucTemp[lIndex++] = TELNET_IAC;
                    pucTemp[lIndex++] = TELNET_SE;

                    // Write the data.
                    tcp_write(pState->pConnectPCB, pucTemp, lIndex, 1);
                    tcp_output(pState->pConnectPCB);

                    // Reset the index.
                    lIndex = 0;
                }
            }
        }
#endif

        // While space is available in the serial output queue, process the
        // pbufs received on the telnet interface.
        while(!SerialSendFull(u))
        {
            // Pop a pbuf off of the RX queue, if one is available, and we are
            // not already processing a pbuf.
            if(pState->pBufHead == NULL)
            {
                if(pState->iBufQRead != pState->iBufQWrite)
                {
                    SYS_ARCH_PROTECT(lev);
                    pState->pBufHead = pState->pBufQ[pState->iBufQRead];
                    pState->iBufQRead = ((pState->iBufQRead + 1) % PBUF_POOL_SIZE);
                    pState->pBufCurrent = pState->pBufHead;
                    pState->ulBufIndex = 0;

                    mcwUARTTxOut[u] += pState->pBufCurrent->len;
                    SYS_ARCH_UNPROTECT(lev);
                }
            }

            // If there is no packet to be processed, break out of the loop.
            if(pState->pBufHead == NULL)
            {
                break;
            }

            CustomerSettings1_TelnetProcessCharacter(u);

            // Setup the data pointer for the current buffer.
            uint8_t *pucData = pState->pBufCurrent->payload;

            // Process the next character in the buffer.
            TelnetProcessCharacter(pucData[pState->ulBufIndex], pState);

            // Increment to next data byte.
            pState->ulBufIndex++;

            // Check to see if we are at the end of the current buffer.  If so,
            // get the next pbuf in the chain.
            if(pState->ulBufIndex >= pState->pBufCurrent->len)
            {
                pState->pBufCurrent = pState->pBufCurrent->next;
                pState->ulBufIndex = 0;
            }

            // Check to see if we are at the end of the chain.  If so,
            // acknowledge this data as being consumed to open up the TCP
            // window.
            if((pState->pBufCurrent == NULL) && (pState->ulBufIndex == 0))
            {
                tcp_recved(pState->pConnectPCB, pState->pBufHead->tot_len);
                pbuf_free(pState->pBufHead);
                pState->pBufHead = NULL;
                pState->pBufCurrent = NULL;
                pState->ulBufIndex = 0;
            }
        }

        // Flush the TCP output buffer, in the event that data was
        // queued up by processing the incoming packet.
        tcp_output(pState->pConnectPCB);

        // If RFC2217 is enabled, and flow control has been set to suspended,
        // skip processing of this port.
#if CONFIG_RFC2217_ENABLED
        if(pState->ucRFC2217FlowControl == TELNET_C2S_FLOWCONTROL_SUSPEND)
        {
            continue;
        }
#endif

        // Process the RX ring buffer data if space is available in the
        // TCP output buffer.
        if(SerialReceiveAvailable(pState->ucSerialPort) &&
           tcp_sndbuf(pState->pConnectPCB) &&
           (pState->pConnectPCB->snd_queuelen < TCP_SND_QUEUELEN))
        {
            // Here, we have data, and we have space.  Set the total amount
            // of data we will process to the lesser of data available or
            // space available.
            long lCount = (long)SerialReceiveAvailable(pState->ucSerialPort);
            if(tcp_sndbuf(pState->pConnectPCB) < lCount)
            {
                lCount = tcp_sndbuf(pState->pConnectPCB);
            }

            // While we have data remaining to process, continue in this loop.
            while((lCount) &&
                  (pState->pConnectPCB->snd_queuelen < TCP_SND_QUEUELEN))
            {
                // First, reset the index into the local buffer.
                long lIndex = 0;

                // Fill the local buffer with data while there is data
                // and/or space remaining.
                while(lCount && (lIndex < sizeof(pucTemp)))
                {
                    uint8_t ucChar = SerialReceive(pState->ucSerialPort);

                    if (fDataDebugFlag)
                      CONSOLE("%u: to TCP %02X\n", u, ucChar);

                    pucTemp[lIndex] = ucChar;
                    lIndex++;
                    lCount--;
                }

                // Write the local buffer into the TCP buffer.
                tcp_write(pState->pConnectPCB, pucTemp, lIndex, 1);
            }

            // https://en.wikipedia.org/wiki/Nagle%27s_algorithm#Interactions_with_real-time_systems
            tcp_nagle_disable(pState->pConnectPCB);

            // Flush the data that has been written into the TCP output buffer.
            tcp_output(pState->pConnectPCB);
            pState->ulLastTCPSendTime = g_ulSystemTimeMS;
        }
    }
}
