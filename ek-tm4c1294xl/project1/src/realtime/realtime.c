/*------------------------------------------------------------------------------
REALTIME.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_energy.h"
#include        "../tariffs/tariffs.h"
#include        "next_second.h"
#include        "next_minute1.h"
#include        "next_minute3.h"
#include        "next_minute30.h"
#include        "next_day.h"
#include        "next_month.h"
#include        "next_year.h"
#include        "../energy.h"
#include        "../energy2.h"
#include        "../power.h"
#include        "../rtc.h"



// признак перехода на сезонное время в текущие сутки
bool                    fSeason;

// признаки перехода на сезонное время при выключенном состоянии
bool                    fSummer, fWinter;

// признак работы в активном режиме
bool                    fActive;
/*
// признаки для запуска локальных задач
bit                     fProfile,fCurrent;

// признак выдачи команды на программирование модема
bit                     fSendAT;

        

void    ClearNewTime(void)
{
  boNewSec = boNewMin = boNewMnt = boNewHou = boNewDay = boNewMon = boNewYea = boTrue;
}
*/


uchar   PrevSoftMnt(void)
{
  if (ibSoftMnt > 0) return(ibSoftMnt - 1);
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


/*
// возвращает индекс текущего получаса
uchar   GetHouIndex(void)
{
  return(tiCurr.bHour*2 + tiCurr.bMinute/30);
}


// возвращает индекс на первый получас требуемых суток назад
uint    PrevDayIndex(uchar  bDay)
{
uchar   i;
uint    j;

  // индекс на первый получас текущих суток
  j = (wHOURS+iwHardHou-GetHouIndex()) % wHOURS;

  // индексы на первые получасы суток назад
  for (i=0; i<bDay; i++) j = (wHOURS+j-48) % wHOURS;

  // индекс на первый получас требуемых суток
  return(j);
}



void    MakeCurrHouCan(void)
{
uchar   i;

  for (i=0; i<bCANALS; i++)
  {
    if ((GetDigitalDevice(i) != 0) && (IsSpecCurrent(GetDigitalDevice(i)) == 0)) 
      SetCanInt(mpwImpHouCan[ibSoftHou], i, 0xFFFF); 
  }
}


void    MakeCurrTimPar(void)
{
}



// обработка перехода на следующий интервал
void    ProcessNextTim(void)
{
  SaveParTim(iwHardTim,ibSoftTim);

  if (++iwHardTim >= wTIMES) iwHardTim = 0;
  if (++ibSoftTim >= 2)      ibSoftTim = 0; 

  memset(&mpreParBuff[ibSoftTim], 0xFF, sizeof(real)*wPARAMS);

  if (cwParamTim < wTIMES-1) cwParamTim++;

  MakeCurrTimPar(); 
}
*/


// обработка перехода на следующий получас
void    ProcessNextHou(void)
{
  // расчёт максимумов мощности за текущие сутки и месяц
  MakeMaxPowAll();

//  // расчёт пределов опроса счётчиков
//  MakeLimits();

  SaveImpHou(0,iwHardHou,ibSoftHou);

  if (++iwHardHou >= wHOURS) iwHardHou = 0;
  if (++ibSoftHou >= 2)      ibSoftHou = 0;

  memset(&mpwImpHouCan[ibSoftHou], 0, sizeof(uint)*bCANALS);

//  MakeCurrHouCan();
//  NextHouDiagram();
//  NextHouLimitsAux();
//  IOControl();

  cdwMinutes30++;
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
    NextMinute1();
  }


  // переход на следующие три минуты
  if ((tiCurr.bMinute % 3 == 0) && (tiPrev.bMinute % 3 != 0))
  {
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

      ProcessNextHou();
      ProcessNextHou();
      ProcessNextHou();
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
      ProcessNextHou();
  }


  // переход на следующие сутки
  if (tiCurr.bDay != tiPrev.bDay)
  {
//    // флаг наступления новых суток
//    boNewDay = boTrue;
//    NextDayExtended4();
//    NextDayExtended5();
//    NextDayExtended6();
//    NextDayExtended7();
//
//    // программирование модема
//    ResetSendAT();

    // обнуление признака перехода на сезонное времени в текущие сутки
    fSeason = 0;

    // рассчёт показаний счётчиков по месяцам
    MakeCounters();

    // рассчёт массивов индексов тарифов для каждого получаса текущих суток для всех блоков (для мощности и энергии)
    MakeAllCurrTariffs();

    SaveImpDay(0,ibHardDay,ibSoftDay);
    SavePowDay(0,ibHardDay,ibSoftDay);

    if (++ibHardDay >= bDAYS) ibHardDay = 0;
    if (++ibSoftDay >= 2)     ibSoftDay = 0;

    memset(&mpimDayCan[ibSoftDay], 0, sizeof(impulse)*bCANALS);
    memset(&mppoDayGrp[ibSoftDay], 0, sizeof(power)*bGROUPS);

//    // обработка брака по суткам
//    tiAlt = tiCurr;
//    MakeDefectDay(0);
//
//    // обработка достоверности по суткам
//    NextDayDef();
//
//    EnableAnswer();
    cwDays++;
  }


  // переход на следующий месяц
  if (tiCurr.bMonth != tiPrev.bMonth)
  {
    SaveImpMon(0,ibHardMon,ibSoftMon);
    SavePowMon(0,ibHardMon,ibSoftMon);
    SaveCntMon(0,ibHardMon,ibSoftMon);

    if (++ibHardMon >= bMONTHS) ibHardMon = 0;
    if (++ibSoftMon >= 2)       ibSoftMon = 0;

    memset(&mpimMonCan[ibSoftMon],    0, sizeof(impulse)*bCANALS);
    memset(&mppoMonGrp[ibSoftMon],    0, sizeof(power)*bGROUPS);
    memset(&mpreCntMonCan[ibSoftMon], 0, sizeof(real)*bCANALS);

//    NextMonExtended4();
//    NextMonExtended4T();
//    NextMonExtended6();
//
//    // обработка брака по месяцам
//    tiAlt = tiCurr;
//    MakeDefectMon(0);
//
//    // сохранение данныех коррекции за предыдущий месяц
//    memcpy(&mpcwPosValuePrev, &mpcwPosValueCurr, sizeof(mpcwPosValuePrev));
//    memcpy(&mpcwNegValuePrev, &mpcwNegValueCurr, sizeof(mpcwNegValuePrev));
//    memcpy(&mpcwPosCountPrev, &mpcwPosCountCurr, sizeof(mpcwPosCountPrev));
//    memcpy(&mpcwNegCountPrev, &mpcwNegCountCurr, sizeof(mpcwNegCountPrev));
//
//    // обнуление данныех коррекции за текущий месяц
//    memset(&mpcwPosValueCurr, 0, sizeof(mpcwPosValueCurr));
//    memset(&mpcwNegValueCurr, 0, sizeof(mpcwNegValueCurr));
//    memset(&mpcwPosCountCurr, 0, sizeof(mpcwPosCountCurr));
//    memset(&mpcwNegCountCurr, 0, sizeof(mpcwNegCountCurr));

    // сохраняем признак совмещённых/раздельных суточных тарифных графиков за предыдущий месяц
    fPublicTariffsPrev = fPublicTariffsCurr;

    // рассчёт показаний счётчиков по месяцам
    MakeCounters();

//    // обработка достоверности по месяцам
//    NextMonDef();

    cwMonths++;
  }


  // переход на следующий год
  if (tiCurr.bYear != tiPrev.bYear)
  {
    NextYear();
  }
}


