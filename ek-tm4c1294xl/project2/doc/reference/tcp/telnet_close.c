/*------------------------------------------------------------------------------
telnet_close,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "../kernel/log.h"
#include "tcp_errors.h"
#include "telnet.h"
#include "telnet_close.h"



err_t TelnetCloseClient(uint8_t ucSerialPort)
{
    ASSERT(ucSerialPort < UART_COUNT);
    tState *pState = &g_sState[ucSerialPort];

    CONSOLE("%u: close client\n", pState->ucSerialPort);

    // If we have a connect PCB, close it down.
    if(pState->pConnectPCB != NULL)
    {
        CONSOLE("%u: closing client data 0x%08x\n", pState->ucSerialPort, pState->pConnectPCB);

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

    // Reset the session data for this port.
    pState->pConnectPCB = NULL;
    pState->pListenPCB = NULL;
    pState->eTCPState = STATE_TCP_IDLE;
    pState->ulConnectionTimeout = 0;
    pState->ulMaxTimeout = 0;
    pState->ucSerialPort = ucSerialPort;
    pState->iBufQRead = 0;
    pState->iBufQWrite = 0;
    pState->pBufHead = NULL;
    pState->pBufCurrent = NULL;
    pState->ulBufIndex = 0;
    pState->ulLastTCPSendTime = 0;
    pState->bLinkLost = false;

    return(ERR_ABRT);
}


void TelnetCloseServer(struct tcp_pcb *pcb, uint8_t ucSerialPort)
{
    ASSERT(ucSerialPort < UART_COUNT);
    tState *pState = &g_sState[ucSerialPort];

    CONSOLE("%u: close server\n", pState->ucSerialPort);

    // If we have a listen PCB, close it down as well.
    if(pState->pListenPCB != NULL)
    {
        CONSOLE("%u: closing server data 0x%08x\n", pState->ucSerialPort, pState->pListenPCB);

        // Clear out all of the TCP callbacks.
        tcp_arg(pcb, NULL);
        tcp_sent(pcb, NULL);
        tcp_recv(pcb, NULL);
        tcp_err(pcb, NULL);
        tcp_poll(pcb, NULL, 1);

        // Close the TCP connection.
        err_t err = tcp_close(pState->pListenPCB);
        if (err != ERR_OK)
        {
            WARNING("%u: TelnetCloseServer.tcp_close failed, error=%d\n", pState->ucSerialPort, err);
            ErrorTCPOperation(pState->ucSerialPort, err, TCP_CLOSE_CLOSE);
        }

        // Clear out any pbufs associated with this session.
        TelnetFreePbufs(pState);
    }

    // Reset the session data for this port.
    pState->pConnectPCB = NULL;
//    pState->pListenPCB = NULL; TODO ???
//    pState->eTCPState = STATE_TCP_IDLE; TODO ???
    pState->ulConnectionTimeout = 0;
    pState->ulMaxTimeout = 0;
    pState->ucSerialPort = ucSerialPort;
    pState->iBufQRead = 0;
    pState->iBufQWrite = 0;
    pState->pBufHead = NULL;
    pState->pBufCurrent = NULL;
    pState->ulBufIndex = 0;
    pState->ulLastTCPSendTime = 0;
    pState->bLinkLost = false;
}

#if 0

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
void
TelnetClose(uint32_t ulSerialPort)
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
    pState->eTelnetState = STATE_NORMAL;
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
#if CONFIG_RFC2217_ENABLED
    pState->eRFC2217State = STATE_2217_GET_DATA;
    pState->ucRFC2217Command = 0;
    pState->ulRFC2217Value = 0;
    pState->ucRFC2217Index = 0;
    pState->ucRFC2217IndexMax = 0;
    pState->ucRFC2217FlowControl = 0;
    pState->ucRFC2217ModemMask = 0;
    pState->ucRFC2217LineMask = 0;
    pState->ucLastModemState = 0;
    pState->ucModemState = 0;
#endif
    pState->bLinkLost = false;
}

#endif

