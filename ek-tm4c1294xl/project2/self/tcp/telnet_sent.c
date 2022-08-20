/*------------------------------------------------------------------------------
telnet_sent.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "../kernel/log.h"
#include "telnet.h"
#include "telnet_sent.h"



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

    CONSOLE("[%u] sent 0x%08x, 0x%08x, %d\n", pState->ucSerialPort, arg, pcb, len);

    // Reset the connection timeout.
    pState->ulConnectionTimeout = 0;

    return(ERR_OK);
}
