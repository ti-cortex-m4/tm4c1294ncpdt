/*------------------------------------------------------------------------------
SERIAL.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/ringbuf.h"



//*****************************************************************************
//! The ring buffers used to hold characters received from the UARTs.
//*****************************************************************************
static tRingBufObject g_sRxBuf[MAX_S2E_PORTS];

//*****************************************************************************
//! The ring buffers used to hold characters to be sent to the UARTs.
//*****************************************************************************
static tRingBufObject g_sTxBuf[MAX_S2E_PORTS];



#if false

//*****************************************************************************
//
//! Handles the UART interrupt.
//!
//! \param ulPort is the serial port number to be accessed.
//!
//! This function is called when either of the UARTs generate an interrupt.
//! An interrupt will be generated when data is received and when the transmit
//! FIFO becomes half empty.  The transmit and receive FIFOs are processed as
//! appropriate.
//!
//! \return None.
//
//*****************************************************************************
static void
SerialUARTIntHandler(uint32_t ulPort)
{
    uint32_t ulStatus;
    uint8_t ucChar;

    //
    // Get the cause of the interrupt.
    //
    ulStatus = UARTIntStatus(g_ulUARTBase[ulPort], true);

    //
    // Clear the cause of the interrupt.
    //
    UARTIntClear(g_ulUARTBase[ulPort], ulStatus);

    //
    // See if there is data to be processed in the receive FIFO.
    //
    if(ulStatus & (UART_INT_RT | UART_INT_RX))
    {
        //
        // Loop while there are characters available in the receive FIFO.
        //
        while(UARTCharsAvail(g_ulUARTBase[ulPort]))
        {
            //
            // Get the next character from the receive FIFO.
            //
            ucChar = UARTCharGet(g_ulUARTBase[ulPort]);

            //
            // If Telnet protocol enabled, check for incoming IAC character,
            // and escape it.
            //
            if((g_sParameters.sPort[ulPort].ucFlags &
                        PORT_FLAG_PROTOCOL) == PORT_PROTOCOL_TELNET)
            {
                //
                // If this is a Telnet IAC character, write it twice.
                //
                if((ucChar == TELNET_IAC) &&
                   (RingBufFree(&g_sRxBuf[ulPort]) >= 2))
                {
                    RingBufWriteOne(&g_sRxBuf[ulPort], ucChar);
                    RingBufWriteOne(&g_sRxBuf[ulPort], ucChar);
                }

                //
                // If not a Telnet IAC character, only write it once.
                //
                else if((ucChar != TELNET_IAC) &&
                        (RingBufFree(&g_sRxBuf[ulPort]) >= 1))
                {
                    RingBufWriteOne(&g_sRxBuf[ulPort], ucChar);
                }
            }

            //
            // if not Telnet, then only write the data once.
            //
            else
            {
                RingBufWriteOne(&g_sRxBuf[ulPort], ucChar);
            }
        }
    }

    //
    // If flow control is enabled, check the status of the RX buffer to
    // determine if flow control GPIO needs to be asserted.
    //
    if(g_sParameters.sPort[ulPort].ucFlowControl == SERIAL_FLOW_CONTROL_HW)
    {
        //
        // If the ring buffer is down to less than 25% free, assert the
        // outbound flow control pin.
        //
        if(RingBufFree(&g_sRxBuf[ulPort]) <
           (RingBufSize(&g_sRxBuf[ulPort]) / 4))
        {
            GPIOPinWrite(g_ulFlowOutBase[ulPort], g_ulFlowOutPin[ulPort],
                         g_ulFlowOutPin[ulPort]);
        }
    }

    //
    // See if there is space to be filled in the transmit FIFO.
    //
    if(ulStatus & UART_INT_TX)
    {
        //
        // Loop while there is space in the transmit FIFO and characters to be
        // sent.
        //
        while(!RingBufEmpty(&g_sTxBuf[ulPort]) &&
                UARTSpaceAvail(g_ulUARTBase[ulPort]))
        {
            //
            // Write the next character into the transmit FIFO.
            //
            UARTCharPut(g_ulUARTBase[ulPort],
                        RingBufReadOne(&g_sTxBuf[ulPort]));
        }
    }
}

//*****************************************************************************
//
//! Checks the availability of the serial port output buffer.
//!
//! \param ulPort is the UART port number to be accessed.
//!
//! This function checks to see if there is room on the UART transmit buffer
//! for additional data.
//!
//! \return Returns the number of bytes available in the serial transmit ring
//! buffer.
//
//*****************************************************************************
bool
SerialSendFull(uint32_t ulPort)
{
    //
    // Check the arguments.
    //
    ASSERT(ulPort < MAX_S2E_PORTS);

    //
    // Return the number of bytes available in the tx ring buffer.
    //
    return(RingBufFull(&g_sTxBuf[ulPort]));
}

//*****************************************************************************
//
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
//
//*****************************************************************************
void
SerialSend(uint32_t ulPort, uint8_t ucChar)
{
    //
    // Check the arguments.
    //
    ASSERT(ulPort < MAX_S2E_PORTS);

    //
    // Disable the UART transmit interrupt while determining how to handle this
    // character.  Failure to do so could result in the loss of this character,
    // or stalled output due to this character being placed into the UART
    // transmit buffer but never transferred out into the UART FIFO.
    //
    UARTIntDisable(g_ulUARTBase[ulPort], UART_INT_TX);

    //
    // See if the transmit buffer is empty and there is space in the FIFO.
    //
    if(RingBufEmpty(&g_sTxBuf[ulPort]) &&
       (UARTSpaceAvail(g_ulUARTBase[ulPort])))
    {
        //
        // Write this character directly into the FIFO.
        //
        UARTCharPut(g_ulUARTBase[ulPort], ucChar);
    }

    //
    // See if there is room in the transmit buffer.
    //
    else if(!RingBufFull(&g_sTxBuf[ulPort]))
    {
        //
        // Put this character into the transmit buffer.
        //
        RingBufWriteOne(&g_sTxBuf[ulPort], ucChar);
    }

    //
    // Enable the UART transmit interrupt.
    //
    UARTIntEnable(g_ulUARTBase[ulPort], UART_INT_TX);
}
#endif
//*****************************************************************************
//
//! Receives a character from the UART.
//!
//! \param ulPort is the UART port number to be accessed.
//!
//! This function receives a character from the relevant port's UART buffer.
//!
//! \return Returns -1 if no data is available or the oldest character held in
//! the receive ring buffer.
//
//*****************************************************************************
long SerialReceive(uint32_t ulPort)
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
//! \return The number of characters available in the ring buffer.
//*****************************************************************************
uint32_t SerialReceiveAvailable(uint32_t ulPort)
{
    // Check the arguments.
    ASSERT(ulPort < MAX_S2E_PORTS);

    // Return the value.
    return(RingBufUsed(&g_sRxBuf[ulPort]));
}
