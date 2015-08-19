/*------------------------------------------------------------------------------
TIMEDATE_DISPLAY.H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../display/display.h"
#include "rtc.h"
#include "timedate.h"
#include "timedate_display.h"



void    ShowTime(time  ti)
{
  sprintf(szLo+4,"%02u:%02u:%02u",
                 ti.bHour,
                 ti.bMinute,
                 ti.bSecond);
}


void    ShowDate(time  ti)
{
  sprintf(szLo+4,"%02u.%02u.%02u",
                 ti.bDay,
                 ti.bMonth,
                 ti.bYear);

  szLo[14] = szDigits[GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay) + 1];
}


void    ShowTimeDate(time  ti)
{
  sprintf(szLo+1,"%02u:%02u %02u.%02u.%02u",
                 ti.bHour,
                 ti.bMinute,
                 ti.bDay,
                 ti.bMonth,
                 ti.bYear);
}


void    ShowDeltaTime(time  ti)
{
  Clear();
  sprintf(szLo+0,"%02u:%02u:%02u",
                 ti.bHour,
                 ti.bMinute,
                 ti.bSecond);

  uint iwDay1 = GetDayIndexMD(ti.bMonth, ti.bDay);
  ulong dwSecond1 = GetSecondIndex(ti);

  time ti2 = *GetCurrTimeDate();

  uint iwDay2 = GetDayIndexMD(ti2.bMonth, ti2.bDay);
  ulong dwSecond2 = GetSecondIndex(ti2);

  if (iwDay1 != iwDay2)
    sprintf(szLo+9,"?");
  else if (dwSecond1 > dwSecond2)
    sprintf(szLo+9,"-%lu", dwSecond1 - dwSecond2);
  else
    sprintf(szLo+9,"+%lu", dwSecond2 - dwSecond1);
}



void    LoadBetaMonth(uchar  ibMonth)
{
  strcpy(szBeta,szOnMonth);
  sprintf(szBeta+11, "%-2u", ibMonth + 1);
}

