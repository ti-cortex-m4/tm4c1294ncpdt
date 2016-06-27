/*------------------------------------------------------------------------------
uart.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "serial.h"
#include "uart.h"



static ulong GetBaudRate(uchar u)
{
  ASSERT(u < UART_COUNT);

  if (mibBaudRate[u] < BAUD_RATE_COUNT)
  {
    return mdwBaudRates[mibBaudRate[u]];
  }
  else
  {
    WARNING("%u: wrong baud rate %u", u, mibBaudRate[u]);
    return mdwBaudRates[BAUD_RATE_DEFAULT];
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

    default: WARNING("%u: wrong parity %u", u, mibParity[u]);
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

    default: WARNING("%u: wrong data bits %u", u, mibDataBits[u]);
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

    default: WARNING("%u: wrong stop bits %u", u, mibStopBits[u]);
             return UART_CONFIG_STOP_ONE;
  }
}


static void InitUART(uchar u, ulong dwClockFreq)
{
  ASSERT(u < UART_COUNT);

  ulong dwBaudRate = GetBaudRate(u);
  ulong dwConfig = (GetParityMask(u) | GetDataBitsMask(u) | GetStopBitsMask(u));
  UARTConfigSetExpClk(g_ulUARTBase[u], dwClockFreq, dwBaudRate, dwConfig);
}



static void InitUART0(ulong dwClockFreq, bool fDebugModeUART)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
  UARTTxIntModeSet(UART0_BASE, UART_TXINT_MODE_EOT);
  UARTFIFOEnable(UART0_BASE);

  if (!fDebugModeUART)
  {
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);

    InitUART(0, dwClockFreq);
  }
}


static void InitUART4(ulong dwClockFreq)
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

  InitUART(1, dwClockFreq);
}


static void InitUART3(ulong dwClockFreq)
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

  InitUART(2, dwClockFreq);
}


static void InitUART2(ulong dwClockFreq)
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

  InitUART(3, dwClockFreq);
}


static void InitUART1(ulong dwClockFreq)
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

  InitUART(4, dwClockFreq);
}



void InitUARTs(ulong dwClockFreq)
{
  InitUART0(dwClockFreq, (ibDebugMode == DEBUG_MODE_UART));
  InitUART4(dwClockFreq);
  InitUART3(dwClockFreq);
  InitUART2(dwClockFreq);
  InitUART1(dwClockFreq);
}
