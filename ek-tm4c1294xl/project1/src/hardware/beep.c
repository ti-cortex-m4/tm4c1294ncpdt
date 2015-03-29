/*------------------------------------------------------------------------------
BEEP.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "inc/hw_sysctl.h"
#include        "inc/hw_gpio.h"
#include        "inc/hw_memmap.h"
#include        "inc/hw_types.h"
#include        "../time/delay.h"
#include        "beep.h"



void    SoundOn(void) {
#ifdef NATIVE_BEEP

  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0010) = 0x0004;

#endif
}


void    SoundOff(void) {
#ifdef NATIVE_BEEP

  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0010) = ~0x0004;

#endif
}



void    InitBeep(void) {
#ifdef NATIVE_BEEP

  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R4; // GPIO Port E Run Mode Clock Gating Control
  RunClocking();
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DIR) |= 0x0004; // GPIO Direction
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DEN) |= 0x0004; // GPIO Digital Enable

#endif

  Beep();
}



void    Beep(void) {
  SoundOn();  Delay(50);
  SoundOff(); Delay(50);
}


void    LongBeep(void) {
  Beep(); Beep(); Beep();
}

