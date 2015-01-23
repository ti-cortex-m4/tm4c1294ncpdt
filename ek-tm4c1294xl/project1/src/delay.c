/*------------------------------------------------------------------------------
DELAY.C 


------------------------------------------------------------------------------*/

#include        "main.h"



void    Nop(void) {
  __asm("nop");
}


void    DelayMicro(uint  wMicroSec) {
uint  i;

  if (wMicroSec == 0) return;

  while (wMicroSec-- > 0) {
    for (i=0; i<2000; i++)
      Nop();
  }
}


void    DelayMilly(uint  wMillySec) {
  if (wMillySec == 0) return;

  while (wMillySec-- > 0) {
    DelayMicro(1000);
  }
}



void    Delay(uint  wMillySec) {
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
