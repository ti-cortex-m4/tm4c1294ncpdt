/*------------------------------------------------------------------------------
DELAY!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/watchdog.h"
#include "delay.h"



void    Nop(void) {
  __asm(" nop");
}


void    DelayGPIO(void) {
  __asm(" nop");
  __asm(" nop");
  __asm(" nop");
  __asm(" nop");
  __asm(" nop");
}



void    DelayMicro(uint  wMicroSec) {
  if (wMicroSec == 0) return;

  while (wMicroSec-- > 0) {
//    Nop();
//    Nop();
//    Nop();
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


void    DelayMilli(uint  wMilliSec) {
  if (wMilliSec == 0) return;

  while (wMilliSec-- > 0) {
    DelayMicro(1000);
  }
}


void    DelaySeconds(uint  wSecond) {
  if (wSecond == 0) return;

  while (wSecond-- > 0) {
    ResetWatchdog();
    DelayMilli(1000);
  }
}


void    Delay(uint  wMillySec) {
  ResetWatchdog();
  DelayMilli(wMillySec);
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
