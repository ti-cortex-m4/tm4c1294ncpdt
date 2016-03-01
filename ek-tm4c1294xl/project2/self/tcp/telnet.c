/*------------------------------------------------------------------------------
TELNET,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "lwip/sys.h"
#include "../kernel/log.h"
#include "../kernel/settings.h"
#include "telnet_listen.h"
#include "telnet_open.h"
#include "telnet_receive.h"
#include "telnet_poll.h"
#include "telnet.h"



//*****************************************************************************
//! The telnet session data array, for use in the telnet handler function.
//*****************************************************************************
tState g_sState[UART_COUNT];



//! The timeout for the TCP connection used for the telnet session, specified in seconds.
//! A value of 0 indicates no timeout is to be used.
ulong getTelnetTimeout(uchar u)
{
  ASSERT(u < UART_COUNT);
  return mbConnectionTimeout[u]*60;
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
    pState->eLastErr = err;

    // Free the pbufs associated with this session.
    TelnetFreePbufs(pState);

    // Reset the session data for this port.
    if(pState->pListenPCB == NULL)
    {
        // Attempt to reestablish the telnet connection to the server.
        TelnetOpen(pState->ulTelnetRemoteIP, pState->usTelnetRemotePort,
                   /*pState->usTelnetLocalPort,*/ pState->ucSerialPort);
    }
    else
    {
        // Reinitialize the server state to wait for incoming connections.
        pState->pConnectPCB = NULL;
        pState->eTCPState = STATE_TCP_LISTEN;
//        pState->eTelnetState = STATE_NORMAL;
//        pState->ucFlags = ((1 << OPT_FLAG_WILL_SUPPRESS_GA) | (1 << OPT_FLAG_SERVER));
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
//! Finalizes the TCP connection in client mode.
//!
//! \param arg is the telnet state data for this connection.
//! \param pcb is the pointer to the TCP control structure.
//! \param err is not used in this implementation.
//!
//! This function is called when the lwIP TCP/IP stack has completed a TCP
//! connection.
//!
//! \return This function will return an lwIP defined error code.
//*****************************************************************************
err_t TelnetConnected(void *arg, struct tcp_pcb *pcb, err_t err)
{
    tState *pState = arg;

    CONSOLE("%u: connected 0x%08x, 0x%08x, %d\n", pState->ucSerialPort, arg, pcb, err);

    // Increment our connection counter.
    pState->ucConnectCount++;

    // If we are not in the listening state, refuse this connection.
    if(pState->eTCPState != STATE_TCP_CONNECTING)
    {
        // If we already have a connection, kill it and start over.
        return(ERR_CONN);
    }

    if(err != ERR_OK)
    {
        CONSOLE("%u: Connected error %d\n", pState->ucSerialPort, err);
        pState->eLastErr = err;

        // Clear out all of the TCP callbacks.
        tcp_arg(pcb, NULL);
        tcp_sent(pcb, NULL);
        tcp_recv(pcb, NULL);
        tcp_err(pcb, NULL);
        tcp_poll(pcb, NULL, 1);

        // Close the TCP connection.
        tcp_close(pcb);

        // Clear out any pbufs associated with this session.
        TelnetFreePbufs(pState);

        // Re-open the connection.
        TelnetOpen(pState->ulTelnetRemoteIP, pState->usTelnetRemotePort,
                   /*pState->usTelnetLocalPort,*/ pState->ucSerialPort);

        // And return.
        return(ERR_OK);
    }

    // Save the PCB for future reference.
    pState->pConnectPCB = pcb;

    // Change TCP state to connected.
    pState->eTCPState = STATE_TCP_CONNECTED;

    // Reset the serial port associated with this session to its default parameters.
    // TODO SerialSetDefault(pState->ucSerialPort);

    // Set the connection timeout to 0.
    pState->ulConnectionTimeout = 0;

    // Setup the TCP connection priority.
    tcp_setprio(pcb, TCP_PRIO_MIN);

    // Setup the TCP receive function.
    tcp_recv(pcb, TelnetReceive);

    // Setup the TCP error function.
    tcp_err(pcb, TelnetError);

    // Setup the TCP polling function/interval.
    tcp_poll(pcb, TelnetPoll, (1000 / TCP_SLOW_INTERVAL));

    // Setup the TCP sent callback function.
    tcp_sent(pcb, TelnetSent);

#ifdef PROTOCOL_TELNET
    // Send the telnet initialization string.
    if((g_sParameters.sPort[pState->ucSerialPort].ucFlags & PORT_FLAG_PROTOCOL) == PORT_PROTOCOL_TELNET)
    {
        tcp_write(pcb, g_pucTelnetInit, sizeof(g_pucTelnetInit), 1);
        tcp_output(pcb);
    }
#endif

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
    int iPort;

    // Initialize the session data for each supported port.
    for(iPort = 0; iPort < UART_COUNT; iPort++)
    {
        g_sState[iPort].pConnectPCB = NULL;
        g_sState[iPort].pListenPCB = NULL;
        g_sState[iPort].eTCPState = STATE_TCP_IDLE;
//        g_sTelnetSession[iPort].eTelnetState = STATE_NORMAL;
//        g_sTelnetSession[iPort].ucFlags = 0;
        g_sState[iPort].ulConnectionTimeout = 0;
        g_sState[iPort].ulMaxTimeout = 0;
        g_sState[iPort].ucSerialPort = iPort;// TODO ??? UART_COUNT;
        g_sState[iPort].usTelnetRemotePort = 0;
        g_sState[iPort].usTelnetLocalPort = 0;
        g_sState[iPort].ulTelnetRemoteIP = 0;
        g_sState[iPort].iBufQRead = 0;
        g_sState[iPort].iBufQWrite = 0;
        g_sState[iPort].pBufHead = NULL;
        g_sState[iPort].pBufCurrent = NULL;
        g_sState[iPort].ulBufIndex = 0;
        g_sState[iPort].ulLastTCPSendTime = 0;
        g_sState[iPort].bLinkLost = false;
        g_sState[iPort].ucConnectCount = 0;
        g_sState[iPort].ucReconnectCount = 0;
        g_sState[iPort].ucErrorCount = 0;
        g_sState[iPort].eLastErr = ERR_OK;
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
        uint8_t ucSerialPort;
        for(ucSerialPort = 0; ucSerialPort < UART_COUNT; ucSerialPort++)
        {
            g_sState[ucSerialPort].bLinkLost = true;
        }
    }
}
