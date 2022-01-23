#if 0
/*------------------------------------------------------------------------------
TELNET.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/sys.h"
#include "../kernel/log.h"
#include "../kernel/settings.h"
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
static void
TelnetFreePbufs(tTelnetSessionData *pState)
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
void
TelnetInit(void)
{
    int iPort;

    // Initialize the session data for each supported port.
    for(iPort = 0; iPort < MAX_S2E_PORTS; iPort++)
    {
        g_sTelnetSession[iPort].pConnectPCB = NULL;
        g_sTelnetSession[iPort].pListenPCB = NULL;
        g_sTelnetSession[iPort].eTCPState = STATE_TCP_IDLE;
        g_sTelnetSession[iPort].eTelnetState = STATE_NORMAL;
        g_sTelnetSession[iPort].ucFlags = 0;
        g_sTelnetSession[iPort].ulConnectionTimeout = 0;
        g_sTelnetSession[iPort].ulMaxTimeout = 0;
        g_sTelnetSession[iPort].ulSerialPort = MAX_S2E_PORTS;
        g_sTelnetSession[iPort].usTelnetRemotePort = 0;
        g_sTelnetSession[iPort].usTelnetLocalPort = 0;
        g_sTelnetSession[iPort].ulTelnetRemoteIP = 0;
        g_sTelnetSession[iPort].iBufQRead = 0;
        g_sTelnetSession[iPort].iBufQWrite = 0;
        g_sTelnetSession[iPort].pBufHead = NULL;
        g_sTelnetSession[iPort].pBufCurrent = NULL;
        g_sTelnetSession[iPort].ulBufIndex = 0;
        g_sTelnetSession[iPort].ulLastTCPSendTime = 0;
#if CONFIG_RFC2217_ENABLED
        g_sTelnetSession[iPort].eRFC2217State = STATE_2217_GET_DATA;
        g_sTelnetSession[iPort].ucRFC2217Command = 0;
        g_sTelnetSession[iPort].ulRFC2217Value = 0;
        g_sTelnetSession[iPort].ucRFC2217Index = 0;
        g_sTelnetSession[iPort].ucRFC2217IndexMax = 0;
        g_sTelnetSession[iPort].ucRFC2217FlowControl = 0;
        g_sTelnetSession[iPort].ucRFC2217ModemMask = 0;
        g_sTelnetSession[iPort].ucRFC2217LineMask = 0;
        g_sTelnetSession[iPort].ucLastModemState = 0;
        g_sTelnetSession[iPort].ucModemState = 0;
#endif
        g_sTelnetSession[iPort].bLinkLost = false;
        g_sTelnetSession[iPort].ucConnectCount = 0;
        g_sTelnetSession[iPort].ucReconnectCount = 0;
        g_sTelnetSession[iPort].ucErrorCount = 0;
        g_sTelnetSession[iPort].eLastErr = ERR_OK;
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
#endif
