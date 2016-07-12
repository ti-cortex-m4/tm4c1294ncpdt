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
//! \param ucSerialPort is the serial port associated with this telnet session.
//!
//! This function is called when the the Telnet/TCP session associated with
//! the specified serial port is to be closed.
//!
//! \return None.
//*****************************************************************************
void TelnetClose(uint8_t ucSerialPort)
{
    ASSERT(ucSerialPort < UART_COUNT);
    tState *pState = &g_sState[ucSerialPort];

    CONSOLE("%u: close\n", pState->ucSerialPort);

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

    // If we have a listen PCB, close it down as well.
    if(pState->pListenPCB != NULL)
    {
        CONSOLE("%u: closing server data 0x%08x\n", pState->ucSerialPort, pState->pListenPCB);

        // Close the TCP connection.
        tcp_close(pState->pListenPCB);

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
}

#endif

