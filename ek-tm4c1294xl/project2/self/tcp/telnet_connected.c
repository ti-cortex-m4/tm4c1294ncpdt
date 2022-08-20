/*------------------------------------------------------------------------------
telnet_connected.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "../kernel/log.h"
#include "../uart/modem.h"
#include "tcp_errors.h"
#include "telnet.h"
#include "telnet_error.h"
#include "telnet_poll.h"
#include "telnet_open.h"
#include "telnet_receive.h"
#include "telnet_sent.h"
#include "telnet_connected.h"



//*****************************************************************************
//! Finalizes the TCP connection in client mode.
//!
//! \param arg is the telnet state data for this connection.
//! \param pcb is the pointer to the TCP control structure.
//! \param err is not used in this implementation.
//!
//! This function is called when the lwIP TCP/IP stack has completed a TCP
//! connection.
//!
//! \return This function will return an lwIP defined error code.
//*****************************************************************************
err_t TelnetConnected(void *arg, struct tcp_pcb *pcb, err_t err)
{
    tState *pState = arg;

    CONSOLE("[%u] connected 0x%08x, 0x%08x, %d\n", pState->ucSerialPort, arg, pcb, err);

    // Increment our connection counter.
    pState->ucConnectCount++;

    // If we are not in the listening state, refuse this connection.
    if(pState->eTCPState != STATE_TCP_CONNECTING)
    {
        // If we already have a connection, kill it and start over.
        CONSOLE("[%u] connected - already connected, start over\n", pState->ucSerialPort);
        return(ERR_CONN);
    }

    if(err != ERR_OK)
    {
        ERROR("[%u] connected error=%d\n", pState->ucSerialPort, err);
        ErrorTCPOperation(pState->ucSerialPort, err, HANDLER_CONNECTED);

        // Clear out all of the TCP callbacks.
        tcp_arg(pcb, NULL);
        tcp_sent(pcb, NULL);
        tcp_recv(pcb, NULL);
        tcp_err(pcb, NULL);
        tcp_poll(pcb, NULL, 1);

        // Close the TCP connection.
        err_t err = tcp_close(pcb);
        if (err != ERR_OK)
        {
           WARNING("[%u] connected.tcp_close failed, error=%d\n", pState->ucSerialPort, err);
           ErrorTCPOperation(pState->ucSerialPort, err, TCP_CLOSE_CONNECTED);
        }

        // Clear out any pbufs associated with this session.
        TelnetFreePbufs(pState);

        // Re-open the connection.
        TelnetOpen(pState->ulTelnetRemoteIP, pState->usTelnetRemotePort, pState->ucSerialPort);

        return(ERR_OK);
    }

    // Save the PCB for future reference.
    pState->pConnectPCB = pcb;

    // Change TCP state to connected.
    pState->eTCPState = STATE_TCP_CONNECTED;

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

    ModemConnected(pState->ucSerialPort);

    return(ERR_OK);
}
