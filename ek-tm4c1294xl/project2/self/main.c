/*------------------------------------------------------------------------------
MAIN,C


------------------------------------------------------------------------------*/

#include "main.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib.patched/sysctl_patched.h"
#include "driverlib/flash.h"
#include "driverlib/pin_map.h"
#include "utils/lwiplib_patched.h"
#include "kernel/log.h"
#include "kernel/tasks.h"
#include "kernel/settings.h"
#include "kernel/console_version.h"
#include "kernel/console_pins.h"
#include "hardware/gpio.h"
#include "hardware/led.h"
#include "hardware/sys_tick.h"
#include "hardware/timer1.h"
#include "hardware/timer2.h"
#include "hardware/delay.h"
#include "hardware/rom.h"
#include "hardware/uart_loader.h"
#include "hardware/watchdog.h"
#include "uart/uart.h"
#include "uart/serial.h"
#include "uart/uart_log.h"
#include "uart/io_mode.h"
#include "uart/modem.h"
#include "uart/modem_to_server.h"
#include "uart/server_to_modem.h"
#include "uart/customer_settings_1.h"
#include "udp/udp_log.h"
#include "udp/udp_handler.h"
#include "tcp/telnet.h"
#include "tcp/tcp_echo.h"



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
//
//! A flag indicating the current link status.
//
//*****************************************************************************
volatile bool g_bLinkStatusUp = false;



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
    // Get the current link status and see if it has changed.
    bool bLinkStatusUp = GPIOPinRead(GPIO_PORTK_BASE, GPIO_PIN_4) ? false : true;

    if(bLinkStatusUp != g_bLinkStatusUp)
    {
        // Save the new link status.
        g_bLinkStatusUp = bLinkStatusUp;

        // Notify the Telnet module that the link status has changed.
        TelnetNotifyLinkStatus(g_bLinkStatusUp);
    }

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
  ulong dwClockFreq = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

  InitGPIO();
//  InitLEDs();
  InitROM();
  InitUARTLoader();

  InitSettings();
  InitUARTLog(dwClockFreq);

  mbMAC[0] = 0x00;
  mbMAC[1] = 0x1B;
  mbMAC[2] = 0xB6;
  mbMAC[3] = 1;
  mbMAC[4] = wSerialNumber / 0x100;
  mbMAC[5] = wSerialNumber % 0x100;

  ASSERT(dwIP != 0);
  lwIPInit(dwClockFreq, mbMAC, dwIP, dwNetmask, dwGateway, IPADDR_USE_STATIC);

  InitUDPLog();
  InitEthernetLEDs();

  // Set the link status based on the LED0 signal (which defaults to link status in the PHY).
  g_bLinkStatusUp = GPIOPinRead(GPIO_PORTK_BASE, GPIO_PIN_4) ? false : true;

  SerialInit();
  TelnetInit();
  InitTCPEcho();

  InitUDPHandler();
  InitSysTick(dwClockFreq);
  InitUARTs(dwClockFreq);
  InitIOModes();
  InitModem();
  InitModemToServer();
  InitServerToModem();
  InitTimer1(dwClockFreq);
  InitTimer2(dwClockFreq);
  InitCustomerSettings1();

  // Set the interrupt priorities.  We set the SysTick interrupt to a higher
  // priority than the Ethernet interrupt to ensure that the file system
  // tick is processed if SysTick occurs while the Ethernet handler is being
  // processed.  This is very likely since all the TCP/IP and HTTP work is
  // done in the context of the Ethernet interrupt.
  IntPrioritySet(INT_EMAC0, ETHERNET_INT_PRIORITY);
  IntPrioritySet(FAULT_SYSTICK, SYSTICK_INT_PRIORITY);

  StartConnections();

  IntMasterEnable();

  ConsoleVersion();
  ConsolePins();
  InitWatchdog();
  InitLEDs_After();

  while (true)
  {
    DelayMilliSecond(100);

    RunConnections();
    RunLwipDebug();

    ResetWatchdog();
  }
}
