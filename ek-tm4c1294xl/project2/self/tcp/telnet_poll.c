/*------------------------------------------------------------------------------
telnet_poll.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "../kernel/tasks.h"
#include "../uart/modem.h"
#include "tcp_errors.h"
#include "telnet.h"
#include "telnet_close.h"
#include "telnet_connected.h"
#include "telnet_poll.h"



//*****************************************************************************
//! Handles lwIP TCP/IP polling and timeout requests.
//!
//! \param arg is the telnet state data for this connection.
//! \param pcb is the pointer to the TCP control structure.
//!
//! This function is called periodically and is used to re-establish dropped
//! client connections and to reset idle server connections.
//!
//! \return This function will return an lwIP defined error code.
//*****************************************************************************
err_t TelnetPoll(void *arg, struct tcp_pcb *pcb)
{
    tState *pState = arg;

    CONSOLE("[%u] poll 0x%08x, 0x%08x %u/%u\n", pState->ucSerialPort, arg, pcb, pState->ulConnectionTimeout, pState->ulMaxTimeout);

    // Are we operating as a server or a client?
    if(!pState->pListenPCB)
    {
        // We are operating as a client.  Are we currently trying to reconnect to the server?
        if(pState->eTCPState == STATE_TCP_CONNECTING)
        {
            if (pcb->state != CLOSED)
            {
              CONSOLE("[%u] poll state=%d\n", pState->ucSerialPort, pcb->state);
            }
            else
            {
                // We are trying to reconnect but can't have received the connection
                // callback in the last 3 seconds so we try connecting again.
                pState->ucReconnectCount++;

                struct ip4_addr sIPAddr;
                sIPAddr.addr = htonl(pState->ulTelnetRemoteIP);

                err_t err = tcp_connect(pcb, &sIPAddr, pState->usTelnetRemotePort, TelnetConnected);
                if(err != ERR_OK)
                {
                    ERROR("[%u] poll.tcp_connect failed, error=%d\n", pState->ucSerialPort, err);
                    ErrorTCPOperation(pState->ucSerialPort, err, TCP_CONNECT_POLL);
                }
            }
        }
        else if(pState->eTCPState == STATE_TCP_CONNECTED)
        {
            pState->ulConnectionTimeout++;
            if ((pState->ulMaxTimeout != 0) && (pState->ulConnectionTimeout > pState->ulMaxTimeout))
            {
               if (IsModemModeData(pState->ucSerialPort)) {
                   ModemDisconnectedByTimeout(pState->ucSerialPort);
               }

               CONSOLE("[%u] poll - close client connection by timeout\n", pState->ucSerialPort);
               return TelnetCloseClient(pState->ucSerialPort);
            }
        }
    }
    else
    {
        // We are operating as a server. Increment the timeout value and close the telnet connection if the configured timeout has been exceeded.
        pState->ulConnectionTimeout++;
        if ((pState->ulMaxTimeout != 0) && (pState->ulConnectionTimeout > pState->ulMaxTimeout))
        {
            CONSOLE("[%u] poll - close server connection by timeout\n", pState->ucSerialPort);

            // Close the telnet connection.
            tcp_abort(pcb);
        }
    }

    return(ERR_OK);
}
