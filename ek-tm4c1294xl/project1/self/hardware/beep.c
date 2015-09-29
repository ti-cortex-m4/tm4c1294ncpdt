/*------------------------------------------------------------------------------
BEEP.C

Звуковой сигнал
------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "../time/delay.h"
#include "beep.h"



static void BeepOn(void)
{
#ifdef ENABLE_BEEP

  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0010) = 0x0004;

#endif
}


static void BeepOff(void)
{
#ifdef ENABLE_BEEP

  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0010) = ~0x0004;

#endif
}



void    InitBeep(void)
{
#ifdef ENABLE_BEEP

  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R4; // GPIO Port E Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DIR) |= 0x0004; // GPIO Direction
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DEN) |= 0x0004; // GPIO Digital Enable

#endif

  Beep();
}



void    Beep(void)
{
  BeepOn();
  Delay(50);

  BeepOff();
  Delay(50);
}


void    LongBeep(void)
{
  Beep();
  Beep();
  Beep();
}
