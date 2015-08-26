/*------------------------------------------------------------------------------
REALTIME.C

TODO атомарные операции
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_params.h"
#include "../digitals/current/current_run.h"
#include "../digitals/wait_query.h"
#include "../hardware/power_off.h"
#include "../time/rtc.h"
#include "../time/gps.h"
#include "../health.h"
#include "../serial/dtr.h"
#include "../serial/print.h"
#include "next_second.h"
#include "next_minute1.h"
#include "next_minute3.h"
#include "next_minute30.h"
#include "next_day.h"
#include "next_month.h"
#include "next_year.h"
#include "realtime_storage.h"



// признак перехода на сезонное время в текущие сутки
bool                    fSeason;

// признаки перехода на сезонное время при выключенном состоянии
bool                    fSummer, fWinter;

// признак работы в активном режиме
bool                    fActive;

// признаки для запуска задач
bool                    fCurrent, fProfile;



// TODO rename возвращает индекс текущего получаса
uchar   GetCurrHouIndex(void)
{
  return(tiCurr.bHour*2 + tiCurr.bMinute/30);
}


// TODO rename возвращает индекс на первый получас требуемых суток назад
uint    GetDayHouIndex(uchar  bDay)
{
uchar   i;
uint    j;

  // индекс на первый получас текущих суток
  j = (wHOURS+iwHardHou-GetCurrHouIndex()) % wHOURS;

  // индексы на первые получасы суток назад
  for (i=0; i<bDay; i++) j = (wHOURS+j-48) % wHOURS;

  // индекс на первый получас требуемых суток
  return(j);
}



uchar   PrevSoftMnt(void)
{
  if (ibSoftMnt > 0) return(0);
  else               return(1);
}


uint    PrevHardMnt(void)
{
  if (iwHardMnt > 0) return(iwHardMnt - 1);
  else               return(bMINUTES-1);
}



uchar   PrevSoftHou(void)
{
  if (ibSoftHou > 0) return(0);
  else               return(1);
}


uint    PrevHardHou(void)
{
  if (iwHardHou > 0) return(iwHardHou - 1);
  else               return(wHOURS-1);
}



uchar   PrevSoftDay(void)
{
  if (ibSoftDay > 0) return(0);
  else               return(1);
}


uchar   PrevHardDay(void)
{
  if (ibHardDay > 0) return(ibHardDay - 1);
  else               return(bDAYS-1);
}



uchar   PrevSoftMon(void)
{
  if (ibSoftMon > 0) return(0);
  else               return(1);
}


uchar   PrevHardMon(void)
{
  if (ibHardMon > 0) return(ibHardMon - 1);
  else               return(bMONTHS-1);
}


uchar   PrevSoftTim(void)
{
  if (ibSoftTim > 0) return(0);
  else               return(1);
}


void    ProcessTime(void)
{
  // переход на следующую секунду
  if (tiCurr.bSecond != tiPrev.bSecond)
  {
    NextSecond();

    if ((fActive == 1) && (enGlobal != GLB_PROGRAM))
    {
      if ((fCurrent == 1) && (cbWaitQuery == 0))
      {
        if ((tiCurr.bMinute % 3)*60 + tiCurr.bSecond >= bTimeoutCurrent)
        {
          RunCurrent();
        }
      }
    }
  }


  // переход на следующую минуту
  if (tiCurr.bMinute != tiPrev.bMinute)
  {
  	PrintStart();
  	PrintString("\n tiCurr="); PrintTime(tiCurr); PrintString(" tiPrev="); PrintTime(tiPrev);
  	PrintString("\n next 1 min.");
    NextMinute1();
  }


  // переход на следующие три минуты
  if ((tiCurr.bMinute % 3 == 0) && (tiPrev.bMinute % 3 != 0))
  {
    PrintString("\n next 3 min.");
    NextMinute3();
    PrintInt(ibSoftMnt); PrintInt(iwHardMnt);

    if (fActive == 1) fCurrent = 1;
  }


  if ((tiCurr.bMinute % 15 == 0) && (tiPrev.bMinute % 15 != 0))
  {
    if (fActive == 1) RunGps();
  }


  // переход на следующий получас
  if ((tiCurr.bMinute % 30 == 0) && (tiPrev.bMinute % 30 != 0))
  {
    if (fActive == 1) RunDTR();

    if (fActive == 1) fProfile = 1;

    if ((tiCurr.bDay   == tiSummer.bDay)   &&
        (tiCurr.bMonth == tiSummer.bMonth) &&
        (tiCurr.bHour  == 2)               && (fSeason == 0))
    {
      cbSummer++;

      if (fActive == 1)
      {
        tiCurr.bHour = 3;
        SetCurrTimeDate(tiCurr);
      }
      else fSummer = 1;

      fSeason = 1;

      NextMinute30();
      NextMinute30();
      NextMinute30();
    }
    else
    if ((tiCurr.bDay   == tiWinter.bDay)   &&
        (tiCurr.bMonth == tiWinter.bMonth) &&
        (tiCurr.bHour  == 3)               && (fSeason == 0))
    {
      cbWinter++;

      if (fActive == 1)
      {
        tiCurr.bHour = 2;
        SetCurrTimeDate(tiCurr);
      }
      else fWinter = 1;

      fSeason = 1;
    }
    else
    if ((tiCurr.bDay   == tiWinter.bDay)   &&
        (tiCurr.bMonth == tiWinter.bMonth) &&
        (tiCurr.bHour  == 2)               && (fSeason == 1))
      { }
    else
    {
    	PrintString("\n next 30 min.");
      NextMinute30();
      PrintInt(ibSoftHou); PrintInt(iwHardHou);
    }
  }


  // переход на следующие сутки
  if (tiCurr.bDay != tiPrev.bDay)
  {
  	PrintString("\n next day");
    fSeason = 0;
    NextDay();
    PrintInt(ibSoftDay); PrintInt(ibHardDay);
  }


  // переход на следующий месяц
  if (tiCurr.bMonth != tiPrev.bMonth)
  {
  	PrintString("\n next month");
  	NextMonth();
  	PrintInt(ibSoftMon); PrintInt(ibHardMon);
  }


  // переход на следующий год
  if (tiCurr.bYear != tiPrev.bYear)
  {
    NextYear();
  }
}



void    RunRealtime(void)
{
time    tiT;

//  if (GetLabelRTC() == 0) {
//	boHealthLabelRTC = false;
//    return;
//  }
//  boHealthLabelRTC = true;

  tiT = *GetCurrTimeDate();
  if (TrueCurrTimeDate(tiT) == 0) {
    boHealthTimeRTC = false;
	return;
  }
  boHealthTimeRTC = true;

  if (RunPowerOff())
    return;

  if (tiCurr.bSecond != tiT.bSecond)
  {
    tiCurr = tiT;

    if (enGlobal != GLB_PROGRAM)
    {
    	ASSERT(ibSoftMnt < bMINUTES);

    	ASSERT(iwHardHou < wHOURS);
    	ASSERT(ibSoftHou < 2);

    	ASSERT(ibHardDay < bDAYS);
    	ASSERT(ibSoftDay < 2);

    	ASSERT(ibHardMon < bMONTHS);
    	ASSERT(ibSoftMon < 2);

    	ASSERT(iwHardTim < wTIMES);
    	ASSERT(ibSoftTim < 2);

      fActive = 1;
      ProcessTime();
    }

    tiPrev = tiCurr;
  }
}
