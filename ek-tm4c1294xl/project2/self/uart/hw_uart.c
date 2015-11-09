/*------------------------------------------------------------------------------
HW_UART.Ñ


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "hw_uart.h"



void    InitUART4(ulong dwSysClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA2_U4RX);
  GPIOPinConfigure(GPIO_PA3_U4TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);

  UARTFIFOLevelSet(UART4_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
  UARTTxIntModeSet(UART4_BASE, UART_TXINT_MODE_EOT);
  UARTFIFOEnable(UART4_BASE);

  IntEnable(INT_UART4);
  UARTIntEnable(UART4_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);

  UARTConfigSetExpClk(UART4_BASE, dwSysClockFreq, 57600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}
