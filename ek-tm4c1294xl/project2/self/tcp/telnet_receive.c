/*------------------------------------------------------------------------------
telnet_receive,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "lwip/sys.h"
#include "../kernel/tasks.h"
#include "../kernel/log.h"
#include "../uart/customer_settings_1.h"
#include "tcp_errors.h"
#include "telnet.h"
#include "telnet_open.h"
#include "telnet_receive.h"



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
err_t TelnetReceive(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
    tState *pState = arg;
    SYS_ARCH_DECL_PROTECT(lev);

#if 0
    CONSOLE("%u: receive 0x%08x, 0x%08x, 0x%08x, %d\n", pState->ucSerialPort, arg, pcb, p, err);
#else
    CONSOLE("%u: receive error=%d\n", pState->ucSerialPort, err);
#endif

    // Place the incoming packet onto the queue if there is space.
    if((err == ERR_OK) && (p != NULL))
    {
        // This should be done in a protected/critical section.
        SYS_ARCH_PROTECT(lev);

        // Do we have space in the queue?
        int iNextWrite = ((pState->iBufQWrite + 1) % PBUF_POOL_SIZE);
        if(iNextWrite == pState->iBufQRead)
        {
            // The queue is full - discard the pbuf and return since we can't handle it just now.
            CONSOLE("%u: WARNING queue is full - discard data\n", pState->ucSerialPort);

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
        CONSOLE("%u: received NULL packet - close connection\n", pState->ucSerialPort);

        // Clear out all of the TCP callbacks.
        tcp_arg(pcb, NULL);
        tcp_sent(pcb, NULL);
        tcp_recv(pcb, NULL);
        tcp_err(pcb, NULL);
        tcp_poll(pcb, NULL, 1);

        // Close the TCP connection.
        err = tcp_close(pcb);
        if (err != ERR_OK)
        {
           WARNING("%u: TelnetReceive.tcp_close failed, error=%d\n", pState->ucSerialPort, err);
           ErrorTCPOperation(pState->ucSerialPort, err, TCP_CLOSE_RECEIVE);
        }

        // Clear out any pbufs associated with this session.
        TelnetFreePbufs(pState);

        // Clear out the telnet session PCB.
        pState->pConnectPCB = NULL;

        // If we don't have a listen PCB, then we are in client mode, and should try to reconnect.
        if(pState->pListenPCB == NULL)
        {
            CONSOLE("%u: reopen client connection\n", pState->ucSerialPort);

            // Re-open the connection.
            TelnetOpen(pState->ulTelnetRemoteIP, pState->usTelnetRemotePort, pState->ucSerialPort);
        }
        else
        {
            CONSOLE("%u: re-listen server connection\n", pState->ucSerialPort);

            // Revert to listening state.
            pState->eTCPState = STATE_TCP_LISTEN;
        }
    }

    CustomerSettings1_TelnetReceive(pState->ucSerialPort);

    return(ERR_OK);
}
