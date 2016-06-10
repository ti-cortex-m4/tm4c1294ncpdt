/*------------------------------------------------------------------------------
delay.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "watchdog.h"
#include "delay.h"



void Nop(void)
{
  __asm("nop");
}


void DelayGPIO(void)
{
  Nop();
  Nop();
  Nop();
  Nop();
  Nop();
}



void DelayMicroSecond(uint wMicroSecond)
{
  if (wMicroSecond == 0)
    return;

  while (wMicroSecond-- > 0)
  {
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


void DelayMilliSecond(uint wMillySecond)
{
  if (wMillySecond == 0)
    return;

  while (wMillySecond-- > 0)
  {
    DelayMicroSecond(1000);
  }
}


void DelaySecond(uint wSecond)
{
  if (wSecond == 0)
    return;

  while (wSecond-- > 0)
  {
    ResetWatchdog();
    DelayMilliSecond(1000);
  }
}
