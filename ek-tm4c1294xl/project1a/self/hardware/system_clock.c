/*------------------------------------------------------------------------------
SYSTEM_CLOCK,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"



static uint32_t         ui32SysClockFreq;



// Set the clocking to run directly from the crystal at 120MHz.
void MakeSystemClockFrequency(void)
{
  ui32SysClockFreq = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);
}


uint32_t GetSystemClockFrequency(void)
{
  return ui32SysClockFreq;
}
