/*------------------------------------------------------------------------------
telnet_listen.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "tcp_errors.h"
#include "telnet.h"
#include "telnet_accept.h"
#include "telnet_listen.h"



//*****************************************************************************
//! Opens a telnet server session (listen).
//!
//! \param usTelnetPort is the telnet port number to listen on.
//! \param ucSerialPort is the serial port associated with this telnet session.
//!
//! This function establishes a TCP session in listen mode as a telnet server.
//!
//! \return None.
//*****************************************************************************
void TelnetListen(uint16_t usTelnetPort, uint8_t ucSerialPort)
{
    ASSERT(ucSerialPort < UART_COUNT);
    ASSERT(usTelnetPort != 0);

    tState *pState = &g_sState[ucSerialPort];

    CONSOLE("[%u] listen on port %d\n", pState->ucSerialPort, usTelnetPort);

    // Fill in the telnet state data structure for this session in listen (server) mode.
    pState->pConnectPCB = NULL;
    pState->eTCPState = STATE_TCP_LISTEN;
    pState->ulConnectionTimeout = 0;
    pState->ulMaxTimeout = getTelnetTimeout(ucSerialPort); // g_sParameters.sPort[ucSerialPort].ulTelnetTimeout;
    pState->ucSerialPort = ucSerialPort;
    pState->usTelnetLocalPort = usTelnetPort;
    pState->usTelnetRemotePort = 0;
    pState->ulTelnetRemoteIP = 0;
    pState->iBufQRead = 0;
    pState->iBufQWrite = 0;
    pState->pBufHead = NULL;
    pState->pBufCurrent = NULL;
    pState->ulBufIndex = 0;
    pState->ulLastTCPSendTime = 0;
    pState->bLinkLost = false;

    // Initialize the application to listen on the requested telnet port.
    struct tcp_pcb *pcb = tcp_new();
    if (pcb == NULL)
    {
        ERROR("[%u] listen.tcp_new failed, NULL\n", pState->ucSerialPort);
        ErrorTCPOperation(pState->ucSerialPort, ERR_MEM, TCP_NEW_LISTEN);
        return;
    }

    ip_set_option(pcb, SOF_REUSEADDR);

    err_t err = tcp_bind(pcb, IP_ADDR_ANY, usTelnetPort);
    if (err != ERR_OK)
    {
        ERROR("[%u] listen.tcp_bind to port %u failed, error=%d\n", pState->ucSerialPort, usTelnetPort, err);
        ErrorTCPOperation(pState->ucSerialPort, err, TCP_BIND_LISTEN);
        return;
    }

    pcb = tcp_listen(pcb);
    pState->pListenPCB = pcb;

    // Save the requested information and set the TCP callback functions and arguments.
    tcp_arg(pcb, pState);
    tcp_accept(pcb, TelnetAccept);
}
