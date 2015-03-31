/*------------------------------------------------------------------------------
CALENDAR.H


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "timedate.h"
#include        "calendar.h"



ulong   DateToSecIndex(time  ti)
{
uchar   i;
ulong   dw;

  dw = 0;

  for (i=0; i<ti.bYear; i++)
    dw += GetDaysInYearY(i);

  for (i=1; i<ti.bMonth; i++)
    dw += GetDaysInMonthYM(ti.bYear, i);

  dw += ti.bDay-1;
  dw *= 1440;
  dw += ti.bHour*60 + ti.bMinute;
  dw *= 60;
  dw += ti.bSecond;

  return(dw);
}


time    SecIndexToDate(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  while (dw >= (ulong)24*60*60*GetDaysInYearY(ti.bYear))
  {
    dw -= (ulong)24*60*60*GetDaysInYearY(ti.bYear);
    ti.bYear++;
  }

  ti.bMonth = 1;
  while (dw >= (ulong)24*60*60*GetDaysInMonthYM(ti.bYear,ti.bMonth))
  {
    dw -= (ulong)24*60*60*GetDaysInMonthYM(ti.bYear,ti.bMonth);
    ti.bMonth++;
  }

  ti.bDay = dw/((ulong)24*60*60); dw -= (ulong)24*60*60*ti.bDay;
  ti.bDay++;

  ti.bHour = dw/((uint)60*60); dw -= (ulong)60*60*ti.bHour;

  ti.bMinute = dw/60;  dw -= (ulong)60*ti.bMinute;
  ti.bSecond = dw;

  return ti;
}


/*
ulong   DateToMntIndex(void)
{
uchar   i;
time    ti;

  dw = 0;

  for (i=0; i<ti.bYear; i++)
    dw += DaysInYearSpec(i);

  for (i=1; i<ti.bMonth; i++)
    dw += DaysInMonthSpec(ti.bYear,i);

  dw += ti.bDay-1;
  dw *= 480;
  dw += ti.bHour*20 + ti.bMinute/3;

  return(dw);
}


void    MntIndexToDate(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  while (dw >= (ulong)480*DaysInYearSpec(ti.bYear))
  {
    dw -= (ulong)480*DaysInYearSpec(ti.bYear);
    ti.bYear++;
  }

  ti.bMonth = 1;
  while (dw >= (ulong)480*DaysInMonthSpec(ti.bYear,ti.bMonth))
  {
    dw -= (ulong)480*DaysInMonthSpec(ti.bYear,ti.bMonth);
    ti.bMonth++;
  }

  ti.bDay = dw/480; dw -= ti.bDay*480;
  ti.bDay++;

  ti.bHour = dw/20; dw -= ti.bHour*20;

  ti.bMinute = dw*3;
  ti.bSecond = 0;
}
*/


ulong   DateToHouIndex(time  ti)
{
uchar   i;
ulong   dw;

  dw = 0;

  for (i=0; i<ti.bYear; i++)
    dw += GetDaysInYearY(i);

  for (i=1; i<ti.bMonth; i++)
    dw += GetDaysInMonthYM(ti.bYear,i);

  dw += ti.bDay-1;
  dw *= 48;
  dw += ti.bHour*2 + ti.bMinute/30;

  return(dw);
}


time    HouIndexToDate(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  while (dw >= (uint)48*GetDaysInYearY(ti.bYear))
  {
    dw -= (uint)48*GetDaysInYearY(ti.bYear);
    ti.bYear++;
  }

  ti.bMonth = 1;
  while (dw >= (uint)48*GetDaysInMonthYM(ti.bYear,ti.bMonth))
  {
    dw -= (uint)48*GetDaysInMonthYM(ti.bYear,ti.bMonth);
    ti.bMonth++;
  }

  ti.bDay = dw/48; dw -= ti.bDay*48;
  ti.bDay++;

  ti.bHour = dw/2; dw -= ti.bHour*2;

  ti.bMinute = dw*30;
  ti.bSecond = 0;

  return ti;
}



ulong   DateToDayIndex(time  ti)
{
uchar   i;
ulong   dw;

  dw = 0;

  for (i=0; i<ti.bYear; i++)
    dw += GetDaysInYearY(i);

  for (i=1; i<ti.bMonth; i++)
    dw += GetDaysInMonthYM(ti.bYear,i);

  dw += ti.bDay-1;

  return(dw);
}


time    DayIndexToDate(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  while (dw >= GetDaysInYearY(ti.bYear))
  {
    dw -= GetDaysInYearY(ti.bYear);
    ti.bYear++;
  }

  ti.bMonth = 1;
  while (dw >= GetDaysInMonthYM(ti.bYear,ti.bMonth))
  {
    dw -= GetDaysInMonthYM(ti.bYear,ti.bMonth);
    ti.bMonth++;
  }

  ti.bDay = dw;
  ti.bDay++;

  ti.bHour   = 0;
  ti.bMinute = 0;
  ti.bSecond = 0;

  return ti;
}



ulong   DateToMonIndex(time  ti)
{
uchar   i;
ulong   dw;

  dw = 0;

  for (i=0; i<ti.bYear; i++)
    dw += 12;

  dw += ti.bMonth-1;

  return(dw);
}


time    MonIndexToDate(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  while (dw >= 12)
  {
    dw -= 12;
    ti.bYear++;
  }

  ti.bMonth = dw+1;
  ti.bDay = 1;

  ti.bHour   = 0;
  ti.bMinute = 0;
  ti.bSecond = 0;

  return ti;
}
