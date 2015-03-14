/*------------------------------------------------------------------------------
TIMEDATE_DISPLAY.H


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../display/display.h"
#include        "timedate.h"
#include        "timedate_display.h"



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
{ ShowTimeDate(ti);
/*
uint    i;

  Clear();
  sprintf(szLo+0,"%02bu:%02bu:%02bu",
                 tiAlt.bHour,
                 tiAlt.bMinute,
                 tiAlt.bSecond);

  dwBuffC = GetSecondIndex();
  i = GetDayIndex();

  tiAlt = *PGetCurrTimeDate();

  if (i != GetDayIndex())
    sprintf(szLo+9,"?");
  else if (dwBuffC > GetSecondIndex())
  {
    dwBuffC = dwBuffC - GetSecondIndex();
    sprintf(szLo+9,"-%lu", dwBuffC);
  }
  else
  {
    dwBuffC = GetSecondIndex() - dwBuffC;
    sprintf(szLo+9,"+%lu", dwBuffC);
  }*/
}



void    LoadBetaMonth(uchar  ibMonth)
{
  strcpy(szBeta,szOnMonth);
  sprintf(szBeta+11, "%-2u", ibMonth + 1);
}