/*
// начальная инициализация индексов
void    MakeNexttime(void)
{
  ibSoftMnt = 0;

  ibSoftHou = 0;
  iwHardHou = 0;

  ibSoftDay = 0;
  ibHardDay = 0;

  ibSoftMon = 0;
  ibHardMon = *PGetCurrTimeDate()->bMonth - 1;

  ibSoftTim = 0;
  iwHardTim = 0;

  cbSummer = 0;
  cbWinter = 0;

  ET0 = 0;
  memset(&mpwImpMntCan[ibSoftMnt], '\0', sizeof(uint)*bCANALS);
  ET0 = 1;

  MakeCurrHouCan();

  MakeCurrTimPar();

  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    if (GetDigitalDevice(ibCan) == 0)
    {
      reBuffA = GetCanReal(mpreCount,ibCan);
      SetCanReal(mpreCntMonCan[ ibSoftMon ],ibCan);    
    }    
  }
}



// программа обработки переходов в виртуальном времени
bit     NexttimeOff(void)
{
uchar   i;

  cbWaitQuery = 0;

  fProfile = 0;
  fCurrent = 0;

  fSeason  = 0;

  if (GetLabelXDATA() == 0)
    return(1);
  else
  {
    // увеличиваем счётчик включений питания
    cbPowerOn++;
    // сохраняем время выключения питания
    tiPowerOff = tiCurr;

    i = 0;
    while (1)
    {
      ResetWDT();

      // чтение текущего времени
      tiKey = *PGetCurrTimeDate();
      // копируем секунды для последующего сравнения
      tiCurr.bSecond = tiKey.bSecond;
       
      // сохраняем время включения питания
      tiPowerOn = tiKey;

      if (memcmp(&tiCurr, &tiKey, sizeof(time)) == 0)
        return(1);

      // перевод время в интервалом в минуту
      if (++tiCurr.bMinute >= 60)
      {
        tiCurr.bMinute = 0;
        if (++tiCurr.bHour >= 24)
        {
          tiCurr.bHour = 0;

          // предельное время выключения питания
          if (++i > 30) return(0);

          tiAlt = tiCurr;
          if (++tiCurr.bDay > DaysInMonth())
          {
            tiCurr.bDay = 1;
            if (++tiCurr.bMonth > 12)
            {
              tiCurr.bMonth = 1;
              tiCurr.bYear++;
            }
          }
        }
      }

      // обработка переходов времени
      ProcessTime();
/ *
      sprintf(szHi,"Дата   %02bu.%02bu.%02bu",
              tiCurr.bDay,   
              tiCurr.bMonth,
              tiCurr.bYear);

      sprintf(szLo,"Время  %02bu:%02bu:%02bu",
              tiCurr.bHour,
              tiCurr.bMinute,
              tiCurr.bSecond);
* /
      sprintf(szHi," %02bu:%02bu %02bu.%02bu.%02bu ",
                     tiCurr.bHour,
                     tiCurr.bMinute,
                     tiCurr.bDay,   
                     tiCurr.bMonth,
                     tiCurr.bYear);

      sprintf(szLo," %02bu:%02bu %02bu.%02bu.%02bu ",
                     tiKey.bHour,
                     tiKey.bMinute,
                     tiKey.bDay,   
                     tiKey.bMonth,
                     tiKey.bYear);

      // запись прошедшего времени
      tiPrev = tiCurr;
    }
  }
}



// программа обработки переходов в виртуальном времени с переходами на сезонное время
void    InitNexttime(void)
{
  if (GetLabelRTC() == 0) TestError(szBadRTC1);

  PGetCurrTimeDate();
  if (TrueCurrTimeDate() == 0) // TestError(szBadRTC2);
  {
    ShowHi(szAlarm); 
    ShowLo(szBadRTC2); LongBeep(); DelayMsg();
    return;
  }

  fSummer = 0;
  fWinter = 0;

  AddSysRecord(EVE_PREVNEXTTIME2);
  NexttimeOff();
  AddSysRecord(EVE_POSTNEXTTIME);

  if (fSummer == 1)
  {
    if (++tiCurr.bHour >= 24)
    {
      tiCurr.bHour = 0;

      tiAlt = tiCurr;
      if (++tiCurr.bDay > DaysInMonth())
      {
        tiCurr.bDay = 1;
        if (++tiCurr.bMonth > 12)
        {
          tiCurr.bMonth = 1;
          tiCurr.bYear++;
        }
      }
    }

    tiSetRTC = tiCurr;
    SetCurrTimeDate();
  }

  if (fWinter == 1)
  {
    if (tiCurr.bHour > 0)
      tiCurr.bHour--;
    else
    {
      tiCurr.bHour = 23;
      if (tiCurr.bDay > 1)
        tiCurr.bDay--;
      else
      {
        if (tiCurr.bMonth > 1)
          tiCurr.bMonth--;
        else
        {
          tiCurr.bMonth = 12;  
          tiCurr.bYear--; 
        }

        tiAlt = tiCurr;
        tiCurr.bDay = DaysInMonth();             
      } 
    }

    tiSetRTC = tiCurr;
    SetCurrTimeDate();
  }
}



// программа обработки переходов в реальном времени
void    Nexttime(void)
{
  if (GetLabelRTC() == 0) return;

  PGetCurrTimeDate();
  if (TrueCurrTimeDate() == 0) return;

  if (tiCurr.bSecond != tiGetRTC.bSecond)
  {
    // чтение текущего времени
    tiCurr = tiGetRTC;

    if (enGlobal != GLB_PROGRAM)
    {
      fActive = 1;
      ProcessTime();
    }
    else
    {
      fProfile = 0;
      fCurrent = 0;

      ClearNewTime();
    }

    // запись прошедшего времени
    tiPrev = tiCurr;
  }
}
*/
