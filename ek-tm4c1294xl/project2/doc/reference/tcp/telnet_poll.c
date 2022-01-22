#if 0
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
static err_t
TelnetPoll(void *arg, struct tcp_pcb *pcb)
{
    err_t eError;
    struct ip_addr sIPAddr;
    tTelnetSessionData *pState = arg;

    DEBUG_MSG("TelnetPoll 0x%08x, 0x%08x\n", arg, pcb);

    // Are we operating as a server or a client?
    if(!pState->pListenPCB)
    {
        // We are operating as a client.  Are we currently trying to reconnect
        // to the server?
        if(pState->eTCPState == STATE_TCP_CONNECTING)
        {
            // We are trying to reconnect but can't have received the connection
            // callback in the last 3 seconds so we try connecting again.
            pState->ucReconnectCount++;
            sIPAddr.addr = htonl(pState->ulTelnetRemoteIP);
            eError = tcp_connect(pcb, &sIPAddr, pState->usTelnetRemotePort,
                                 TelnetConnected);

            if(eError != ERR_OK)
            {
                // Remember the error for later.
                pState->eLastErr = eError;
            }
        }
    }
    else
    {
        // We are operating as a server. Increment the timeout value and close
        // the telnet connection if the configured timeout has been exceeded.
        pState->ulConnectionTimeout++;
        if((pState->ulMaxTimeout != 0) &&
           (pState->ulConnectionTimeout > pState->ulMaxTimeout))
        {
            // Close the telnet connection.
            tcp_abort(pcb);
        }
    }

    // Return OK.
    return(ERR_OK);
}

#endif