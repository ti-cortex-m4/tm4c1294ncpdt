/*------------------------------------------------------------------------------
TELNET.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/sys.h"
#include "../kernel/log.h"
#include "../kernel/settings.h"
#include "../kernel/link_up_reset.h"
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
    if(bLinkStatusUp)
    {
        CONSOLE("link status: up, ignore\n");
        LinkUpReset_Start();
    }
    else
    {
        CONSOLE("link status: down\n");

        uint8_t u;
        for(u = 0; u < UART_COUNT; u++)
        {
            g_sState[u].bLinkLost = true;
        }
    }
}
