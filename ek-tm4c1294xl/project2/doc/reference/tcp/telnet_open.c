#if 0
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
//! \param usTelnetLocalPort is local port number to connect from.
//! \param ulSerialPort is the serial port associated with this telnet session.
//!
//! This function establishes a TCP session by attempting a connection to
//! a telnet server.
//!
//! \return None.
//*****************************************************************************
void
TelnetOpen(uint32_t ulIPAddr, uint16_t usTelnetRemotePort,
           uint16_t usTelnetLocalPort, uint32_t ulSerialPort)
{
    void *pcb;
    struct ip_addr sIPAddr;
    err_t eError;
    tTelnetSessionData *pState;

    DEBUG_MSG("TelnetOpen %d.%d.%d.%d port %d, UART %d\n",
              (ulIPAddr >> 24), (ulIPAddr >> 16) & 0xFF,
              (ulIPAddr >> 8) & 0xFF, ulIPAddr & 0xFF, usTelnetRemotePort,
              ulSerialPort);

    // Check the arguments.
    ASSERT(ulIPAddr != 0);
    ASSERT(ulSerialPort < MAX_S2E_PORTS);
    ASSERT(usTelnetRemotePort != 0);
    ASSERT(usTelnetLocalPort != 0);
    pState = &g_sTelnetSession[ulSerialPort];

    // Fill in the telnet state data structure for this session in client
    // mode.
    pState->pConnectPCB = NULL;
    pState->pListenPCB = NULL;
    pState->eTCPState = STATE_TCP_CONNECTING;
    pState->eTelnetState = STATE_NORMAL;
    pState->ucFlags = (1 << OPT_FLAG_WILL_SUPPRESS_GA);
    pState->ulConnectionTimeout = 0;
    pState->ulMaxTimeout = g_sParameters.sPort[ulSerialPort].ulTelnetTimeout;
    pState->ulSerialPort = ulSerialPort;
    pState->usTelnetRemotePort = usTelnetRemotePort;
    pState->usTelnetLocalPort = usTelnetLocalPort;
    pState->ulTelnetRemoteIP = ulIPAddr;
    pState->iBufQRead = 0;
    pState->iBufQWrite = 0;
    pState->pBufHead = NULL;
    pState->pBufCurrent = NULL;
    pState->ulBufIndex = 0;
    pState->ulLastTCPSendTime = 0;

#if CONFIG_RFC2217_ENABLED
    pState->ucFlags |= (1 << OPT_FLAG_WILL_RFC2217);
    pState->ucRFC2217FlowControl =
        TELNET_C2S_FLOWCONTROL_RESUME;
    pState->ucRFC2217ModemMask = 0;
    pState->ucRFC2217LineMask = 0xff;
    pState->ucLastModemState = 0;
    pState->ucModemState = 0;
#endif
    pState->bLinkLost = false;

    // Make a connection to the remote telnet server.
    sIPAddr.addr = htonl(ulIPAddr);
    pcb = tcp_new();

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
        // Remember the error for later.
        pState->eLastErr = eError;
        return;
    }
}

#endif
