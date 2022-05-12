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
void TelnetError(void *arg, err_t err)
{
    tState *pState = arg;

    CONSOLE("[%u] error 0x%08x, %d\n", pState->ucSerialPort, arg, err);

    // Increment our error counter.
    pState->ucErrorCount++;
    ErrorTCPOperation(pState->ucSerialPort, err, HANDLER_ERROR);

    // Free the pbufs associated with this session.
    TelnetFreePbufs(pState);

    // Reset the session data for this port.
    if(pState->pListenPCB == NULL)
    {
        if (IsModem(pState->ucSerialPort))
        {
            ModemConnectFailed(pState->ucSerialPort, err);
        }
        else
        {
            CONSOLE("[%u] try to connect again\n", pState->ucSerialPort);

            // Attempt to reestablish the telnet connection to the server.
            TelnetOpen(pState->ulTelnetRemoteIP, pState->usTelnetRemotePort, pState->ucSerialPort);
        }
    }
    else
    {
        // Reinitialize the server state to wait for incoming connections.
        pState->pConnectPCB = NULL;
        pState->eTCPState = STATE_TCP_LISTEN;
        pState->ulConnectionTimeout = 0;
        pState->iBufQRead = 0;
        pState->iBufQWrite = 0;
        pState->pBufHead = NULL;
        pState->pBufCurrent = NULL;
        pState->ulBufIndex = 0;
        pState->ulLastTCPSendTime = 0;
        pState->bLinkLost = false;
    }
}

