#if 1
/*------------------------------------------------------------------------------
serial_send.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "serial.h"
#include "serial_send.h"



//*****************************************************************************
//! Checks the availability of the serial port output buffer.
//!
//! \param ulPort is the UART port number to be accessed.
//!
//! This function checks to see if there is room on the UART transmit buffer
//! for additional data.
//!
//! \return Returns the number of bytes available in the serial transmit ring
//! buffer.
//*****************************************************************************
bool
SerialSendFull(uint32_t ulPort)
{
    // Check the arguments.
    ASSERT(ulPort < MAX_S2E_PORTS);

    // Return the number of bytes available in the tx ring buffer.
    return(RingBufFull(&g_sTxBuf[ulPort]));
}

//*****************************************************************************
//! Sends a character to the UART.
//!
//! \param ulPort is the UART port number to be accessed.
//! \param ucChar is the character to be sent.
//!
//! This function sends a character to the UART.  The character will either be
//! directly written into the UART FIFO or into the UART transmit buffer, as
//! appropriate.
//!
//! \return None.
//*****************************************************************************
void
SerialSend(uint32_t ulPort, uint8_t ucChar)
{
    // Check the arguments.
    ASSERT(ulPort < MAX_S2E_PORTS);

    // Disable the UART transmit interrupt while determining how to handle this
    // character.  Failure to do so could result in the loss of this character,
    // or stalled output due to this character being placed into the UART
    // transmit buffer but never transferred out into the UART FIFO.
    UARTIntDisable(g_ulUARTBase[ulPort], UART_INT_TX);

    // See if the transmit buffer is empty and there is space in the FIFO.
    if(RingBufEmpty(&g_sTxBuf[ulPort]) &&
       (UARTSpaceAvail(g_ulUARTBase[ulPort])))
    {
        // Write this character directly into the FIFO.
        UARTCharPut(g_ulUARTBase[ulPort], ucChar);
    }

    // See if there is room in the transmit buffer.
    else if(!RingBufFull(&g_sTxBuf[ulPort]))
    {
        // Put this character into the transmit buffer.
        RingBufWriteOne(&g_sTxBuf[ulPort], ucChar);
    }

    // Enable the UART transmit interrupt.
    UARTIntEnable(g_ulUARTBase[ulPort], UART_INT_TX);
}

#endif