/*------------------------------------------------------------------------------
telnet_accept.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "../kernel/log.h"
#include "telnet.h"
#include "telnet_error.h"
#include "telnet_poll.h"
#include "telnet_receive.h"
#include "telnet_sent.h"
#include "telnet_accept.h"



//*****************************************************************************
//! Accepts a TCP connection for the telnet port.
//!
//! \param arg is the telnet state data for this connection.
//! \param pcb is the pointer to the TCP control structure.
//! \param err is not used in this implementation.
//!
//! This function is called when the lwIP TCP/IP stack has an incoming
//! connection request on the telnet port.
//!
//! \return This function will return an lwIP defined error code.
//*****************************************************************************
err_t TelnetAccept(void *arg, struct tcp_pcb *pcb, err_t err)
{
    tState *pState = arg;

    CONSOLE("[%u] accept 0x%08x, 0x%08x, %d\n", pState->ucSerialPort, arg, pcb, err);

    // If we are not in the listening state, refuse this connection.
    if(pState->eTCPState != STATE_TCP_LISTEN)
    {
        // If we haven't lost the link, then refuse this connection.
        if(!pState->bLinkLost)
        {
            // If we already have a connection, kill it and start over.
            CONSOLE("[%u] accept - already connected, start over\n", pState->ucSerialPort);
            return(ERR_CONN);
        }

        // Reset the flag for next time.
        pState->bLinkLost = false;

        // Abort the existing TCP connection.
        tcp_abort(pState->pConnectPCB);

        // Clear out any pbufs associated with this session.
        TelnetFreePbufs(pState);

        // Clear out the telnet session PCB.
        pState->pConnectPCB = NULL;
    }

    // Save the PCB for future reference.
    pState->pConnectPCB = pcb;

    // Change TCP state to connected.
    pState->eTCPState = STATE_TCP_CONNECTED;

    // Acknowledge that we have accepted this connection.
    tcp_accepted(pcb);

    // Set the connection timeout to 0.
    pState->ulConnectionTimeout = 0;

    // Setup the TCP connection priority.
    tcp_setprio(pcb, TCP_PRIO_MIN);

    // Setup the TCP receive function.
    tcp_recv(pcb, TelnetReceive);

    // Setup the TCP error function.
    tcp_err(pcb, TelnetError);

    // Setup the TCP polling function/interval.
    tcp_poll(pcb, TelnetPoll, (1000 / TCP_SLOW_INTERVAL));

    // Setup the TCP sent callback function.
    tcp_sent(pcb, TelnetSent);

#ifdef PROTOCOL_TELNET
    // Send the telnet initialization string.
    if((g_sParameters.sPort[pState->ucSerialPort].ucFlags & PORT_FLAG_PROTOCOL) == PORT_PROTOCOL_TELNET)
    {
        tcp_write(pcb, g_pucTelnetInit, sizeof(g_pucTelnetInit), 1);
        tcp_output(pcb);
    }
#endif

    return(ERR_OK);
}
