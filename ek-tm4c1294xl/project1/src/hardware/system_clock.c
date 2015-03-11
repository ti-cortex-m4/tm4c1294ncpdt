/*------------------------------------------------------------------------------
SYSTEM_CLOCK.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "driverlib/rom_map.h"
#include        "driverlib/sysctl.h"



uint32_t GetSystemClockFrequency(void)
{
  // Set the clocking to run directly from the crystal at 120MHz.
  return MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                 SYSCTL_OSC_MAIN |
                                 SYSCTL_USE_PLL |
                                 SYSCTL_CFG_VCO_480), 120000000);
}
