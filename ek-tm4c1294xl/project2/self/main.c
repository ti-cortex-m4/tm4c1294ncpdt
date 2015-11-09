/*------------------------------------------------------------------------------
MAIN.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "settings.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/flash.h"
#include "driverlib/systick.h"
#include "utils/lwiplib_patched.h"
#include "drivers/pinout.h"
#include "timer1.h"
#include "uart/uart.h"
#include "udp/udp_handler.h"
#include "tcp/tcp_handler.h"



//
// Defines for setting up the system clock.
//
#define SYSTICKHZ               100
#define SYSTICKMS               (1000 / SYSTICKHZ)



//
// Interrupt priority definitions.  The top 3 bits of these values are
// significant with lower values indicating higher priority interrupts.
//
#define SYSTICK_INT_PRIORITY    0x80
#define ETHERNET_INT_PRIORITY   0xC0



//
// Required by lwIP library to support any host-related timer functions.
//
void    lwIPHostTimerHandler(void)
{
}



//
// The interrupt handler for the SysTick interrupt.
//
void    SysTickIntHandler(void)
{
  lwIPTimer(SYSTICKMS);
}



int     main(void)
{
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
  // Configure SysTick for a periodic interrupt.
  //
  SysTickPeriodSet(dwSysClockFreq / SYSTICKHZ);
  SysTickEnable();
  SysTickIntEnable();

  //
  // Configure the hardware MAC address for Ethernet Controller filtering of
  // incoming packets.  The MAC address will be stored in the non-volatile
  // USER0 and USER1 registers.
  //
  ulong dwUser0, dwUser1;
  FlashUserGet(&dwUser0, &dwUser1);
  if((dwUser0 == 0xffffffff) || (dwUser1 == 0xffffffff))
  {
      //
      // We should never get here.  This is an error if the MAC address has
      // not been programmed into the device.  Exit the program.
      // Let the user know there is no MAC address
      //
      while(1)
      {
        // TODO
      }
  }

  //
  // Convert the 24/24 split MAC address from NV ram into a 32/16 split MAC
  // address needed to program the hardware registers, then program the MAC
  // address into the Ethernet Controller registers.
  //
  pbMAC[0] = ((dwUser0 >>  0) & 0xff);
  pbMAC[1] = ((dwUser0 >>  8) & 0xff);
  pbMAC[2] = ((dwUser0 >> 16) & 0xff);
  pbMAC[3] = ((dwUser1 >>  0) & 0xff);
  pbMAC[4] = ((dwUser1 >>  8) & 0xff);
  pbMAC[5] = ((dwUser1 >> 16) & 0xff);

  InitSettings();

  lwIPInit(dwSysClockFreq, pbMAC, dwIP, dwGateway, dwNetmask, IPADDR_USE_STATIC);

  InitUDP_Handler();
  InitTCP_Handler();

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

  IntMasterEnable();

  while(1)
  {
  }
}
