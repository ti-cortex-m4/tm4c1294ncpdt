/*------------------------------------------------------------------------------
uarts.c


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
#include "../kernel/log.h"
#include "uarts.h"



static ulong GetBaudRate(uchar u)
{
  ASSERT(u < UART_COUNT);

  if (mibBaudRate[u] < BAUD_RATE_COUNT)
  {
    return mdwBaudRates[mibBaudRate[u]];
  }
  else
  {
    CONSOLE("%u: WARNING baud rate %u", u, mibBaudRate[u]);
    return mdwBaudRates[DEFAULT_BAUD_RATE];
  }
}


static ulong GetParityMask(uchar u)
{
  ASSERT(u < UART_COUNT);

  switch(mibParity[u])
  {
    case 0: return UART_CONFIG_PAR_NONE;
    case 1: return UART_CONFIG_PAR_EVEN;
    case 2: return UART_CONFIG_PAR_ODD;
    case 3: return UART_CONFIG_PAR_ONE;
    case 4: return UART_CONFIG_PAR_ZERO;

    default: CONSOLE("%u: WARNING parity %u", u, mibParity[u]);
             return UART_CONFIG_PAR_NONE;
  }
}


static ulong GetDataBitsMask(uchar u)
{
  ASSERT(u < UART_COUNT);

  switch(mibDataBits[u])
  {
    case 0: return UART_CONFIG_WLEN_7;
    case 1: return UART_CONFIG_WLEN_8;

    default: CONSOLE("%u: WARNING data bits %u", u, mibDataBits[u]);
             return UART_CONFIG_WLEN_8;
  }
}


static ulong GetStopBitsMask(uchar u)
{
  ASSERT(u < UART_COUNT);

  switch(mibStopBits[u])
  {
    case 0: return UART_CONFIG_STOP_ONE;
    case 1: return UART_CONFIG_STOP_TWO;

    default: CONSOLE("%u: WARNING stop bits %u", u, mibStopBits[u]);
             return UART_CONFIG_STOP_ONE;
  }
}


static void InitUart(uchar u, ulong dwUart, ulong dwInterrupt, ulong dwClockFreq)
{
  ASSERT(u < UART_COUNT);

  UARTFIFOLevelSet(dwUart, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
  UARTTxIntModeSet(dwUart, UART_TXINT_MODE_EOT);
  UARTFIFOEnable(dwUart);

  IntEnable(dwInterrupt);
  UARTIntEnable(dwUart, UART_INT_RX | UART_INT_RT | UART_INT_TX);

  ulong dwBaudRate = GetBaudRate(u);
  ulong dwConfig = (GetParityMask(u) | GetDataBitsMask(u) | GetStopBitsMask(u));
  UARTConfigSetExpClk(dwUart, dwClockFreq, dwBaudRate, dwConfig);
}



static void InitUart0(ulong dwClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  InitUart(0, UART0_BASE, INT_UART0, dwClockFreq);
}


static void InitUart4(ulong dwClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA2_U4RX);
  GPIOPinConfigure(GPIO_PA3_U4TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);

  InitUart(1, UART4_BASE, INT_UART4, dwClockFreq);
}


static void InitUart3(ulong dwClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA4_U3RX);
  GPIOPinConfigure(GPIO_PA5_U3TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5);

  InitUart(2, UART3_BASE, INT_UART3, dwClockFreq);
}


static void InitUart2(ulong dwClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA6_U2RX);
  GPIOPinConfigure(GPIO_PA7_U2TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);

  InitUart(3, UART2_BASE, INT_UART2, dwClockFreq);
}


static void InitUart1(ulong dwClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

  GPIOPinConfigure(GPIO_PB0_U1RX);
  GPIOPinConfigure(GPIO_PB1_U1TX);
  GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  InitUart(4, UART1_BASE, INT_UART1, dwClockFreq);
}



void InitUarts(ulong dwClockFreq)
{
  if (ibDebugMode != DEBUG_MODE_UART)
  {
    InitUart0(dwClockFreq);
  }

  InitUart4(dwClockFreq);
  InitUart3(dwClockFreq);
  InitUart2(dwClockFreq);
  InitUart1(dwClockFreq);
}
