/*------------------------------------------------------------------------------
REALTIME_INIT.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "realtime_storage.h"


/*
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
*/



void    InitRealtime(void)
{
  if (enGlobal == GLB_WORK)
  {
    LoadPointersMnt();
    LoadPointersHou();
    LoadPointersDay();
    LoadPointersMon();

    LoadTimeCurr();
  }
}
