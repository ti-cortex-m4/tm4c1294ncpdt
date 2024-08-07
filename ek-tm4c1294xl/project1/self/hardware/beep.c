/*------------------------------------------------------------------------------
BEEP.C

�������� ������
------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "../time/delay.h"
#include "led.h"
#include "beep.h"



static void BeepOn(void)
{
#ifdef ENABLE_BEEP
#ifndef NO_DISPLAY

  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0010) = 0x0004;

#else

  LEDGreenOn();
  LEDRedOn();

#endif
#endif
}


static void BeepOff(void)
{
#ifdef ENABLE_BEEP
#ifndef NO_DISPLAY

  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0010) = ~0x0004;

#else

  LEDGreenOff();
  LEDRedOff();

#endif
#endif
}



void    InitBeep(void)
{
#ifdef ENABLE_BEEP
#ifndef NO_DISPLAY

  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R4; // GPIO Port E Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DIR) |= 0x0004; // GPIO Direction
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DEN) |= 0x0004; // GPIO Digital Enable

#else

  InitLED();

#endif
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
