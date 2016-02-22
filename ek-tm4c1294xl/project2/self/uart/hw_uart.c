/*------------------------------------------------------------------------------
HW_UART.Ñ


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "hw_uart.h"



static void InitUart(uchar u, ulong dwUartBase, ulong dwInterrupt, ulong dwSysClockFreq)
{
  ASSERT(u < UART_COUNT);

  UARTFIFOLevelSet(dwUartBase, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
  UARTTxIntModeSet(dwUartBase, UART_TXINT_MODE_EOT);
  UARTFIFOEnable(dwUartBase);

  IntEnable(dwInterrupt);
  UARTIntEnable(dwUartBase, UART_INT_RX | UART_INT_RT | UART_INT_TX);

  ulong dwConfig = (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
  UARTConfigSetExpClk(dwUartBase, dwSysClockFreq, GetBaudRate(u), dwConfig);
}



void InitUart0(ulong dwSysClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  InitUart(0, UART0_BASE, INT_UART0, dwSysClockFreq);
}


void InitUart4(ulong dwSysClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA2_U4RX);
  GPIOPinConfigure(GPIO_PA3_U4TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);

  InitUart(1, UART4_BASE, INT_UART4, dwSysClockFreq);
}


void InitUart3(ulong dwSysClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA4_U3RX);
  GPIOPinConfigure(GPIO_PA5_U3TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5);

  InitUart(2, UART3_BASE, INT_UART3, dwSysClockFreq);
}


void InitUart2(ulong dwSysClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA6_U2RX);
  GPIOPinConfigure(GPIO_PA7_U2TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);

  InitUart(3, UART2_BASE, INT_UART2, dwSysClockFreq);
}


void InitUart1(ulong dwSysClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

  GPIOPinConfigure(GPIO_PB0_U1RX);
  GPIOPinConfigure(GPIO_PB1_U1TX);
  GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  InitUart(4, UART1_BASE, INT_UART1, dwSysClockFreq);
}
