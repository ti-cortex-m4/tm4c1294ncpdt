/*------------------------------------------------------------------------------
clock.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "clock.h"



#define SECONDS_IN_DAY      (ulong)(24*60*60)
#define SECONDS_IN_HOUR     (uint)(60*60)
#define SECONDS_IN_MINUTE   (uchar)60



static volatile ulong dwClockSeconds = 0;



void Clock_1Hz(void)
{
  dwClockSeconds++;
}


ulong GetClockSeconds(void)
{
  return dwClockSeconds;
}



date_t SecondsToDate(ulong dwSeconds)
{
  date_t days;

  days.wDays = dwSeconds / SECONDS_IN_DAY;
  dwSeconds %= SECONDS_IN_DAY;

  days.bHours = dwSeconds / SECONDS_IN_HOUR;
  dwSeconds %= SECONDS_IN_HOUR;

  days.bMinutes = dwSeconds / SECONDS_IN_MINUTE;

  days.bSeconds = dwSeconds % SECONDS_IN_MINUTE;

  return days;
}
