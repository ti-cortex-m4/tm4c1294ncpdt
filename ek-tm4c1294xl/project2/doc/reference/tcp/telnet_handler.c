#if 0
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
//*****************************************************************************
static void
TelnetProcessCharacter(uint8_t ucChar, tTelnetSessionData *pState)
{
    uint8_t pucBuf[9];

    if((g_sParameters.sPort[pState->ulSerialPort].ucFlags &
                PORT_FLAG_PROTOCOL) == PORT_PROTOCOL_RAW)
    {
        // Write this character to the UART with no telnet processing.
        SerialSend(pState->ulSerialPort, ucChar);

        // And return.
        return;
    }

    // Determine the current state of the telnet command parser.
    switch(pState->eTelnetState)
    {
        // The normal state of the parser, were each character is either sent
        // to the UART or is a telnet IAC character.
        case STATE_NORMAL:
        {
            // See if this character is the IAC character.
            if(ucChar == TELNET_IAC)
            {
                // Skip this character and go to the IAC state.
                pState->eTelnetState = STATE_IAC;
            }
            else
            {
                // Write this character to the UART.
                SerialSend(pState->ulSerialPort, ucChar);
            }

            // This state has been handled.
            break;
        }

        // The previous character was the IAC character.
        case STATE_IAC:
        {
            // Determine how to interpret this character.
            switch(ucChar)
            {
                // See if this character is also an IAC character.
                case TELNET_IAC:
                {
                    // Send 0xff to the UART.
                    SerialSend(pState->ulSerialPort, ucChar);

                    // Switch back to normal mode.
                    pState->eTelnetState = STATE_NORMAL;

                    // This character has been handled.
                    break;
                }

                // See if this character is the WILL request.
                case TELNET_WILL:
                {
                    // Switch to the WILL mode; the next character will have
                    // the option in question.
                    pState->eTelnetState = STATE_WILL;

                    // This character has been handled.
                    break;
                }

                // See if this character is the WONT request.
                case TELNET_WONT:
                {
                    // Switch to the WONT mode; the next character will have
                    // the option in question.
                    pState->eTelnetState = STATE_WONT;

                    // This character has been handled.
                    break;
                }

                // See if this character is the DO request.
                case TELNET_DO:
                {
                    // Switch to the DO mode; the next character will have the
                    // option in question.
                    pState->eTelnetState = STATE_DO;

                    // This character has been handled.
                    break;
                }

                // See if this character is the DONT request.
                case TELNET_DONT:
                {
                    // Switch to the DONT mode; the next character will have
                    // the option in question.
                    pState->eTelnetState = STATE_DONT;

                    // This character has been handled.
                    break;
                }

                // See if this character is the AYT request.
                case TELNET_AYT:
                {
                    // Send a short string back to the client so that it knows
                    // that we're still alive.
                    pucBuf[0] = '\r';
                    pucBuf[1] = '\n';
                    pucBuf[2] = '[';
                    pucBuf[3] = 'Y';
                    pucBuf[4] = 'e';
                    pucBuf[5] = 's';
                    pucBuf[6] = ']';
                    pucBuf[7] = '\r';
                    pucBuf[8] = '\n';
                    tcp_write(pState->pConnectPCB, pucBuf, 9, 1);

                    // Switch back to normal mode.
                    pState->eTelnetState = STATE_NORMAL;

                    // This character has been handled.
                    break;
                }

                // See if this is the SB request.
#if CONFIG_RFC2217_ENABLED
                case TELNET_SB:
                {
                    // Switch to SB processing mode.
                    pState->eTelnetState = STATE_SB;

                    // This character has been handled.
                    break;
                }
#endif

                // Explicitly ignore the GA and NOP request, plus provide a
                // catch-all ignore for unrecognized requests.
                case TELNET_GA:
                case TELNET_NOP:
                default:
                {
                    // Switch back to normal mode.
                    pState->eTelnetState = STATE_NORMAL;

                    // This character has been handled.
                    break;
                }
            }

            // This state has been handled.
            break;
        }

        // The previous character sequence was IAC WILL.
        case STATE_WILL:
        {
            // Process the WILL request on this option.
            TelnetProcessWill(ucChar, pState);

            // Switch back to normal mode.
            pState->eTelnetState = STATE_NORMAL;

            // This state has been handled.
            break;
        }

        // The previous character sequence was IAC WONT.
        case STATE_WONT:
        {
            // Process the WONT request on this option.
            TelnetProcessWont(ucChar, pState);

            // Switch back to normal mode.
            pState->eTelnetState = STATE_NORMAL;

            // This state has been handled.
            break;
        }

        // The previous character sequence was IAC DO.
        case STATE_DO:
        {
            // Process the DO request on this option.
            TelnetProcessDo(ucChar, pState);

            // Switch back to normal mode.
            pState->eTelnetState = STATE_NORMAL;

            // This state has been handled.
            break;
        }

        // The previous character sequence was IAC DONT.
        case STATE_DONT:
        {
            // Process the DONT request on this option.
            TelnetProcessDont(ucChar, pState);

            // Switch back to normal mode.
            pState->eTelnetState = STATE_NORMAL;

            // This state has been handled.
            break;
        }

        // The previous character sequence was IAC SB.
        case STATE_SB:
        {
            // If the SB request is COM_PORT request (in other words, RFC
            // 2217).
#if CONFIG_RFC2217_ENABLED
            if((ucChar == TELNET_OPT_RFC2217) &&
               (HWREGBITB(&pState->ucFlags, OPT_FLAG_WILL_RFC2217) == 1) &&
               (HWREGBITB(&pState->ucFlags, OPT_FLAG_DO_RFC2217) == 1))
            {
                // Initialize the COM PORT option state machine.
                pState->eRFC2217State = STATE_2217_GET_COMMAND;

                // Change state to COM PORT option processing state.
                pState->eTelnetState = STATE_SB_RFC2217;
            }
            else
#endif
            {
                // Ignore this SB option.
                pState->eTelnetState = STATE_SB_IGNORE;
            }

            // This state has been handled.
            break;
        }

        // In the middle of an unsupported IAC SB sequence.
        case STATE_SB_IGNORE:
        {
            // Check for the IAC character.
            if(ucChar == TELNET_IAC)
            {
                // Change state to look for Telnet SE character.
                pState->eTelnetState = STATE_SB_IGNORE_IAC;
            }

            // This state has been handled.
            break;
        }

        // In the middle of a an RFC 2217 sequence.
#if CONFIG_RFC2217_ENABLED
        case STATE_SB_RFC2217:
        {
            // Allow the 2217 processor to handle this character.
            TelnetProcessRFC2217Character(ucChar, pState);

            // This state has been handled.
            break;
        }
#endif

        // Checking for the terminating IAC SE in unsupported IAC SB sequence.
        case STATE_SB_IGNORE_IAC:
        {
            // Check for the IAC character.
            if(ucChar == TELNET_SE)
            {
                // IAC SB sequence is terminated.  Revert to normal telnet
                // character processing.
                pState->eTelnetState = STATE_NORMAL;
            }
            else
            {
                // Go back to looking for the IAC SE sequence.
                pState->eTelnetState = STATE_SB_IGNORE;
            }

            // This state has been handled.
            break;
        }

        // A catch-all for unknown states.  This should never be reached, but
        // is provided just in case it is ever needed.
        default:
        {
            // Switch back to normal mode.
            pState->eTelnetState = STATE_NORMAL;

            // This state has been handled.
            break;
        }
    }
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
void
TelnetHandler(void)
{
    long lCount, lIndex;
    static uint8_t pucTemp[PBUF_POOL_BUFSIZE];
    int iLoop;
    SYS_ARCH_DECL_PROTECT(lev);
    uint8_t *pucData;
    tTelnetSessionData *pState;

    // Loop through the possible telnet sessions.
    for(iLoop = 0; iLoop < MAX_S2E_PORTS; iLoop++)
    {
        // Initialize the state pointer.
        pState = &g_sTelnetSession[iLoop];

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
        while(!SerialSendFull(iLoop))
        {
            // Pop a pbuf off of the rx queue, if one is available, and we are
            // not already processing a pbuf.
            if(pState->pBufHead == NULL)
            {
                if(pState->iBufQRead != pState->iBufQWrite)
                {
                    SYS_ARCH_PROTECT(lev);
                    pState->pBufHead = pState->pBufQ[pState->iBufQRead];
                    pState->iBufQRead =
                        ((pState->iBufQRead + 1) % PBUF_POOL_SIZE);
                    pState->pBufCurrent = pState->pBufHead;
                    pState->ulBufIndex = 0;
                    SYS_ARCH_UNPROTECT(lev);
                }
            }

            // If there is no packet to be processed, break out of the loop.
            if(pState->pBufHead == NULL)
            {
                break;
            }

            // Setup the data pointer for the current buffer.
            pucData = pState->pBufCurrent->payload;

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
        if(SerialReceiveAvailable(pState->ulSerialPort) &&
           tcp_sndbuf(pState->pConnectPCB) &&
           (pState->pConnectPCB->snd_queuelen < TCP_SND_QUEUELEN))
        {
            // Here, we have data, and we have space.  Set the total amount
            // of data we will process to the lesser of data available or
            // space available.
            lCount = (long)SerialReceiveAvailable(pState->ulSerialPort);
            if(tcp_sndbuf(pState->pConnectPCB) < lCount)
            {
                lCount = tcp_sndbuf(pState->pConnectPCB);
            }

            // While we have data remaining to process, continue in this
            // loop.
            while((lCount) &&
                  (pState->pConnectPCB->snd_queuelen < TCP_SND_QUEUELEN))
            {
                // First, reset the index into the local buffer.
                lIndex = 0;

                // Fill the local buffer with data while there is data
                // and/or space remaining.
                while(lCount && (lIndex < sizeof(pucTemp)))
                {
                    pucTemp[lIndex] = SerialReceive(pState->ulSerialPort);
                    lIndex++;
                    lCount--;
                }

                // Write the local buffer into the TCP buffer.
                tcp_write(pState->pConnectPCB, pucTemp, lIndex, 1);
            }

            // Flush the data that has been written into the TCP output
            // buffer.
            tcp_output(pState->pConnectPCB);
            pState->ulLastTCPSendTime = g_ulSystemTimeMS;
        }
    }
}

#endif
