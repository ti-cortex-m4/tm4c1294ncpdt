/*------------------------------------------------------------------------------
DELAY!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/watchdog.h"
#include "delay.h"



void    Nop(void) {
  __asm("nop");
}


void    DelayGPIO(void) {
__asm("   nop\n"
      "   nop\n"
      "   nop\n");
}



void    DelayMicro(uint  wMicroSec) {
  if (wMicroSec == 0) return;

  while (wMicroSec-- > 0) {
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
  }
}


void    DelayMilly(uint  wMillySec) {
  if (wMillySec == 0) return;

  while (wMillySec-- > 0) {
    DelayMicro(1000);
  }
}


void    DelaySeconds(uint  wSecond) {
  if (wSecond == 0) return;

  while (wSecond-- > 0) {
    ResetWatchdog();
    DelayMilly(1000);
  }
}


void    Delay(uint  wMillySec) {
  ResetWatchdog();
  DelayMilly(wMillySec);
}



void    DelayMsg(void) {
  Delay(1500);
}


void    DelayInf(void) {
  Delay(500);
}


void    DelayOff(void) {
  Delay(100);
}
