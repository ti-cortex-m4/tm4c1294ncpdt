/*------------------------------------------------------------------------------
TCP_CLIENT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "lwip/sys.h"
#include "../uart/log.h"
#include "../uart/serial.h"
#include "../settings2.h"
#include "telnet.h"
#include "tcp_client.h"



//*****************************************************************************
//! The telnet session data array, for use in the telnet handler function.
//*****************************************************************************
static tTelnetSessionData g_sTelnetSession[MAX_S2E_PORTS];


//*****************************************************************************
// Forward Reference.
//*****************************************************************************
static err_t TelnetConnected(void *arg, struct tcp_pcb *pcb, err_t err);


//*****************************************************************************
// External Reference.
//*****************************************************************************
extern uint32_t g_ulSystemTimeMS;



//*****************************************************************************
//! Free up any queued pbufs associated with at telnet session.
//!
//! \param pState is the pointer ot the telnet session state data.
//!
//! This will free up any pbufs on the queue, and any currently active pbufs.
//!
//! \return None.
//*****************************************************************************
static void TelnetFreePbufs(tTelnetSessionData *pState)
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
//! Handles lwIP TCP/IP polling and timeout requests.
//!
//! \param arg is the telnet state data for this connection.
//! \param pcb is the pointer to the TCP control structure.
//!
//! This function is called periodically and is used to re-establish dropped
//! client connections and to reset idle server connections.
//!
//! \return This function will return an lwIP defined error code.
//*****************************************************************************
static err_t TelnetPoll(void *arg, struct tcp_pcb *pcb)
{
    err_t eError;
    struct ip_addr sIPAddr;
    tTelnetSessionData *pState = arg;

    DEBUG_MSG("TelnetPoll 0x%08x, 0x%08x\n", arg, pcb);

    // Are we operating as a server or a client?
    if(!pState->pListenPCB)
    {
        // We are operating as a client.  Are we currently trying to reconnect
        // to the server?
        if(pState->eTCPState == STATE_TCP_CONNECTING)
        {
            // We are trying to reconnect but can't have received the connection
            // callback in the last 3 seconds so we try connecting again.
            pState->ucReconnectCount++;
            sIPAddr.addr = htonl(pState->ulTelnetRemoteIP);
            eError = tcp_connect(pcb, &sIPAddr, pState->usTelnetRemotePort, TelnetConnected);

            if(eError != ERR_OK)
            {
                // Remember the error for later.
                pState->eLastErr = eError;
            }
        }
    }
    else
    {
        // We are operating as a server. Increment the timeout value and close
        // the telnet connection if the configured timeout has been exceeded.
        pState->ulConnectionTimeout++;
        if((pState->ulMaxTimeout != 0) &&
           (pState->ulConnectionTimeout > pState->ulMaxTimeout))
        {
            // Close the telnet connection.
            tcp_abort(pcb);
        }
    }

    // Return OK.
    return(ERR_OK);
}

//*****************************************************************************
//
//! Processes a character received from the telnet port.
//!
//! \param ucChar is the character in question.
//! \param pState is the telnet state data for this connection.
//!
//! This function processes a character received from the telnet port, handling
//! the interpretation of telnet commands (as indicated by the telnet interpret
//! as command (IAC) byte).
//!
//! \return None.
//
//*****************************************************************************
static void TelnetProcessCharacter(uint8_t ucChar, tTelnetSessionData *pState)
{
    // Write this character to the UART with no telnet processing.
    SerialSend(pState->ulSerialPort, ucChar);
}

//*****************************************************************************
//! Receives a TCP packet from lwIP for the telnet server.
//!
//! \param arg is the telnet state data for this connection.
//! \param pcb is the pointer to the TCP control structure.
//! \param p is the pointer to the pbuf structure containing the packet data.
//! \param err is used to indicate if any errors are associated with the
//! incoming packet.
//!
//! This function is called when the lwIP TCP/IP stack has an incoming packet
//! to be processed.
//!
//! \return This function will return an lwIP defined error code.
//*****************************************************************************
static err_t TelnetReceive(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
    tTelnetSessionData *pState = arg;
    int iNextWrite;
    SYS_ARCH_DECL_PROTECT(lev);

    DEBUG_MSG("TelnetReceive 0x%08x, 0x%08x, 0x%08x, %d\n", arg, pcb, p, err);

    // Place the incoming packet onto the queue if there is space.
    if((err == ERR_OK) && (p != NULL))
    {
        // This should be done in a protected/critical section.
        SYS_ARCH_PROTECT(lev);

        // Do we have space in the queue?
        iNextWrite = ((pState->iBufQWrite + 1) % PBUF_POOL_SIZE);
        if(iNextWrite == pState->iBufQRead)
        {
            // The queue is full - discard the pbuf and return since we can't
            // handle it just now.

            // Restore previous level of protection.
            SYS_ARCH_UNPROTECT(lev);

            // Free up the pbuf.  Note that we don't acknowledge receipt of
            // the data since we want it to be retransmitted later.
            pbuf_free(p);
        }
        else
        {
            // Place the pbuf in the circular queue.
            pState->pBufQ[pState->iBufQWrite] = p;

            // Increment the queue write index.
            pState->iBufQWrite = iNextWrite;

            // Restore previous level of protection.
            SYS_ARCH_UNPROTECT(lev);
        }
    }

    // If a null packet is passed in, close the connection.
    else if((err == ERR_OK) && (p == NULL))
    {
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

        // Clear out the telnet session PCB.
        pState->pConnectPCB = NULL;

        // If we don't have a listen PCB, then we are in client mode, and
        // should try to reconnect.
        if(pState->pListenPCB == NULL)
        {
            // Re-open the connection.
            TelnetOpen(pState->ulTelnetRemoteIP, pState->usTelnetRemotePort,
                       pState->usTelnetLocalPort, pState->ulSerialPort);
        }
        else
        {
            // Revert to listening state.
            pState->eTCPState = STATE_TCP_LISTEN;
        }
    }

    // Return okay.
    return(ERR_OK);
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
static void TelnetError(void *arg, err_t err)
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
//        pState->eTelnetState = STATE_NORMAL;
        pState->ucFlags = ((1 << OPT_FLAG_WILL_SUPPRESS_GA) | (1 << OPT_FLAG_SERVER));
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
static err_t TelnetSent(void *arg, struct tcp_pcb *pcb, u16_t len)
{
    tTelnetSessionData *pState = arg;

    DEBUG_MSG("TelnetSent 0x%08x, 0x%08x, %d\n", arg, pcb, len);

    // Reset the connection timeout.
    pState->ulConnectionTimeout = 0;

    // Return OK.
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
static err_t TelnetConnected(void *arg, struct tcp_pcb *pcb, err_t err)
{
    tTelnetSessionData *pState = arg;

    DEBUG_MSG("TelnetConnected 0x%08x, 0x%08x, %d\n", arg, pcb, err);

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
        // Remember the error that is being reported.
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
                   pState->usTelnetLocalPort, pState->ulSerialPort);

        // And return.
        return(ERR_OK);
    }

    // Save the PCB for future reference.
    pState->pConnectPCB = pcb;

    // Change TCP state to connected.
    pState->eTCPState = STATE_TCP_CONNECTED;

    // Reset the serial port associated with this session to its default
    // parameters.
    SerialSetDefault(pState->ulSerialPort);

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
    if((g_sParameters.sPort[pState->ulSerialPort].ucFlags & PORT_FLAG_PROTOCOL) == PORT_PROTOCOL_TELNET)
    {
        tcp_write(pcb, g_pucTelnetInit, sizeof(g_pucTelnetInit), 1);
        tcp_output(pcb);
    }
#endif

    // Return a success code.
    return(ERR_OK);
}

//*****************************************************************************
//! Accepts a TCP connection for the telnet port.
//!
//! \param arg is the telnet state data for this connection.
//! \param pcb is the pointer to the TCP control structure.
//! \param err is not used in this implementation.
//!
//! This function is called when the lwIP TCP/IP stack has an incoming
//! connection request on the telnet port.
//!
//! \return This function will return an lwIP defined error code.
//*****************************************************************************
static err_t TelnetAccept(void *arg, struct tcp_pcb *pcb, err_t err)
{
    tTelnetSessionData *pState = arg;

    DEBUG_MSG("TelnetAccept 0x%08x, 0x%08x, 0x%08x\n", arg, pcb, err);

    // If we are not in the listening state, refuse this connection.
    if(pState->eTCPState != STATE_TCP_LISTEN)
    {
        // If we haven't lost the link, then refuse this connection.
        if(!pState->bLinkLost)
        {
            // If we already have a connection, kill it and start over.
            return(ERR_CONN);
        }

        // Reset the flag for next time.
        pState->bLinkLost = false;

        // Abort the existing TCP connection.
        tcp_abort(pState->pConnectPCB);

        // Clear out any pbufs associated with this session.
        TelnetFreePbufs(pState);

        // Clear out the telnet session PCB.
        pState->pConnectPCB = NULL;

    }

    // Save the PCB for future reference.
    pState->pConnectPCB = pcb;

    // Change TCP state to connected.
    pState->eTCPState = STATE_TCP_CONNECTED;

    // Acknowledge that we have accepted this connection.
    tcp_accepted(pcb);

    // Reset the serial port associated with this session to its default
    // parameters.
    SerialSetDefault(pState->ulSerialPort);

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
    if((g_sParameters.sPort[pState->ulSerialPort].ucFlags & PORT_FLAG_PROTOCOL) == PORT_PROTOCOL_TELNET)
    {
        tcp_write(pcb, g_pucTelnetInit, sizeof(g_pucTelnetInit), 1);
        tcp_output(pcb);
    }
#endif

    // Return a success code.
    return(ERR_OK);
}

//*****************************************************************************
//! Closes an existing Ethernet connection.
//!
//! \param ulSerialPort is the serial port associated with this telnet session.
//!
//! This function is called when the the Telnet/TCP session associated with
//! the specified serial port is to be closed.
//!
//! \return None.
//*****************************************************************************
void TelnetClose(uint32_t ulSerialPort)
{
    tTelnetSessionData *pState;

    DEBUG_MSG("TelnetClose UART %d\n", ulSerialPort);

    // Check the arguments.
    ASSERT(ulSerialPort < MAX_S2E_PORTS);
    pState = &g_sTelnetSession[ulSerialPort];

    // If we have a connect PCB, close it down.
    if(pState->pConnectPCB != NULL)
    {
        DEBUG_MSG("Closing connect pcb 0x%08x\n", pState->pConnectPCB);

        // Clear out all of the TCP callbacks.
        tcp_arg(pState->pConnectPCB, NULL);
        tcp_sent(pState->pConnectPCB, NULL);
        tcp_recv(pState->pConnectPCB, NULL);
        tcp_err(pState->pConnectPCB, NULL);
        tcp_poll(pState->pConnectPCB, NULL, 1);

        // Abort the existing TCP connection.
        tcp_abort(pState->pConnectPCB);

        // Clear out any pbufs associated with this session.
        TelnetFreePbufs(pState);
    }

    // If we have a listen PCB, close it down as well.
    if(pState->pListenPCB != NULL)
    {
        DEBUG_MSG("Closing listen pcb 0x%08x\n", pState->pListenPCB);

        // Close the TCP connection.
        tcp_close(pState->pListenPCB);

        // Clear out any pbufs associated with this session.
        TelnetFreePbufs(pState);
    }

    // Reset the session data for this port.
    pState->pConnectPCB = NULL;
    pState->pListenPCB = NULL;
    pState->eTCPState = STATE_TCP_IDLE;
//    pState->eTelnetState = STATE_NORMAL;
    pState->ucFlags = 0;
    pState->ulConnectionTimeout = 0;
    pState->ulMaxTimeout = 0;
    pState->ulSerialPort = MAX_S2E_PORTS;
    pState->iBufQRead = 0;
    pState->iBufQWrite = 0;
    pState->pBufHead = NULL;
    pState->pBufCurrent = NULL;
    pState->ulBufIndex = 0;
    pState->ulLastTCPSendTime = 0;
    pState->bLinkLost = false;
}

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
void TelnetOpen(uint32_t ulIPAddr, uint16_t usTelnetRemotePort, uint16_t usTelnetLocalPort, uint32_t ulSerialPort)
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
//    pState->eTelnetState = STATE_NORMAL;
    pState->ucFlags = (1 << OPT_FLAG_WILL_SUPPRESS_GA);
    pState->ulConnectionTimeout = 0;
    pState->ulMaxTimeout = getTelnetTimeout(ulSerialPort); // g_sParameters.sPort[ulSerialPort].ulTelnetTimeout;
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
    tTelnetSessionData *pState;

    DEBUG_MSG("TelnetListen port %d, UART %d\n", usTelnetPort, ulSerialPort);

    // Check the arguments.
    ASSERT(ulSerialPort < MAX_S2E_PORTS);
    ASSERT(usTelnetPort != 0);
    pState = &g_sTelnetSession[ulSerialPort];

    // Fill in the telnet state data structure for this session in listen
    // (in other words, server) mode.
    pState->pConnectPCB = NULL;
    pState->eTCPState = STATE_TCP_LISTEN;
//    pState->eTelnetState = STATE_NORMAL;
    pState->ucFlags = ((1 << OPT_FLAG_WILL_SUPPRESS_GA) | (1 << OPT_FLAG_SERVER));
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
    pcb = tcp_new();
    tcp_bind(pcb, IP_ADDR_ANY, usTelnetPort);
    pcb = tcp_listen(pcb);
    pState->pListenPCB = pcb;

    // Save the requested information and set the TCP callback functions
    // and arguments.
    tcp_arg(pcb, pState);
    tcp_accept(pcb, TelnetAccept);
}

#if false
//*****************************************************************************
//! Gets the current local port for a connection's telnet session.
//!
//! \param ulSerialPort is the serial port associated with this telnet session.
//!
//! This function returns the local port in use by the telnet session
//! associated with the given serial port.  If operating as a telnet server,
//! this port is the port that is listening for an incoming connection.  If
//! operating as a telnet client, this is the local port used to connect to
//! the remote server.
//!
//! \return None.
//*****************************************************************************
uint16_t TelnetGetLocalPort(uint32_t ulSerialPort)
{
    // Check the arguments.
    ASSERT(ulSerialPort < MAX_S2E_PORTS);

    return(g_sTelnetSession[ulSerialPort].usTelnetLocalPort);
}

//*****************************************************************************
//! Gets the current remote port for a connection's telnet session.
//!
//! \param ulSerialPort is the serial port associated with this telnet session.
//!
//! This function returns the remote port in use by the telnet session
//! associated with the given serial port.  If operating as a telnet server,
//! this function will return 0.  If operating as a telnet client, this is the
//! server port that the connection is using.
//!
//! \return None.
//*****************************************************************************
uint16_t TelnetGetRemotePort(uint32_t ulSerialPort)
{
    // Check the arguments.
    ASSERT(ulSerialPort < MAX_S2E_PORTS);

    return(g_sTelnetSession[ulSerialPort].usTelnetRemotePort);
}
#endif

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
    for(iPort = 0; iPort < MAX_S2E_PORTS; iPort++)
    {
        g_sTelnetSession[iPort].pConnectPCB = NULL;
        g_sTelnetSession[iPort].pListenPCB = NULL;
        g_sTelnetSession[iPort].eTCPState = STATE_TCP_IDLE;
//        g_sTelnetSession[iPort].eTelnetState = STATE_NORMAL;
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
        g_sTelnetSession[iPort].bLinkLost = false;
        g_sTelnetSession[iPort].ucConnectCount = 0;
        g_sTelnetSession[iPort].ucReconnectCount = 0;
        g_sTelnetSession[iPort].ucErrorCount = 0;
        g_sTelnetSession[iPort].eLastErr = ERR_OK;
    }
}

//*****************************************************************************
//! Handles periodic task for telnet sessions.
//!
//! This function is called periodically from the lwIP timer thread context.
//! This function will handle transferring data between the UART and the
//! the telnet sockets.  The time period for this should be tuned to the UART
//! ring buffer sizes to maintain optimal throughput.
//!
//! \return None.
//*****************************************************************************
void
TelnetHandler(void)
{
    long lCount, lIndex;
    static uint8_t pucTemp[PBUF_POOL_BUFSIZE];
    int iLoop;
    SYS_ARCH_DECL_PROTECT(lev);
    uint8_t *pucData;
    tTelnetSessionData *pState;

    // Loop through the possible telnet sessions.
    for(iLoop = 0; iLoop < MAX_S2E_PORTS; iLoop++)
    {
        // Initialize the state pointer.
        pState = &g_sTelnetSession[iLoop];

        // If the telnet session is not connected, skip this port.
        if(pState->eTCPState != STATE_TCP_CONNECTED)
        {
            continue;
        }

#if defined(CONFIG_RFC2217_ENABLED)
        // Check to see if modem state options have changed.
        if(pState->ucLastModemState != pState->ucModemState)
        {
            // Save the current state for the next comparison.
            pState->ucLastModemState = pState->ucModemState;

            // Check to see if the modem state options have been negotiated,
            // and if they have changed.
            if((HWREGBITB(&pState->ucFlags, OPT_FLAG_WILL_RFC2217) == 1) &&
               (HWREGBITB(&pState->ucFlags, OPT_FLAG_DO_RFC2217) == 1))
            {
                // Check to see if the state change has been enabled.
                if(pState->ucModemState & pState->ucRFC2217ModemMask)
                {
                    lIndex = 0;
                    pucTemp[lIndex++] = TELNET_IAC;
                    pucTemp[lIndex++] = TELNET_SB;
                    pucTemp[lIndex++] = TELNET_OPT_RFC2217;

                    // Use the "Server to Client" notification value.
                    pucTemp[lIndex++] = (TELNET_C2S_NOTIFY_MODEMSTATE + 100);

                    pucTemp[lIndex++] = (pState->ucModemState &
                            pState->ucRFC2217ModemMask);
                    if((pState->ucModemState & pState->ucRFC2217ModemMask) ==
                            TELNET_IAC)
                    {
                        pucTemp[lIndex++] = TELNET_IAC;
                    }
                    pucTemp[lIndex++] = TELNET_IAC;
                    pucTemp[lIndex++] = TELNET_SE;

                    // Write the data.
                    tcp_write(pState->pConnectPCB, pucTemp, lIndex, 1);
                    tcp_output(pState->pConnectPCB);

                    // Reset the index.
                    lIndex = 0;
                }
            }
        }
#endif

        // While space is available in the serial output queue, process the
        // pbufs received on the telnet interface.
        while(!SerialSendFull(iLoop))
        {
            // Pop a pbuf off of the rx queue, if one is available, and we are
            // not already processing a pbuf.
            if(pState->pBufHead == NULL)
            {
                if(pState->iBufQRead != pState->iBufQWrite)
                {
                    SYS_ARCH_PROTECT(lev);
                    pState->pBufHead = pState->pBufQ[pState->iBufQRead];
                    pState->iBufQRead =
                        ((pState->iBufQRead + 1) % PBUF_POOL_SIZE);
                    pState->pBufCurrent = pState->pBufHead;
                    pState->ulBufIndex = 0;
                    SYS_ARCH_UNPROTECT(lev);
                }
            }

            // If there is no packet to be processed, break out of the loop.
            if(pState->pBufHead == NULL)
            {
                break;
            }

            // Setup the data pointer for the current buffer.
            pucData = pState->pBufCurrent->payload;

            // Process the next character in the buffer.
            TelnetProcessCharacter(pucData[pState->ulBufIndex], pState);

            // Increment to next data byte.
            pState->ulBufIndex++;

            // Check to see if we are at the end of the current buffer.  If so,
            // get the next pbuf in the chain.
            if(pState->ulBufIndex >= pState->pBufCurrent->len)
            {
                pState->pBufCurrent = pState->pBufCurrent->next;
                pState->ulBufIndex = 0;
            }

            // Check to see if we are at the end of the chain.  If so,
            // acknowledge this data as being consumed to open up the TCP
            // window.
            if((pState->pBufCurrent == NULL) && (pState->ulBufIndex == 0))
            {
                tcp_recved(pState->pConnectPCB, pState->pBufHead->tot_len);
                pbuf_free(pState->pBufHead);
                pState->pBufHead = NULL;
                pState->pBufCurrent = NULL;
                pState->ulBufIndex = 0;
            }
        }

        // Flush the TCP output buffer, in the event that data was
        // queued up by processing the incoming packet.
        tcp_output(pState->pConnectPCB);

        // If RFC2217 is enabled, and flow control has been set to suspended,
        // skip processing of this port.
#if CONFIG_RFC2217_ENABLED
        if(pState->ucRFC2217FlowControl == TELNET_C2S_FLOWCONTROL_SUSPEND)
        {
            continue;
        }
#endif

        // Process the RX ring buffer data if space is available in the
        // TCP output buffer.
        if(SerialReceiveAvailable(pState->ulSerialPort) &&
           tcp_sndbuf(pState->pConnectPCB) &&
           (pState->pConnectPCB->snd_queuelen < TCP_SND_QUEUELEN))
        {
            // Here, we have data, and we have space.  Set the total amount
            // of data we will process to the lesser of data available or
            // space available.
            lCount = (long)SerialReceiveAvailable(pState->ulSerialPort);
            if(tcp_sndbuf(pState->pConnectPCB) < lCount)
            {
                lCount = tcp_sndbuf(pState->pConnectPCB);
            }

            // While we have data remaining to process, continue in this
            // loop.
            while((lCount) &&
                  (pState->pConnectPCB->snd_queuelen < TCP_SND_QUEUELEN))
            {
                // First, reset the index into the local buffer.
                lIndex = 0;

                // Fill the local buffer with data while there is data
                // and/or space remaining.
                while(lCount && (lIndex < sizeof(pucTemp)))
                {
                    pucTemp[lIndex] = SerialReceive(pState->ulSerialPort);
                    lIndex++;
                    lCount--;
                }

                // Write the local buffer into the TCP buffer.
                tcp_write(pState->pConnectPCB, pucTemp, lIndex, 1);
            }

            // Flush the data that has been written into the TCP output
            // buffer.
            tcp_output(pState->pConnectPCB);
            pState->ulLastTCPSendTime = g_ulSystemTimeMS;
        }
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
    int iPort;

    // We don't care if the link is up, only if it goes down.
    if(bLinkStatusUp)
    {
        return;
    }

    // For every port, indicate that the link has been lost.
    for(iPort = 0; iPort < MAX_S2E_PORTS; iPort++)
    {
        g_sTelnetSession[iPort].bLinkLost = true;
    }
}
