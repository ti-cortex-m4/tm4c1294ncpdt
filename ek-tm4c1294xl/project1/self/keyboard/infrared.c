/*------------------------------------------------------------------------------
INFRARED,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "keyboard.h"
#include "../time/delay.h"
#include "../access.h"
#include "../../irmp/irmp.h"
#include "infrared.h"



#ifndef NO_DISPLAY

void    InitInfrared(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R13; // GPIO Port P Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTP_BASE + GPIO_O_DIR) &= 0xFFFE; // GPIO Direction
  HWREG(GPIO_PORTP_BASE + GPIO_O_DEN) |= 0x0001; // GPIO Digital Enable
}



static uchar ConvertKey(uint  i)
{
  switch (i)
  {
    case 0: return 0x2B;
    case 1: return 0x0E;
    case 2: return 0x1E;
    case 3: return 0x2E;
    case 4: return 0x3E;
    case 5: return 0x0D;
    case 6: return 0x1D;
    case 7: return 0x2D;
    case 8: return 0x3D;
    case 9: return 0x0B;
    case 12: return 0x07;
    case 59: return 0x17;
    default: return 0xFF;
  }
}


void    RunInfrared(void)
{
  static IRMP_DATA irmp_data;

  if (irmp_get_data(&irmp_data))
  {
    if (!(irmp_data.flags & IRMP_FLAG_REPETITION))
    {
      uchar i = ConvertKey(irmp_data.command);
      if (i != 0xFF)
      {
        bKey = i;
        fKey = true;
      }

      if ((enGlobal == GLB_WORK) && (wProgram == bSET_PASSWORD))
      {
        if ((bKey == mpbKeys[13]) && (SuperUser() == false))
        {
          fKey = false;
          Beep();
        }
      }
    }
  }
}

#endif
