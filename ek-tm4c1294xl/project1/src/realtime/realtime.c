/*------------------------------------------------------------------------------
REALTIME.C

TODO атомарные операции
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../time/rtc.h"
#include        "../health.h"
#include        "next_second.h"
#include        "next_minute1.h"
#include        "next_minute3.h"
#include        "next_minute30.h"
#include        "next_day.h"
#include        "next_month.h"
#include        "next_year.h"
#include        "realtime_storage.h"



// признак перехода на сезонное время в текущие сутки
bool                    fSeason;

// признаки перехода на сезонное время при выключенном состоянии
bool                    fSummer, fWinter;

// признак работы в активном режиме
bool                    fActive;



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
  if (ibSoftMnt > 0) return(ibSoftMnt - 1);
  else               return(bMINUTES-1);
}


uchar   PrevHardMnt(void)
{
  if (ibHardMnt > 0) return(ibHardMnt - 1);
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



void    ProcessTime(void)
{
  // переход на следующую секунду
  if (tiCurr.bSecond != tiPrev.bSecond)
  {
    NextSecond();
  }


  // переход на следующую минуту
  if (tiCurr.bMinute != tiPrev.bMinute)
  {
    PrintString("\n Next 1 min");
    NextMinute1();
  }


  // переход на следующие три минуты
  if ((tiCurr.bMinute % 3 == 0) && (tiPrev.bMinute % 3 != 0))
  {
    PrintString("\n Next 3 min");
    NextMinute3();
  }


  // переход на следующий получас
  if ((tiCurr.bMinute % 30 == 0) && (tiPrev.bMinute % 30 != 0))
  {
    if ((tiCurr.bDay   == tiSummer.bDay)   &&
        (tiCurr.bMonth == tiSummer.bMonth) &&
        (tiCurr.bHour  == 2)               && (fSeason == 0))
    {
      cbSummer++;

      if (fActive == 1)
      {
        tiCurr.bHour = 3;
        SetCurrTimeDate(&tiCurr);
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
        SetCurrTimeDate(&tiCurr);
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
      PrintString("\n Next 30 min");
      NextMinute30();
    }
  }


  // переход на следующие сутки
  if (tiCurr.bDay != tiPrev.bDay)
  {
    PrintString("\n Next day");
    fSeason = 0;
    NextDay();
  }


  // переход на следующий месяц
  if (tiCurr.bMonth != tiPrev.bMonth)
  {
    PrintString("\n Next month");
  	NextMonth();
  }


  // переход на следующий год
  if (tiCurr.bYear != tiPrev.bYear)
  {
    NextYear();
  }
}



void    Realtime(void)
{
time    tiT;

//  if (GetLabelRTC() == 0) {
//	boHealthLabelRTC = FALSE;
//    return;
//  }
//  boHealthLabelRTC = TRUE;

  tiT = *GetCurrTimeDate();
  if (TrueCurrTimeDate(&tiT) == 0) {
    boHealthTimeRTC = FALSE;
	return;
  }
  boHealthTimeRTC = TRUE;

  if (tiCurr.bSecond != tiT.bSecond)
  {
    tiCurr = tiT;

    if (enGlobal != GLB_PROGRAM)
    {
    	ASSERT(ibSoftMnt < bMINUTES);

    	ASSERT(iwHardHou < wHOURS);
    	ASSERT(ibSoftHou < 2);

    	ASSERT(iwHardDay < bDAYS);
    	ASSERT(ibSoftDay < 2);

    	ASSERT(iwHardMon < bMONTHS);
    	ASSERT(ibSoftMon < 2);

      fActive = 1;
      ProcessTime();
    }

    tiPrev = tiCurr;
  }
}
