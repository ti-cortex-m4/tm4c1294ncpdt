/*------------------------------------------------------------------------------
CALENDAR2.H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "calendar2.h"



ulong   TimeToSecIndex(time  ti)
{
ulong   dw;

  dw = ti.bHour*60 + ti.bMinute;
  dw *= 60;
  dw += ti.bSecond;

  return dw;
}

/*
time    SecIndexToTime(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  ti.bMonth = 0;
  ti.bDay = 0;

  ti.bHour = dw/((uint)60*60); dw -= (ulong)60*60*ti.bHour;

  ti.bMinute = dw/60; dw -= (ulong)60*ti.bMinute;
  ti.bSecond = dw;

  return ti;
}
*/


ulong   TimeToHouIndex(time  ti)
{
  return ti.bHour*2 + ti.bMinute/30;
}

/*
time    HouIndexToTime(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  ti.bMonth = 0;
  ti.bDay = 0;

  ti.bHour = dw/2; dw -= ti.bHour*2;

  ti.bMinute = dw*30;
  ti.bSecond = 0;

  return ti;
}
*/
