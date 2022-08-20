/*------------------------------------------------------------------------------
serial_handler.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/uart.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "io_mode.h"
#include "serial.h"
#include "modem.h"
#include "modem_to_server.h"
#include "server_to_modem.h"
#include "serial_handler.h"
#include "customer_settings_1.h"



//*****************************************************************************
//! Handles the UART interrupt.
//!
//! \param ucPort is the serial port number to be accessed.
//!
//! This function is called when either of the UARTs generate an interrupt.
//! An interrupt will be generated when data is received and when the transmit
//! FIFO becomes half empty.  The transmit and receive FIFOs are processed as
//! appropriate.
//!
//! \return None.
//*****************************************************************************
static void SerialUARTIntHandler(uint8_t ucPort)
{
    // Get the cause of the interrupt.
    uint32_t ulStatus = UARTIntStatus(g_ulUARTBase[ucPort], true);

    // Clear the cause of the interrupt.
    UARTIntClear(g_ulUARTBase[ucPort], ulStatus);

    // See if there is data to be processed in the receive FIFO.
    if(ulStatus & (UART_INT_RT | UART_INT_RX))
    {
        // Loop while there are characters available in the receive FIFO.
        while(UARTCharsAvail(g_ulUARTBase[ucPort]))
        {
            // Get the next character from the receive FIFO.
            uint8_t ucChar = UARTCharGet(g_ulUARTBase[ucPort]);

#ifdef PROTOCOL_TELNET
            // If Telnet protocol enabled, check for incoming IAC character,
            // and escape it.
            if((g_sParameters.sPort[ucPort].ucFlags &
                        PORT_FLAG_PROTOCOL) == PORT_PROTOCOL_TELNET)
            {
                // If this is a Telnet IAC character, write it twice.
                if((ucChar == TELNET_IAC) &&
                   (RingBufFree(&g_sRxBuf[ucPort]) >= 2))
                {
                    RingBufWriteOne(&g_sRxBuf[ucPort], ucChar);
                    RingBufWriteOne(&g_sRxBuf[ucPort], ucChar);
                }

                // If not a Telnet IAC character, only write it once.
                else if((ucChar != TELNET_IAC) &&
                        (RingBufFree(&g_sRxBuf[ucPort]) >= 1))
                {
                    RingBufWriteOne(&g_sRxBuf[ucPort], ucChar);
                }
            }

            // if not Telnet, then only write the data once.
            else
#endif

            {
                if (fDataDebugFlag)
                  CONSOLE("[%u] from UART %02X\n", ucPort, ucChar);

                if (IsModemModeCommand(ucPort))
                  ProcessModemModeCommand(ucPort, ucChar);
                else
                {
                  ProcessModemModeData(ucPort, ucChar);
                  RingBufWriteOne(&g_sRxBuf[ucPort], ucChar);
                }

                ProcessModemToServerData(ucPort);
                ProcessServerToModemData(ucPort, ucChar);
            }
        }
    }

#ifdef SERIAL_FLOW_CONTROL
    // If flow control is enabled, check the status of the RX buffer to
    // determine if flow control GPIO needs to be asserted.
    if(g_sParameters.sPort[ucPort].ucFlowControl == SERIAL_FLOW_CONTROL_HW)
    {
        // If the ring buffer is down to less than 25% free, assert the
        // outbound flow control pin.
        if(RingBufFree(&g_sRxBuf[ucPort]) <
           (RingBufSize(&g_sRxBuf[ucPort]) / 4))
        {
            GPIOPinWrite(g_ulFlowOutBase[ucPort], g_ulFlowOutPin[ucPort],
                         g_ulFlowOutPin[ucPort]);
        }
    }
#endif

    // See if there is space to be filled in the transmit FIFO.
    if(((ulStatus & UART_INT_TX) != 0) || (ulStatus == 0))
    {
        bool fInMode = true;

        // Loop while there is space in the transmit FIFO and characters to be sent.
        while(!RingBufEmpty(&g_sTxBuf[ucPort]) && UARTSpaceAvail(g_ulUARTBase[ucPort]))
        {
            uint8_t ucChar = RingBufReadOne(&g_sTxBuf[ucPort]);

            if (fDataDebugFlag)
              CONSOLE("[%u] to UART %02X\n", ucPort, ucChar);

            // Write the next character into the transmit FIFO.
            UARTCharPut(g_ulUARTBase[ucPort], ucChar);

            CustomerSettings1_SerialProcessCharacter(ucPort, ucChar);

            mcwUARTTxOut[ucPort]--;

            fInMode = false;
        }

        if((ulStatus & UART_INT_TX) != 0)
        {
          if ((mcwUARTTxOut[ucPort] == 0) && (fInMode)) {
              InMode(ucPort);
          }
        }
    }
}



void UART0IntHandler(void)
{
  SerialUARTIntHandler(0);
}

void UART4IntHandler(void)
{
#ifndef SINGLE_UART
  SerialUARTIntHandler(1);
#endif
}

void UART3IntHandler(void)
{
#ifndef SINGLE_UART
  SerialUARTIntHandler(2);
#endif
}

void UART2IntHandler(void)
{
#ifndef SINGLE_UART
  SerialUARTIntHandler(3);
#endif
}

void UART1IntHandler(void)
{
#ifndef SINGLE_UART
  SerialUARTIntHandler(4);
#endif
}
