/*------------------------------------------------------------------------------
TELNET,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "lwip/sys.h"
#include "../kernel/log.h"
#include "../kernel/settings.h"
#include "tcp_errors.h"
#include "telnet_listen.h"
#include "telnet_open.h"
#include "telnet_receive.h"
#include "telnet_poll.h"
#include "telnet.h"



//*****************************************************************************
//! The telnet session data array, for use in the telnet handler function.
//*****************************************************************************
tState g_sState[UART_COUNT];



//*****************************************************************************
//! The timeout for the TCP connection used for the telnet session, specified in seconds.
//! A value of 0 indicates no timeout is to be used.
//*****************************************************************************
ulong getTelnetTimeout(uchar u)
{
  ASSERT(u < UART_COUNT);
  return mbConnectionTimeout[u];
}

//*****************************************************************************
//! Free up any queued pbufs associated with at telnet session.
//!
//! \param pState is the pointer ot the telnet session state data.
//!
//! This will free up any pbufs on the queue, and any currently active pbufs.
//!
//! \return None.
//*****************************************************************************
void TelnetFreePbufs(tState *pState)
{
    SYS_ARCH_DECL_PROTECT(lev);

    // This should be done in a protected/critical section.
    SYS_ARCH_PROTECT(lev);

    // Pop a pbuf off of the rx queue, if one is available, and we are
    // not already processing a pbuf.
    if(pState->pBufHead != NULL)
    {
        pbuf_free(pState->pBufHead);
        pState->pBufHead = NULL;
        pState->pBufCurrent = NULL;
        pState->ulBufIndex = 0;
    }

    while(pState->iBufQRead != pState->iBufQWrite)
    {
        pbuf_free(pState->pBufQ[pState->iBufQRead]);
        pState->iBufQRead = ((pState->iBufQRead + 1) % PBUF_POOL_SIZE);
    }

    // Restore previous level of protection.
    SYS_ARCH_UNPROTECT(lev);
}

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

    CONSOLE("%u: error 0x%08x, %d\n", pState->ucSerialPort, arg, err);

    // Increment our error counter.
    pState->ucErrorCount++;
    ErrorTCPOperation(pState->ucSerialPort, err, HANDLER_ERROR);

    // Free the pbufs associated with this session.
    TelnetFreePbufs(pState);

    // Reset the session data for this port.
    if(pState->pListenPCB == NULL)
    {
        // Attempt to reestablish the telnet connection to the server.
        TelnetOpen(pState->ulTelnetRemoteIP, pState->usTelnetRemotePort, pState->ucSerialPort);
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

//*****************************************************************************
//! Handles acknowledgment of data transmitted via Ethernet.
//!
//! \param arg is the telnet state data for this connection.
//! \param pcb is the pointer to the TCP control structure.
//! \param len is the length of the data transmitted.
//!
//! This function is called when the lwIP TCP/IP stack has received an
//! acknowledgment for data that has been transmitted.
//!
//! \return This function will return an lwIP defined error code.
//*****************************************************************************
err_t TelnetSent(void *arg, struct tcp_pcb *pcb, u16_t len)
{
    tState *pState = arg;

    CONSOLE("%u: sent 0x%08x, 0x%08x, %d\n", pState->ucSerialPort, arg, pcb, len);

    // Reset the connection timeout.
    pState->ulConnectionTimeout = 0;

    return(ERR_OK);
}

//*****************************************************************************
//! Initializes the telnet session(s) for the Serial to Ethernet Module.
//!
//! This function initializes the telnet session data parameter block.
//!
//! \return None.
//*****************************************************************************
void TelnetInit(void)
{
    uint8_t u;
    for(u = 0; u < UART_COUNT; u++)
    {
        g_sState[u].pConnectPCB = NULL;
        g_sState[u].pListenPCB = NULL;
        g_sState[u].eTCPState = STATE_TCP_IDLE;
        g_sState[u].ulConnectionTimeout = 0;
        g_sState[u].ulMaxTimeout = 0;
        g_sState[u].ucSerialPort = u;
        g_sState[u].usTelnetRemotePort = 0;
        g_sState[u].usTelnetLocalPort = 0;
        g_sState[u].ulTelnetRemoteIP = 0;
        g_sState[u].iBufQRead = 0;
        g_sState[u].iBufQWrite = 0;
        g_sState[u].pBufHead = NULL;
        g_sState[u].pBufCurrent = NULL;
        g_sState[u].ulBufIndex = 0;
        g_sState[u].ulLastTCPSendTime = 0;
        g_sState[u].bLinkLost = false;
        g_sState[u].ucConnectCount = 0;
        g_sState[u].ucReconnectCount = 0;
        g_sState[u].ucErrorCount = 0;
    }
}

//*****************************************************************************
//! Handles link status notification.
//!
//! \param bLinkStatusUp is the boolean indicate of link layer status.
//!
//! This function should be called when the link layer status has changed.
//!
//! \return None.
//*****************************************************************************
void TelnetNotifyLinkStatus(bool bLinkStatusUp)
{
    // We don't care if the link is up, only if it goes down.
    if(bLinkStatusUp)
    {
        CONSOLE("link status: up, ignore\n");
    }
    else
    {
        CONSOLE("link status: down\n");

        // For every port, indicate that the link has been lost.
        uint8_t u;
        for(u = 0; u < UART_COUNT; u++)
        {
            g_sState[u].bLinkLost = true;
        }
    }
}
