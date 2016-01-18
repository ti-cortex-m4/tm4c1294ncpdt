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
//
//    //
//    // Save the PCB for future reference.
//    //
//    pState->pConnectPCB = pcb;
//
//    //
//    // Change TCP state to connected.
//    //
//    pState->eTCPState = STATE_TCP_CONNECTED;
//
//    //
//    // Reset the serial port associated with this session to its default
//    // parameters.
//    //
//    SerialSetDefault(pState->ulSerialPort);
//
//    //
//    // Set the connection timeout to 0.
//    //
//    pState->ulConnectionTimeout = 0;
//
//    //
//    // Setup the TCP connection priority.
//    //
//    tcp_setprio(pcb, TCP_PRIO_MIN);
//
//    //
//    // Setup the TCP receive function.
//    //
//    tcp_recv(pcb, TelnetReceive);
//
//    //
//    // Setup the TCP error function.
//    //
//    tcp_err(pcb, TelnetError);
//
//    //
//    // Setup the TCP polling function/interval.
//    //
//    tcp_poll(pcb, TelnetPoll, (1000 / TCP_SLOW_INTERVAL));
//
//    //
//    // Setup the TCP sent callback function.
//    //
//    tcp_sent(pcb, TelnetSent);
//
//    //
//    // Send the telnet initialization string.
//    //
//    if((g_sParameters.sPort[pState->ulSerialPort].ucFlags &
//                PORT_FLAG_PROTOCOL) == PORT_PROTOCOL_TELNET)
//    {
//        tcp_write(pcb, g_pucTelnetInit, sizeof(g_pucTelnetInit), 1);
//        tcp_output(pcb);
//    }

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
