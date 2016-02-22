/*------------------------------------------------------------------------------
MAIN,C


------------------------------------------------------------------------------*/

#include "main.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/flash.h"
#include "utils/lwiplib_patched.h"
#include "drivers/pinout.h"
#include "kernel/log.h"
#include "kernel/tasks.h"
#include "settings.h"
#include "systick.h"
#include "timer1.h"
#include "uart/uart.h"
#include "uart/serial.h"
#include "uart/uart_log.h"
#include "uart/io_mode.h"
#include "udp/udp_log.h"
#include "udp/udp_handler.h"
#include "tcp/tcp_handler.h"
#include "tcp/telnet.h"



//
// Interrupt priority definitions.  The top 3 bits of these values are
// significant with lower values indicating higher priority interrupts.
//
#define SYSTICK_INT_PRIORITY    0x80
#define ETHERNET_INT_PRIORITY   0xC0


//*****************************************************************************
//! Keeps track of elapsed time in milliseconds.
//*****************************************************************************
uint32_t g_ulSystemTimeMS = 0;



//*****************************************************************************
//! Handles the Ethernet interrupt hooks for the client software.
//!
//! This function will run any handlers that are required to run in the
//! Ethernet interrupt context.  All the actual TCP/IP processing occurs within
//! this function (since lwIP is not re-entrant).
//!
//! \return None.
//*****************************************************************************
void    lwIPHostTimerHandler(void)
{
    // Service the telnet module.
    TelnetHandler();
}



int     main(void)
{
  // Make sure the main oscillator is enabled because this is required by
  // the PHY.  The system must have a 25MHz crystal attached to the OSC
  // pins. The SYSCTL_MOSC_HIGHFREQ parameter is used when the crystal
  // frequency is 10MHz or higher.
  SysCtlMOSCConfigSet(SYSCTL_MOSC_HIGHFREQ);

  // Run from the PLL at 120 MHz.
  ulong dwSysClockFreq = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

  // Configure the device pins.
  PinoutSet(true, false);

  // Configure Port N1 for as an output for the animation LED.
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);

  // Initialize LED to OFF (0)
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, ~GPIO_PIN_1);

  InitSettings();

  InitUartLog(dwSysClockFreq);

  pbMAC[0] = 0x00;
  pbMAC[1] = 0x1B;
  pbMAC[2] = 0xB6;
  pbMAC[3] = 1;
  pbMAC[4] = wSerialNumber / 0x100;
  pbMAC[5] = wSerialNumber % 0x100;

  lwIPInit(dwSysClockFreq, pbMAC, dwIP, dwGateway, dwNetmask, IPADDR_USE_STATIC);

  InitUdpLog();

  InitUdpHandler();
//  InitTCP_Handler();

  SerialInit();
  TelnetInit();

  InitSysTick(dwSysClockFreq);
  InitUART(dwSysClockFreq);
  InitIoModes();
  InitTimer1(dwSysClockFreq);

  // Set the interrupt priorities.  We set the SysTick interrupt to a higher
  // priority than the Ethernet interrupt to ensure that the file system
  // tick is processed if SysTick occurs while the Ethernet handler is being
  // processed.  This is very likely since all the TCP/IP and HTTP work is
  // done in the context of the Ethernet interrupt.
  IntPrioritySet(INT_EMAC0, ETHERNET_INT_PRIORITY);
  IntPrioritySet(FAULT_SYSTICK, SYSTICK_INT_PRIORITY);

  InitConnections();

  IntMasterEnable();

  CONSOLE("start\n");

  while (true)
  {
    SysCtlDelay(SysCtlClockGet());

    TaskConnections();
    TaskLwIpDebug();
  }
}
