/*------------------------------------------------------------------------------
TCP_CLIENT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/tcp_impl.h"
#include "../state.h"
#include "../uart/log.h"
#include "tcp_client.h"



err_t TCPClientInit(void)
{
  return ERR_OK;
}



static void TCPClientError(void *arg, err_t err)
{
  tState *pState = arg;

  LOG(("TCPClientError 0x%08x, %d\n", arg, err));

  // Increment our error counter.
  pState->ucErrorCount++;
  pState->eLastErr = err;

//    //
//    // Free the pbufs associated with this session.
//    //
//    TelnetFreePbufs(pState);
//
//    //
//    // Reset the session data for this port.
//    //
//    if(pState->pListenPCB == NULL)
//    {
//        //
//        // Attempt to reestablish the telnet connection to the server.
//        //
//        TelnetOpen(pState->ulTelnetRemoteIP, pState->usTelnetRemotePort,
//                   pState->usTelnetLocalPort, pState->ulSerialPort);
//    }
//    else
//    {
//        //
//        // Reinitialize the server state to wait for incoming connections.
//        //
//        pState->pConnectPCB = NULL;
//        pState->eTCPState = STATE_TCP_LISTEN;
//        pState->eTelnetState = STATE_NORMAL;
//        pState->ucFlags = ((1 << OPT_FLAG_WILL_SUPPRESS_GA) |
//                           (1 << OPT_FLAG_SERVER));
//        pState->ulConnectionTimeout = 0;
//        pState->iBufQRead = 0;
//        pState->iBufQWrite = 0;
//        pState->pBufHead = NULL;
//        pState->pBufCurrent = NULL;
//        pState->ulBufIndex = 0;
//        pState->ulLastTCPSendTime = 0;
//#if CONFIG_RFC2217_ENABLED
//        pState->ucFlags |= (1 << OPT_FLAG_WILL_RFC2217);
//        pState->ucRFC2217FlowControl =
//            TELNET_C2S_FLOWCONTROL_RESUME;
//        pState->ucRFC2217ModemMask = 0;
//        pState->ucRFC2217LineMask = 0xff;
//        pState->ucLastModemState = 0;
//        pState->ucModemState = 0;
//#endif
//        pState->bLinkLost = false;
//    }
}


static err_t TCPClientPoll(void *arg, struct tcp_pcb *pcb)
{
//    err_t eError;
//    struct ip_addr sIPAddr;
  tState *pState = arg;

  LOG(("TCPClientPoll 0x%08x, 0x%08x\n", arg, pcb));

//    //
//    // Are we operating as a server or a client?
//    //
//    if(!pState->pListenPCB)
//    {
//        //
//        // We are operating as a client.  Are we currently trying to reconnect
//        // to the server?
//        //
//        if(pState->eTCPState == STATE_TCP_CONNECTING)
//        {
//            //
//            // We are trying to reconnect but can't have received the connection
//            // callback in the last 3 seconds so we try connecting again.
//            //
//            pState->ucReconnectCount++;
//            sIPAddr.addr = htonl(pState->ulTelnetRemoteIP);
//            eError = tcp_connect(pcb, &sIPAddr, pState->usTelnetRemotePort,
//                                 TelnetConnected);
//
//            if(eError != ERR_OK)
//            {
//                //
//                // Remember the error for later.
//                //
//                pState->eLastErr = eError;
//            }
//        }
//    }
//    else
//    {
//        //
//        // We are operating as a server. Increment the timeout value and close
//        // the telnet connection if the configured timeout has been exceeded.
//        //
//        pState->ulConnectionTimeout++;
//        if((pState->ulMaxTimeout != 0) &&
//           (pState->ulConnectionTimeout > pState->ulMaxTimeout))
//        {
//            //
//            // Close the telnet connection.
//            //
//            tcp_abort(pcb);
//        }
//    }

  return ERR_OK;
}


static err_t TCPClientReceive(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
  tState *pState = arg;
//    int iNextWrite;
//    SYS_ARCH_DECL_PROTECT(lev);

  LOG(("TCPClientReceive 0x%08x, 0x%08x, 0x%08x, %d\n", arg, pcb, p, err));

//    //
//    // Place the incoming packet onto the queue if there is space.
//    //
//    if((err == ERR_OK) && (p != NULL))
//    {
//        //
//        // This should be done in a protected/critical section.
//        //
//        SYS_ARCH_PROTECT(lev);
//
//        //
//        // Do we have space in the queue?
//        //
//        iNextWrite = ((pState->iBufQWrite + 1) % PBUF_POOL_SIZE);
//        if(iNextWrite == pState->iBufQRead)
//        {
//            //
//            // The queue is full - discard the pbuf and return since we can't
//            // handle it just now.
//            //
//
//            //
//            // Restore previous level of protection.
//            //
//            SYS_ARCH_UNPROTECT(lev);
//
//            //
//            // Free up the pbuf.  Note that we don't acknowledge receipt of
//            // the data since we want it to be retransmitted later.
//            //
//            pbuf_free(p);
//        }
//        else
//        {
//            //
//            // Place the pbuf in the circular queue.
//            //
//            pState->pBufQ[pState->iBufQWrite] = p;
//
//            //
//            // Increment the queue write index.
//            //
//            pState->iBufQWrite = iNextWrite;
//
//            //
//            // Restore previous level of protection.
//            //
//            SYS_ARCH_UNPROTECT(lev);
//        }
//    }
//
//    //
//    // If a null packet is passed in, close the connection.
//    //
//    else if((err == ERR_OK) && (p == NULL))
//    {
//        //
//        // Clear out all of the TCP callbacks.
//        //
//        tcp_arg(pcb, NULL);
//        tcp_sent(pcb, NULL);
//        tcp_recv(pcb, NULL);
//        tcp_err(pcb, NULL);
//        tcp_poll(pcb, NULL, 1);
//
//        //
//        // Close the TCP connection.
//        //
//        tcp_close(pcb);
//
//        //
//        // Clear out any pbufs associated with this session.
//        //
//        TelnetFreePbufs(pState);
//
//        //
//        // Clear out the telnet session PCB.
//        //
//        pState->pConnectPCB = NULL;
//
//        //
//        // If we don't have a listen PCB, then we are in client mode, and
//        // should try to reconnect.
//        //
//        if(pState->pListenPCB == NULL)
//        {
//            //
//            // Re-open the connection.
//            //
//            TelnetOpen(pState->ulTelnetRemoteIP, pState->usTelnetRemotePort,
//                       pState->usTelnetLocalPort, pState->ulSerialPort);
//        }
//        else
//        {
//            //
//            // Revert to listening state.
//            //
//            pState->eTCPState = STATE_TCP_LISTEN;
//        }
//    }

  return ERR_OK;
}


static err_t TCPClientSent(void *arg, struct tcp_pcb *pcb, u16_t len)
{
  tState *pState = arg;

  LOG(("TCPClientSent 0x%08x, 0x%08x, %d\n", arg, pcb, len));

  // Reset the connection timeout.
  pState->ulConnectionTimeout = 0;

  return ERR_OK;
}


static err_t TCPClientConnected(void *arg, struct tcp_pcb *pcb, err_t err)
{
  tState *pState = arg;

  LOG(("TCPClientConnected 0x%08x, 0x%08x, %d\n", arg, pcb, err));

  // Increment our connection counter.
  pState->ucConnectCount++;

//    //
//    // If we are not in the listening state, refuse this connection.
//    //
//    if(pState->eTCPState != STATE_TCP_CONNECTING)
//    {
//        //
//        // If we already have a connection, kill it and start over.
//        //
//        return(ERR_CONN);
//    }
//
//    if(err != ERR_OK)
//    {
//        //
//        // Remember the error that is being reported.
//        //
//        pState->eLastErr = err;
//
//        //
//        // Clear out all of the TCP callbacks.
//        //
//        tcp_arg(pcb, NULL);
//        tcp_sent(pcb, NULL);
//        tcp_recv(pcb, NULL);
//        tcp_err(pcb, NULL);
//        tcp_poll(pcb, NULL, 1);
//
//        //
//        // Close the TCP connection.
//        //
//        tcp_close(pcb);
//
//        //
//        // Clear out any pbufs associated with this session.
//        //
//        TelnetFreePbufs(pState);
//
//        //
//        // Re-open the connection.
//        //
//        TelnetOpen(pState->ulTelnetRemoteIP, pState->usTelnetRemotePort,
//                   pState->usTelnetLocalPort, pState->ulSerialPort);
//
//        //
//        // And return.
//        //
//        return(ERR_OK);
//    }

    // Save the PCB for future reference.
    pState->pConnectPCB = pcb;

    // Change TCP state to connected.
    pState->eTCPState = STATE_TCP_CONNECTED;

//    //
//    // Reset the serial port associated with this session to its default
//    // parameters.
//    //
//    SerialSetDefault(pState->ulSerialPort);

    // Set the connection timeout to 0.
    pState->ulConnectionTimeout = 0;
//
//    //
//    // Setup the TCP connection priority.
//    //
//    tcp_setprio(pcb, TCP_PRIO_MIN);

  // Setup the TCP receive function.
  tcp_recv(pcb, TCPClientReceive);

  // Setup the TCP error function.
  tcp_err(pcb, TCPClientError);

  // Setup the TCP polling function/interval.
  tcp_poll(pcb, TCPClientPoll, (1000 / TCP_SLOW_INTERVAL));

  // Setup the TCP sent callback function.
  tcp_sent(pcb, TCPClientSent);

  return ERR_OK;
}


err_t TCPClientConnect(ulong dwRemoteIP, uint wRemotePort)
{
  tState *pState = GetState(0);

  void *pcb = tcp_new();

  // Save the requested information and set the TCP callback functions and arguments.
  tcp_arg(pcb, pState);

  // Set the TCP error callback.
  tcp_err(pcb, TCPClientError);

  // Set the callback that will be made after 3 seconds.  This allows us to reattempt the connection if we do not receive a response.
  tcp_poll(pcb, TCPClientPoll, (3000 / TCP_SLOW_INTERVAL));

  struct ip_addr sIPAddr;
  sIPAddr.addr = htonl(dwRemoteIP);

  err_t eErr = tcp_connect(pcb, &sIPAddr, wRemotePort, TCPClientConnected);
  if (eErr != ERR_OK)
  {
    pState->eLastErr = eErr;
  }

  return eErr;
}


#if false
//*****************************************************************************
//
//! Handles periodic task for telnet sessions.
//!
//! This function is called periodically from the lwIP timer thread context.
//! This function will handle transferring data between the UART and the
//! the telnet sockets.  The time period for this should be tuned to the UART
//! ring buffer sizes to maintain optimal throughput.
//!
//! \return None.
//
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

    //
    // Loop through the possible telnet sessions.
    //
    for(iLoop = 0; iLoop < MAX_S2E_PORTS; iLoop++)
    {
        //
        // Initialize the state pointer.
        //
        pState = &g_sTelnetSession[iLoop];

        //
        // If the telnet session is not connected, skip this port.
        //
        if(pState->eTCPState != STATE_TCP_CONNECTED)
        {
            continue;
        }

#if defined(CONFIG_RFC2217_ENABLED)
        //
        // Check to see if modem state options have changed.
        //
        if(pState->ucLastModemState != pState->ucModemState)
        {
            //
            // Save the current state for the next comparison.
            //
            pState->ucLastModemState = pState->ucModemState;

            //
            // Check to see if the modem state options have been negotiated,
            // and if they have changed.
            //
            if((HWREGBITB(&pState->ucFlags, OPT_FLAG_WILL_RFC2217) == 1) &&
               (HWREGBITB(&pState->ucFlags, OPT_FLAG_DO_RFC2217) == 1))
            {
                //
                // Check to see if the state change has been enabled.
                //
                if(pState->ucModemState & pState->ucRFC2217ModemMask)
                {
                    lIndex = 0;
                    pucTemp[lIndex++] = TELNET_IAC;
                    pucTemp[lIndex++] = TELNET_SB;
                    pucTemp[lIndex++] = TELNET_OPT_RFC2217;

                    //
                    // Use the "Server to Client" notification value.
                    //
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

                    //
                    // Write the data.
                    //
                    tcp_write(pState->pConnectPCB, pucTemp, lIndex, 1);
                    tcp_output(pState->pConnectPCB);

                    //
                    // Reset the index.
                    //
                    lIndex = 0;
                }
            }
        }
#endif

        //
        // While space is available in the serial output queue, process the
        // pbufs received on the telnet interface.
        //
        while(!SerialSendFull(iLoop))
        {
            //
            // Pop a pbuf off of the rx queue, if one is available, and we are
            // not already processing a pbuf.
            //
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

            //
            // If there is no packet to be processed, break out of the loop.
            //
            if(pState->pBufHead == NULL)
            {
                break;
            }

            //
            // Setup the data pointer for the current buffer.
            //
            pucData = pState->pBufCurrent->payload;

            //
            // Process the next character in the buffer.
            //
            TelnetProcessCharacter(pucData[pState->ulBufIndex], pState);

            //
            // Increment to next data byte.
            //
            pState->ulBufIndex++;

            //
            // Check to see if we are at the end of the current buffer.  If so,
            // get the next pbuf in the chain.
            //
            if(pState->ulBufIndex >= pState->pBufCurrent->len)
            {
                pState->pBufCurrent = pState->pBufCurrent->next;
                pState->ulBufIndex = 0;
            }

            //
            // Check to see if we are at the end of the chain.  If so,
            // acknowledge this data as being consumed to open up the TCP
            // window.
            //
            if((pState->pBufCurrent == NULL) && (pState->ulBufIndex == 0))
            {
                tcp_recved(pState->pConnectPCB, pState->pBufHead->tot_len);
                pbuf_free(pState->pBufHead);
                pState->pBufHead = NULL;
                pState->pBufCurrent = NULL;
                pState->ulBufIndex = 0;
            }
        }

        //
        // Flush the TCP output buffer, in the event that data was
        // queued up by processing the incoming packet.
        //
        tcp_output(pState->pConnectPCB);

        //
        // If RFC2217 is enabled, and flow control has been set to suspended,
        // skip processing of this port.
        //
#if CONFIG_RFC2217_ENABLED
        if(pState->ucRFC2217FlowControl == TELNET_C2S_FLOWCONTROL_SUSPEND)
        {
            continue;
        }
#endif

        //
        // Process the RX ring buffer data if space is available in the
        // TCP output buffer.
        //
        if(SerialReceiveAvailable(pState->ulSerialPort) &&
           tcp_sndbuf(pState->pConnectPCB) &&
           (pState->pConnectPCB->snd_queuelen < TCP_SND_QUEUELEN))
        {
            //
            // Here, we have data, and we have space.  Set the total amount
            // of data we will process to the lesser of data available or
            // space available.
            //
            lCount = (long)SerialReceiveAvailable(pState->ulSerialPort);
            if(tcp_sndbuf(pState->pConnectPCB) < lCount)
            {
                lCount = tcp_sndbuf(pState->pConnectPCB);
            }

            //
            // While we have data remaining to process, continue in this
            // loop.
            //
            while((lCount) &&
                  (pState->pConnectPCB->snd_queuelen < TCP_SND_QUEUELEN))
            {
                //
                // First, reset the index into the local buffer.
                //
                lIndex = 0;

                //
                // Fill the local buffer with data while there is data
                // and/or space remaining.
                //
                while(lCount && (lIndex < sizeof(pucTemp)))
                {
                    pucTemp[lIndex] = SerialReceive(pState->ulSerialPort);
                    lIndex++;
                    lCount--;
                }

                //
                // Write the local buffer into the TCP buffer.
                //
                tcp_write(pState->pConnectPCB, pucTemp, lIndex, 1);
            }

            //
            // Flush the data that has been written into the TCP output
            // buffer.
            //
            tcp_output(pState->pConnectPCB);
            pState->ulLastTCPSendTime = g_ulSystemTimeMS;
        }
    }
}

#endif
