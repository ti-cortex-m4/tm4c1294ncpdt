/*------------------------------------------------------------------------------
OUT_TEST_TIME,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../time/rtc.h"
#include "../time/timedate.h"
#include "out_test_time.h"



void    OutTestMinute3(void)
{
  time ti = *GetCurrTimeDate();
  ti.bSecond = 58;
  ti.bMinute = (ti.bMinute/3)*3 + 2;

  SetCurrTimeDate(ti);
  Common(GetCurrTimeDate(), sizeof(time));
}


void    OutTestMinute15(void)
{
  time ti = *GetCurrTimeDate();
  ti.bSecond = 58;
  ti.bMinute = (ti.bMinute/15)*15 + 14;

  SetCurrTimeDate(ti);
  Common(GetCurrTimeDate(), sizeof(time));
}


void    OutTestMinute30(void)
{
  time ti = *GetCurrTimeDate();
  ti.bSecond = 58;
  ti.bMinute = (ti.bMinute/30)*30 + 29;

  SetCurrTimeDate(ti);
  Common(GetCurrTimeDate(), sizeof(time));
}


void    OutTestDay(void)
{
  time ti = *GetCurrTimeDate();
  ti.bSecond = 58;
  ti.bMinute = 59;
  ti.bHour   = 23;

  SetCurrTimeDate(ti);
  Common(GetCurrTimeDate(), sizeof(time));
}


void    OutTestMonth(void)
{
  time ti = *GetCurrTimeDate();
  ti.bSecond = 58;
  ti.bMinute = 59;
  ti.bHour   = 23;
  ti.bDay    = GetDaysInMonthYM(ti.bYear, ti.bMonth);

  SetCurrTimeDate(ti);
  Common(GetCurrTimeDate(), sizeof(time));
}


void    OutTestYear(void)
{
  time ti = *GetCurrTimeDate();
  ti.bSecond = 58;
  ti.bMinute = 59;
  ti.bHour   = 23;
  ti.bDay    = 31;
  ti.bMonth  = 12;

  SetCurrTimeDate(ti);
  Common(GetCurrTimeDate(), sizeof(time));
}
