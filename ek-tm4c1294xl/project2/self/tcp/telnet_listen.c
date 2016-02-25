/*------------------------------------------------------------------------------
telnet_listen,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "telnet.h"
#include "telnet_listen.h"



//*****************************************************************************
//! Opens a telnet server session (listen).
//!
//! \param usTelnetPort is the telnet port number to listen on.
//! \param ulSerialPort is the serial port associated with this telnet session.
//!
//! This function establishes a TCP session in listen mode as a telnet server.
//!
//! \return None.
//*****************************************************************************
void TelnetListen(uint16_t usTelnetPort, uint32_t ulSerialPort)
{
    void *pcb;

    // Check the arguments.
    ASSERT(ulSerialPort < UART_COUNT);
    ASSERT(usTelnetPort != 0);
    tTelnetSession *pState = &g_sTelnetSession[ulSerialPort];

    CONSOLE("%u: listen port %d, UART %d\n", pState->ulSerialPort, usTelnetPort, ulSerialPort);

    // Fill in the telnet state data structure for this session in listen
    // (in other words, server) mode.
    pState->pConnectPCB = NULL;
    pState->eTCPState = STATE_TCP_LISTEN;
//    pState->eTelnetState = STATE_NORMAL;
//    pState->ucFlags = ((1 << OPT_FLAG_WILL_SUPPRESS_GA) | (1 << OPT_FLAG_SERVER));
    pState->ulConnectionTimeout = 0;
    pState->ulMaxTimeout = getTelnetTimeout(ulSerialPort); // g_sParameters.sPort[ulSerialPort].ulTelnetTimeout;
    pState->ulSerialPort = ulSerialPort;
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
    pcb = tcp_new(); // TODO check NULL
    tcp_bind(pcb, IP_ADDR_ANY, usTelnetPort);
    pcb = tcp_listen(pcb);
    pState->pListenPCB = pcb;

    // Save the requested information and set the TCP callback functions
    // and arguments.
    tcp_arg(pcb, pState);
    tcp_accept(pcb, TelnetAccept);
}
