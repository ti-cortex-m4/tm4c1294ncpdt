/*------------------------------------------------------------------------------
IMPULSES!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_digitals.h"
#include "../realtime/realtime.h"
#include "../time/delay.h"
#include "impulses.h"



volatile bool           fOnImpulse, fOnSecond;

static volatile bool    fEnabledImpulses = false;

#ifdef NATIVE_IMPULSES
static uint             bLo0,bLo1,bLo2,bLo3;
#endif


void    EnableImpulses(void) {
  fEnabledImpulses = true;
}


void    DisableImpulses(void) {
  fEnabledImpulses = false;
}


#ifdef NATIVE_IMPULSES

uint    GetImpulses(void)
{
  uint w = 0;

  if (HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0004) == 0) w |= 0x0001;
  if (HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0008) == 0) w |= 0x0002;
  if (HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0010) == 0) w |= 0x0004;
  if (HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0020) == 0) w |= 0x0008;
  if (HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0040) == 0) w |= 0x0010;
  if (HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0080) == 0) w |= 0x0020;
  if (HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0100) == 0) w |= 0x0040;
  if (HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0200) == 0) w |= 0x0080;

  if (HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0004) == 0) w |= 0x0100;
  if (HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0008) == 0) w |= 0x0200;
  if (HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0010) == 0) w |= 0x0400;
  if (HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0020) == 0) w |= 0x0800;
  if (HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0040) == 0) w |= 0x1000;
  if (HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0080) == 0) w |= 0x2000;
  if (HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0100) == 0) w |= 0x4000;
  if (HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0200) == 0) w |= 0x8000;

  return w;
}

#endif


void    Impulses_Timer0(void) {
// TODO uint *pwImpMntCan = mpwImpMntCan[ibSoftMnt];

  if (fEnabledImpulses)  {
#ifdef NATIVE_IMPULSES

    bLo0 = GetImpulses();
    uint w = bLo0 & bLo1 & bLo2 & bLo3;

    w &= wDigitalsMask;
    if (w != 0) fOnImpulse = 1;

    if ((w & 0x0001) != 0) mpwImpMntCan[ibSoftMnt][0]++;
    if ((w & 0x0002) != 0) mpwImpMntCan[ibSoftMnt][1]++;
    if ((w & 0x0004) != 0) mpwImpMntCan[ibSoftMnt][2]++;
    if ((w & 0x0008) != 0) mpwImpMntCan[ibSoftMnt][3]++;
    if ((w & 0x0010) != 0) mpwImpMntCan[ibSoftMnt][4]++;
    if ((w & 0x0020) != 0) mpwImpMntCan[ibSoftMnt][5]++;
    if ((w & 0x0040) != 0) mpwImpMntCan[ibSoftMnt][6]++;
    if ((w & 0x0080) != 0) mpwImpMntCan[ibSoftMnt][7]++;
    if ((w & 0x0100) != 0) mpwImpMntCan[ibSoftMnt][8]++;
    if ((w & 0x0200) != 0) mpwImpMntCan[ibSoftMnt][9]++;
    if ((w & 0x0400) != 0) mpwImpMntCan[ibSoftMnt][10]++;
    if ((w & 0x0800) != 0) mpwImpMntCan[ibSoftMnt][11]++;
    if ((w & 0x1000) != 0) mpwImpMntCan[ibSoftMnt][12]++;
    if ((w & 0x2000) != 0) mpwImpMntCan[ibSoftMnt][13]++;
    if ((w & 0x4000) != 0) mpwImpMntCan[ibSoftMnt][14]++;
    if ((w & 0x8000) != 0) mpwImpMntCan[ibSoftMnt][15]++;

    bLo3 = bLo2; bLo2 = bLo1; bLo1 = ~bLo0;

#endif
  }
}


void    Impulses_1Hz(void) {
  if (fEnabledImpulses)  {
//    fOnImpulse = 1;
//    mpwImpMntCan[ibSoftMnt][0]++;
  }
}



void    InitImpulses(void) {
#ifdef NATIVE_IMPULSES

  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R9; // GPIO Port K Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTK_BASE + GPIO_O_DIR) &= 0xFF00; // GPIO Direction
  HWREG(GPIO_PORTK_BASE + GPIO_O_DEN) |= 0x00FF; // GPIO Digital Enable

  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R11; // GPIO Port M Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTM_BASE + GPIO_O_DIR) &= 0xFF00; // GPIO Direction
  HWREG(GPIO_PORTM_BASE + GPIO_O_DEN) |= 0x00FF; // GPIO Digital Enable

  bLo0 = bLo1 = bLo2 = bLo3 = 0;

#endif

  (enGlobal == GLB_WORK) ? EnableImpulses() : DisableImpulses();
}


void    StartImpulses(void) {
  EnableImpulses();
}
