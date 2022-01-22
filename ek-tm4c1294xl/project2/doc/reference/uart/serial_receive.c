#if 0
/*------------------------------------------------------------------------------
serial_receive.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/uart.h"
#include "serial.h"
#include "serial_receive.h"



//*****************************************************************************
//! Receives a character from the UART.
//!
//! \param ulPort is the UART port number to be accessed.
//!
//! This function receives a character from the relevant port's UART buffer.
//!
//! \return Returns -1 if no data is available or the oldest character held in
//! the receive ring buffer.
//*****************************************************************************
long
SerialReceive(uint32_t ulPort)
{
    uint32_t ulData;

    // Check the arguments.
    ASSERT(ulPort < MAX_S2E_PORTS);

    // See if the receive buffer is empty and there is space in the FIFO.
    if(RingBufEmpty(&g_sRxBuf[ulPort]))
    {
        // Return -1 (EOF) to indicate no data available.
        return(-1);
    }

    // Read a single character.
    ulData = (long)RingBufReadOne(&g_sRxBuf[ulPort]);

    // If flow control is enabled, check the status of the RX buffer to
    // determine if flow control GPIO needs to be de-asserted.
    if(g_sParameters.sPort[ulPort].ucFlowControl == SERIAL_FLOW_CONTROL_HW)
    {
        // If the ring buffer is down to less than 25% used,
        // de-assert the outbound flow control pin.
        if((RingBufUsed(&g_sRxBuf[ulPort]) <
            (RingBufSize(&g_sRxBuf[ulPort]) / 4)) &&
           (g_ulSetFlowOutValue[ulPort] == 0))
        {
            GPIOPinWrite(g_ulFlowOutBase[ulPort], g_ulFlowOutPin[ulPort], 0);
        }
    }

    // Return the data that was read.
    return(ulData);
}

//*****************************************************************************
//! Returns number of characters available in the serial ring buffer.
//!
//! \param ulPort is the UART port number to be accessed.
//!
//! This function will return the number of characters available in the
//! serial ring buffer.
//!
//! \return The number of characters available in the ring buffer..
//*****************************************************************************
uint32_t
SerialReceiveAvailable(uint32_t ulPort)
{
    // Check the arguments.
    ASSERT(ulPort < MAX_S2E_PORTS);

    // Return the value.
    return(RingBufUsed(&g_sRxBuf[ulPort]));
}

#endif