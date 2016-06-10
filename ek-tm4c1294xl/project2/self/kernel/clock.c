/*------------------------------------------------------------------------------
clock.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "clock.h"



static volatile ulong dwClockSeconds = 0;



void Clock_1Hz(void)
{
  dwClockSeconds++;
}


ulong GetClockSeconds(void)
{
  return dwClockSeconds;
}
