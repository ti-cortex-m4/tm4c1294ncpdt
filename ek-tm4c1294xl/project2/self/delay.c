/*------------------------------------------------------------------------------
DELAY.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "delay.h"



void    Nop(void)
{
  __asm("nop");
}


void    DelayMicroSecond(uint wMicroSecond)
{
  if (wMicroSecond == 0) return;

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


void    DelayMillySecond(uint wMillySecond)
{
  if (wMillySecond == 0) return;

  while (wMillySecond-- > 0)
  {
    DelayMicroSecond(1000);
  }
}


void    DelaySecond(uint wSecond)
{
  if (wSecond == 0) return;

  while (wSecond-- > 0)
  {
    DelayMillySecond(1000);
  }
}
