/*------------------------------------------------------------------------------
clock.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "clock.h"



static volatile ulong dwClock = 0;



void Clock_1Hz(void)
{
  dwClock++;
}


ulong GetClock(void)
{
  return dwClock;
}
