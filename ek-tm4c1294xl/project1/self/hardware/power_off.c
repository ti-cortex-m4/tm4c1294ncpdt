/*------------------------------------------------------------------------------
POWER_OFF.C

 Датчик низкого напрящения
------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "power_off.h"



//                                           0123456789ABCDEF
static char const       szPowerOff1[]     = "    Низкое      ",
                        szPowerOff2[]     = "  напряжение !  ";



void    InitPowerOff(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R13; // GPIO Port P Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTP_BASE + GPIO_O_DIR) &= 0xFFFD; // GPIO Direction
  HWREG(GPIO_PORTP_BASE + GPIO_O_DEN) |= 0x0002; // GPIO Digital Enable
}



bool    IsPowerOff(void)
{
  return (HWREG(GPIO_PORTP_BASE + GPIO_O_DATA + 0x0008) == 0);
}



bool    RunPowerOff(void)
{
static bool fPowerOff = false;

  if (IsPowerOff())
  {
    if (fPowerOff == false)
    {
      SaveDisplay();

      ShowHi(szPowerOff1);
      ShowLo(szPowerOff2);
    }

    fPowerOff = true;
    return true;
  }

  if (fPowerOff == true)
  {
    LoadDisplay();

    fPowerOff = false;
  }

  return false;
}
