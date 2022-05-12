/*------------------------------------------------------------------------------
telnet_open.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "../kernel/log.h"
#include "tcp_errors.h"
#include "telnet.h"
#include "telnet_error.h"
#include "telnet_poll.h"
#include "telnet_connected.h"
#include "telnet_open.h"



//*****************************************************************************
//! Opens a telnet server session (client).
//!
//! \param ulIPAddr is the IP address of the telnet server.
//! \param usTelnetRemotePort is port number of the telnet server.
//! \param ucSerialPort is the serial port associated with this telnet session.
//!
//! This function establishes a TCP session by attempting a connection to
//! a telnet server.
//!
//! \return None.
//*****************************************************************************
void TelnetOpen(uint32_t ulIPAddr, uint16_t usTelnetRemotePort, uint8_t ucSerialPort)
{
    ASSERT(ulIPAddr != 0);
    ASSERT(ucSerialPort < UART_COUNT);
    ASSERT(usTelnetRemotePort != 0);

    tState *pState = &g_sState[ucSerialPort];

    CONSOLE("[%u] open %d.%d.%d.%d port %d\n",
            pState->ucSerialPort,
            (ulIPAddr >> 24), (ulIPAddr >> 16) & 0xFF, (ulIPAddr >> 8) & 0xFF, ulIPAddr & 0xFF,
            usTelnetRemotePort);

    // Fill in the telnet state data structure for this session in client mode.
    pState->pConnectPCB = NULL;
    pState->pListenPCB = NULL;
    pState->eTCPState = STATE_TCP_CONNECTING;
    pState->ulConnectionTimeout = 0;
    pState->ulMaxTimeout = getTelnetTimeout(ucSerialPort); // g_sParameters.sPort[ucSerialPort].ulTelnetTimeout;
    pState->ucSerialPort = ucSerialPort;
    pState->usTelnetRemotePort = usTelnetRemotePort;
    pState->ulTelnetRemoteIP = ulIPAddr;
    pState->iBufQRead = 0;
    pState->iBufQWrite = 0;
    pState->pBufHead = NULL;
    pState->pBufCurrent = NULL;
    pState->ulBufIndex = 0;
    pState->ulLastTCPSendTime = 0;
    pState->bLinkLost = false;

    // Make a connection to the remote telnet server.
    void *pcb = tcp_new();
    if (pcb == NULL)
    {
        ERROR("[%u] open.tcp_new failed, NULL\n", pState->ucSerialPort);
        ErrorTCPOperation(pState->ucSerialPort, ERR_MEM, TCP_NEW_OPEN);
        return;
    }

    // Save the requested information and set the TCP callback functions and arguments.
    tcp_arg(pcb, pState);

    // Set the TCP error callback.
    tcp_err(pcb, TelnetError);

    // Set the callback that will be made after 3 seconds.  This allows us to
    // reattempt the connection if we do not receive a response.
    tcp_poll(pcb, TelnetPoll, (3000 / TCP_SLOW_INTERVAL));

    struct ip4_addr sIPAddr;
    sIPAddr.addr = htonl(ulIPAddr);

    // Attempt to connect to the server.
    err_t err = tcp_connect(pcb, &sIPAddr, usTelnetRemotePort, TelnetConnected);
    if(err != ERR_OK)
    {
        ERROR("[%u] open.tcp_connect failed, error=%d\n", pState->ucSerialPort, err);
        ErrorTCPOperation(pState->ucSerialPort, err, TCP_CONNECT_OPEN);
        return;
    }
}

