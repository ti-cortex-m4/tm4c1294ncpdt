/*------------------------------------------------------------------------------
telnet_open,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "lwip/sys.h"
#include "../kernel/log.h"
#include "telnet.h"
#include "telnet_poll.h"
#include "telnet_open.h"



//*****************************************************************************
//! Opens a telnet server session (client).
//!
//! \param ulIPAddr is the IP address of the telnet server.
//! \param usTelnetRemotePort is port number of the telnet server.
//! \param usTelnetLocalPort is local port number to connect from.
//! \param ucSerialPort is the serial port associated with this telnet session.
//!
//! This function establishes a TCP session by attempting a connection to
//! a telnet server.
//!
//! \return None.
//*****************************************************************************
void TelnetOpen(uint32_t ulIPAddr, uint16_t usTelnetRemotePort,/* uint16_t usTelnetLocalPort,*/ uint8_t ucSerialPort)
{
    void *pcb;
    struct ip_addr sIPAddr;
    err_t eError;

    // Check the arguments.
    ASSERT(ulIPAddr != 0);
    ASSERT(ucSerialPort < UART_COUNT);
    ASSERT(usTelnetRemotePort != 0);
//    ASSERT(usTelnetLocalPort != 0);
    tState *pState = &g_sState[ucSerialPort];

    CONSOLE("%u: open %d.%d.%d.%d port %d, UART %d\n",
              pState->ucSerialPort,
              (ulIPAddr >> 24), (ulIPAddr >> 16) & 0xFF,
              (ulIPAddr >> 8) & 0xFF, ulIPAddr & 0xFF, usTelnetRemotePort,
              ucSerialPort);

    // Fill in the telnet state data structure for this session in client
    // mode.
    pState->pConnectPCB = NULL;
    pState->pListenPCB = NULL;
    pState->eTCPState = STATE_TCP_CONNECTING;
//    pState->eTelnetState = STATE_NORMAL;
//    pState->ucFlags = (1 << OPT_FLAG_WILL_SUPPRESS_GA);
    pState->ulConnectionTimeout = 0;
    pState->ulMaxTimeout = getTelnetTimeout(ucSerialPort); // g_sParameters.sPort[ucSerialPort].ulTelnetTimeout;
    pState->ucSerialPort = ucSerialPort;
    pState->usTelnetRemotePort = usTelnetRemotePort;
//    pState->usTelnetLocalPort = usTelnetLocalPort;
    pState->ulTelnetRemoteIP = ulIPAddr;
    pState->iBufQRead = 0;
    pState->iBufQWrite = 0;
    pState->pBufHead = NULL;
    pState->pBufCurrent = NULL;
    pState->ulBufIndex = 0;
    pState->ulLastTCPSendTime = 0;
    pState->bLinkLost = false;

    // Make a connection to the remote telnet server.
    sIPAddr.addr = htonl(ulIPAddr);
    pcb = tcp_new(); // TODO check NULL

    // Save the requested information and set the TCP callback functions
    // and arguments.
    tcp_arg(pcb, pState);

    // Set the TCP error callback.
    tcp_err(pcb, TelnetError);

    // Set the callback that will be made after 3 seconds.  This allows us to
    // reattempt the connection if we do not receive a response.
    tcp_poll(pcb, TelnetPoll, (3000 / TCP_SLOW_INTERVAL));

    // Attempt to connect to the server.
    eError = tcp_connect(pcb, &sIPAddr, usTelnetRemotePort, TelnetConnected);
    if(eError != ERR_OK)
    {
        CONSOLE("%u: Open error %d\n", pState->ucSerialPort, eError);
        pState->eLastErr = eError;
        return;
    }
}

