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



void InitUart(uchar u, ulong dwUartBase, ulong dwInterrupt, ulong dwSysClockFreq)
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


void    InitUart0(ulong dwSysClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
  UARTTxIntModeSet(UART0_BASE, UART_TXINT_MODE_EOT);
  UARTFIFOEnable(UART0_BASE);

  IntEnable(INT_UART0);
  UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);

  UARTConfigSetExpClk(UART0_BASE, dwSysClockFreq, GetBaudRate(0), (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}


void    InitUart4(ulong dwSysClockFreq)
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

  UARTConfigSetExpClk(UART4_BASE, dwSysClockFreq, GetBaudRate(1), (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}


void    InitUart3(ulong dwSysClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA4_U3RX);
  GPIOPinConfigure(GPIO_PA5_U3TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5);

  UARTFIFOLevelSet(UART3_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
  UARTTxIntModeSet(UART3_BASE, UART_TXINT_MODE_EOT);
  UARTFIFOEnable(UART3_BASE);

  IntEnable(INT_UART3);
  UARTIntEnable(UART3_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);

  UARTConfigSetExpClk(UART3_BASE, dwSysClockFreq, GetBaudRate(2), (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}


void    InitUart2(ulong dwSysClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA6_U2RX);
  GPIOPinConfigure(GPIO_PA7_U2TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);

  UARTFIFOLevelSet(UART2_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
  UARTTxIntModeSet(UART2_BASE, UART_TXINT_MODE_EOT);
  UARTFIFOEnable(UART2_BASE);

  IntEnable(INT_UART2);
  UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);

  UARTConfigSetExpClk(UART2_BASE, dwSysClockFreq, GetBaudRate(3), (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}


void    InitUart1(ulong dwSysClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

  GPIOPinConfigure(GPIO_PB0_U1RX);
  GPIOPinConfigure(GPIO_PB1_U1TX);
  GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
  UARTTxIntModeSet(UART1_BASE, UART_TXINT_MODE_EOT);
  UARTFIFOEnable(UART1_BASE);

  IntEnable(INT_UART1);
  UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);

  UARTConfigSetExpClk(UART1_BASE, dwSysClockFreq, GetBaudRate(4), (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}
