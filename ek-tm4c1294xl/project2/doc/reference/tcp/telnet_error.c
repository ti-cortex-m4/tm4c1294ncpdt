#if 1
/*------------------------------------------------------------------------------
telnet_error.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "../kernel/log.h"
#include "../uart/modem.h"
#include "tcp_errors.h"
#include "telnet.h"
#include "telnet_open.h"
#include "telnet_error.h"



//*****************************************************************************
//! Handles lwIP TCP/IP errors.
//!
//! \param arg is the telnet state data for this connection.
//! \param err is the error that was detected.
//!
//! This function is called when the lwIP TCP/IP stack has detected an error.
//! The connection is no longer valid.
//!
//! \return None.
//*****************************************************************************
static void
TelnetError(void *arg, err_t err)
{
    tTelnetSessionData *pState = arg;

    DEBUG_MSG("TelnetError 0x%08x, %d\n", arg, err);

    // Increment our error counter.
    pState->ucErrorCount++;
    pState->eLastErr = err;

    // Free the pbufs associated with this session.
    TelnetFreePbufs(pState);

    // Reset the session data for this port.
    if(pState->pListenPCB == NULL)
    {
        // Attempt to reestablish the telnet connection to the server.
        TelnetOpen(pState->ulTelnetRemoteIP, pState->usTelnetRemotePort,
                   pState->usTelnetLocalPort, pState->ulSerialPort);
    }
    else
    {
        // Reinitialize the server state to wait for incoming connections.
        pState->pConnectPCB = NULL;
        pState->eTCPState = STATE_TCP_LISTEN;
        pState->eTelnetState = STATE_NORMAL;
        pState->ucFlags = ((1 << OPT_FLAG_WILL_SUPPRESS_GA) |
                           (1 << OPT_FLAG_SERVER));
        pState->ulConnectionTimeout = 0;
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
    }
}

#endif

