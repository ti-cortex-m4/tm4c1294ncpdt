/*------------------------------------------------------------------------------
serial_handler.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/uart.h"
#include "../uart/io_mode.h"
#include "serial.h"
#include "serial_handler.h"



//*****************************************************************************
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
//*****************************************************************************
static void SerialUARTIntHandler(uint32_t ulPort)
{
    uint32_t ulStatus;
    uint8_t ucChar;

    // Get the cause of the interrupt.
    ulStatus = UARTIntStatus(g_ulUARTBase[ulPort], true);

    // Clear the cause of the interrupt.
    UARTIntClear(g_ulUARTBase[ulPort], ulStatus);

    // See if there is data to be processed in the receive FIFO.
    if(ulStatus & (UART_INT_RT | UART_INT_RX))
    {
        // Loop while there are characters available in the receive FIFO.
        while(UARTCharsAvail(g_ulUARTBase[ulPort]))
        {
            // Get the next character from the receive FIFO.
            ucChar = UARTCharGet(g_ulUARTBase[ulPort]);

#ifdef PROTOCOL_TELNET
            // If Telnet protocol enabled, check for incoming IAC character,
            // and escape it.
            if((g_sParameters.sPort[ulPort].ucFlags &
                        PORT_FLAG_PROTOCOL) == PORT_PROTOCOL_TELNET)
            {
                // If this is a Telnet IAC character, write it twice.
                if((ucChar == TELNET_IAC) &&
                   (RingBufFree(&g_sRxBuf[ulPort]) >= 2))
                {
                    RingBufWriteOne(&g_sRxBuf[ulPort], ucChar);
                    RingBufWriteOne(&g_sRxBuf[ulPort], ucChar);
                }

                // If not a Telnet IAC character, only write it once.
                else if((ucChar != TELNET_IAC) &&
                        (RingBufFree(&g_sRxBuf[ulPort]) >= 1))
                {
                    RingBufWriteOne(&g_sRxBuf[ulPort], ucChar);
                }
            }

            // if not Telnet, then only write the data once.
            else
#endif

            {
                RingBufWriteOne(&g_sRxBuf[ulPort], ucChar);
            }
        }
    }

#ifdef SERIAL_FLOW_CONTROL
    // If flow control is enabled, check the status of the RX buffer to
    // determine if flow control GPIO needs to be asserted.
    if(g_sParameters.sPort[ulPort].ucFlowControl == SERIAL_FLOW_CONTROL_HW)
    {
        // If the ring buffer is down to less than 25% free, assert the
        // outbound flow control pin.
        if(RingBufFree(&g_sRxBuf[ulPort]) <
           (RingBufSize(&g_sRxBuf[ulPort]) / 4))
        {
            GPIOPinWrite(g_ulFlowOutBase[ulPort], g_ulFlowOutPin[ulPort],
                         g_ulFlowOutPin[ulPort]);
        }
    }
#endif

    // See if there is space to be filled in the transmit FIFO.
    if(ulStatus & UART_INT_TX)
    {
        // Loop while there is space in the transmit FIFO and characters to be
        // sent.
        while(!RingBufEmpty(&g_sTxBuf[ulPort]) &&
                UARTSpaceAvail(g_ulUARTBase[ulPort]))
        {
            // Write the next character into the transmit FIFO.
            UARTCharPut(g_ulUARTBase[ulPort], RingBufReadOne(&g_sTxBuf[ulPort]));
        }

        InputMode(ulPort);
    }
}



void UART0IntHandler(void)
{
  SerialUARTIntHandler(0);
}

void UART4IntHandler(void)
{
  SerialUARTIntHandler(1);
}

void UART3IntHandler(void)
{
  SerialUARTIntHandler(2);
}

void UART2IntHandler(void)
{
  SerialUARTIntHandler(3);
}

void UART1IntHandler(void)
{
  SerialUARTIntHandler(4);
}
