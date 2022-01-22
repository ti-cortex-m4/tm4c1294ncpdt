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
//! \param ucPort is the UART port number to be accessed.
//!
//! This function checks to see if there is room on the UART transmit buffer
//! for additional data.
//!
//! \return Returns the number of bytes available in the serial transmit ring
//! buffer.
//*****************************************************************************
bool SerialSendFull(uint8_t ucPort)
{
    // Check the arguments.
    ASSERT(ucPort < UART_COUNT);

    // Return the number of bytes available in the tx ring buffer.
    return(RingBufFull(&g_sTxBuf[ucPort]));
}



//*****************************************************************************
//! Sends a character to the UART.
//!
//! \param ucPort is the UART port number to be accessed.
//! \param ucChar is the character to be sent.
//!
//! This function sends a character to the UART.  The character will either be
//! directly written into the UART FIFO or into the UART transmit buffer, as
//! appropriate.
//!
//! \return None.
//*****************************************************************************
void SerialSend(uint8_t ucPort, uint8_t ucChar)
{
    // Check the arguments.
    ASSERT(ucPort < UART_COUNT);

    // Disable the UART transmit interrupt while determining how to handle this
    // character.  Failure to do so could result in the loss of this character,
    // or stalled output due to this character being placed into the UART
    // transmit buffer but never transferred out into the UART FIFO.
    UARTIntDisable(g_ulUARTBase[ucPort], UART_INT_TX);

#if 0
    // See if the transmit buffer is empty and there is space in the FIFO.
    if(RingBufEmpty(&g_sTxBuf[ucPort]) && (UARTSpaceAvail(g_ulUARTBase[ucPort])))
    {
        // Write this character directly into the FIFO.
        UARTCharPut(g_ulUARTBase[ucPort], ucChar);
    }

    // See if there is room in the transmit buffer.
    else
#endif
    if(!RingBufFull(&g_sTxBuf[ucPort]))
    {
        // Put this character into the transmit buffer.
        RingBufWriteOne(&g_sTxBuf[ucPort], ucChar);
    }

    // Enable the UART transmit interrupt.
    UARTIntEnable(g_ulUARTBase[ucPort], UART_INT_TX);
    IntPendSet(g_ulIntUART[ucPort]);
}
