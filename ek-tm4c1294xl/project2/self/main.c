/*------------------------------------------------------------------------------
MAIN.C


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
#include "settings.h"
#include "settings2.h"
#include "systick.h"
#include "timer1.h"
#include "uart/uart.h"
#include "uart/log.h"
#include "uart/serial.h"
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
  InitLog();

  LOG(("init\n"));

  //
  // Make sure the main oscillator is enabled because this is required by
  // the PHY.  The system must have a 25MHz crystal attached to the OSC
  // pins. The SYSCTL_MOSC_HIGHFREQ parameter is used when the crystal
  // frequency is 10MHz or higher.
  //
  SysCtlMOSCConfigSet(SYSCTL_MOSC_HIGHFREQ);

  //
  // Run from the PLL at 120 MHz.
  //
  ulong dwSysClockFreq = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

  //
  // Configure the device pins.
  //
  PinoutSet(true, false);

  //
  // Configure Port N1 for as an output for the animation LED.
  //
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);

  //
  // Initialize LED to OFF (0)
  //
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, ~GPIO_PIN_1);

  //
  // Configure the hardware MAC address for Ethernet Controller filtering of
  // incoming packets.  The MAC address will be stored in the non-volatile
  // USER0 and USER1 registers.
  //
  ulong dwUser0, dwUser1;
  FlashUserGet(&dwUser0, &dwUser1);

  dwUser0 = 0x00B61A00; // TODO MAC
  dwUser1 = 0x00FCC502+1;

  if((dwUser0 == 0xFFFFFFFF) || (dwUser1 == 0xFFFFFFFF))
  {
      //
      // We should never get here.  This is an error if the MAC address has
      // not been programmed into the device.  Exit the program.
      // Let the user know there is no MAC address
      //
      while(1)
      {
        LOG(("No MAC address\n"));
      }
  }

  //
  // Convert the 24/24 split MAC address from NV ram into a 32/16 split MAC
  // address needed to program the hardware registers, then program the MAC
  // address into the Ethernet Controller registers.
  //
  pbMAC[0] = ((dwUser0 >>  0) & 0xFF);
  pbMAC[1] = ((dwUser0 >>  8) & 0xFF);
  pbMAC[2] = ((dwUser0 >> 16) & 0xFF);
  pbMAC[3] = ((dwUser1 >>  0) & 0xFF);
  pbMAC[4] = ((dwUser1 >>  8) & 0xFF);
  pbMAC[5] = ((dwUser1 >> 16) & 0xFF);

  InitSettings();

  lwIPInit(dwSysClockFreq, pbMAC, dwIP, dwGateway, dwNetmask, IPADDR_USE_STATIC);

  InitUdpLog();

  InitUDP_Handler();
//  InitTCP_Handler();

  // Initialize the serial port module.
  SerialInit();

  // Initialize the telnet module.
  TelnetInit();

  InitSysTick(dwSysClockFreq);
  InitUART(dwSysClockFreq);
  InitTimer1(dwSysClockFreq);

  //
  // Set the interrupt priorities.  We set the SysTick interrupt to a higher
  // priority than the Ethernet interrupt to ensure that the file system
  // tick is processed if SysTick occurs while the Ethernet handler is being
  // processed.  This is very likely since all the TCP/IP and HTTP work is
  // done in the context of the Ethernet interrupt.
  //
  IntPrioritySet(INT_EMAC0, ETHERNET_INT_PRIORITY);
  IntPrioritySet(FAULT_SYSTICK, SYSTICK_INT_PRIORITY);

#if true
  uint8_t u;
  for(u = 0; u < UART_COUNT; u++)
  {
      // Are we to operate as a telnet server?
      if(isServer(u))
      {
          // Yes - start listening on the required port.
//           TelnetListen(g_sParameters.sPort[ibPort].usTelnetLocalPort, u);
          ASSERT(false);
      }
      else
      {
          // No - we are a client so initiate a connection to the desired IP address using the configured ports.
//          TelnetOpen(g_sParameters.sPort[u].ulTelnetIPAddr,
//                     g_sParameters.sPort[u].usTelnetRemotePort,
//                     g_sParameters.sPort[u].usTelnetLocalPort, u);
          TelnetOpen(mdwDestinationIP[u], mwDestinationPort[u], 1, u);
      }
  }
#endif
  IntMasterEnable();

  LOG(("start\n"));

  while(1)
  {
//    SysCtlDelay(100*SysCtlClockGet());
//    stats_display();
  }
}
