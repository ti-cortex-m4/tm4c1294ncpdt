/*------------------------------------------------------------------------------
REALTIME_INIT.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../flash/records.h"
#include        "../timedate.h"
#include        "../rtc.h"
#include        "../display/display.h"
#include        "realtime.h"
#include        "realtime_storage.h"



boolean RealtimeOffline(void)
{
uchar   cbDays;
time    tiT;

    cbPowerOn++;
    tiPowerOff = tiCurr;

    cbDays = 0;
    while (1)
    {
      ResetWDT();

      // чтение текущего времени
      tiT = *PGetCurrTimeDate();
      // копируем секунды для последующего сравнения
      tiCurr.bSecond = tiT.bSecond;

      // сохраняем время включения питания
      tiPowerOn = tiT;

      if (tiCurr == tiT) return TRUE;

      // перевод время в интервалом в минуту
      if (++tiCurr.bMinute >= 60)
      {
        tiCurr.bMinute = 0;
        if (++tiCurr.bHour >= 24)
        {
          tiCurr.bHour = 0;

          // предельное время выключения питания
          if (++cbDays > 30) return FALSE;

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

      ProcessTime();

      sprintf(szHi," %02u:%02u %02u.%02u.%02u ",
                     tiCurr.bHour,
                     tiCurr.bMinute,
                     tiCurr.bDay,
                     tiCurr.bMonth,
                     tiCurr.bYear);

      sprintf(szLo," %02u:%02u %02u.%02u.%02u ",
                     tiT.bHour,
                     tiT.bMinute,
                     tiT.bDay,
                     tiT.bMonth,
                     tiT.bYear);

      tiPrev = tiCurr;
    }
}


/*
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

  ...

  ...
}
*/


void    RealtimeSeason(void)
{
  if (fSummer == 1)
  {
    if (++tiCurr.bHour >= 24)
    {
      tiCurr.bHour = 0;

      tiAlt = tiCurr;
      if (++tiCurr.bDay > GetDaysInMonthYM(tiCurr.bYear, tiCurr.bMonth))
      {
        tiCurr.bDay = 1;
        if (++tiCurr.bMonth > 12)
        {
          tiCurr.bMonth = 1;
          tiCurr.bYear++;
        }
      }
    }

    SetCurrTimeDate(&tiCurr);
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

        tiCurr.bDay = GetDaysInMonthYM(tiCurr.bYear, tiCurr.bMonth);
      }
    }

    SetCurrTimeDate(&tiCurr);
  }
}



void    LoadRealtime(void)
{
  LoadPointersMnt();
  LoadPointersHou();
  LoadPointersDay();
  LoadPointersMon();

  LoadTimeCurr();
}


void    DefaultRealtime(void)
{
  ibSoftMnt = 0;

  ibSoftHou = 0;
  iwHardHou = 0;

  ibSoftDay = 0;
  ibHardDay = 0;

  ibSoftMon = 0;
  ibHardMon = 0;
}


void    InitRealtime(void)
{
  if (enGlobal == GLB_WORK)
  {
    LoadRealtime();

    fSummer = 0;
    fWinter = 0;

    fSeason = 0;

    AddSysRecord(EVE_PREVNEXTTIME2);
    RealtimeOffline();
    AddSysRecord(EVE_POSTNEXTTIME);

    RealtimeSeason();
  }
  else
  {
    DefaultRealtime();
  }

//  fProfile = 0;
//  fCurrent = 0;
}
