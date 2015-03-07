/*------------------------------------------------------------------------------
REALTIME_INIT.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../flash/records.h"
#include        "../time/timedate.h"
#include        "../time/rtc.h"
#include        "../time/delay.h"
#include        "../display/display.h"
#include        "../display/lcd.h"
#include        "../hardware/watchdog.h"
#include        "../beep.h"
#include        "../serial/print.h"
#include        "realtime.h"
#include        "realtime_storage.h"



boolean RealtimeOffline(void)
{
uchar   cbDays;
time    tiT;

  cbDays = 0;
  while (1)
  {
    ResetWDT();

    tiT = *GetCurrTimeDate();
    tiCurr.bSecond = tiT.bSecond;

    PrintString("\n"); PrintTime(&tiCurr); PrintTime(&tiT);

    if ((tiCurr.bMinute == tiT.bMinute) &&
        (tiCurr.bHour   == tiT.bHour)   &&
        (tiCurr.bDay    == tiT.bDay)    &&
        (tiCurr.bMonth  == tiT.bMonth)  &&
        (tiCurr.bYear   == tiT.bYear))
    {
    	PrintString("\n Finish OK");
      return TRUE;
    }

    // перевод время в интервалом в минуту
    if (++tiCurr.bMinute >= 60)
    {
      tiCurr.bMinute = 0;
      if (++tiCurr.bHour >= 24)
      {
        tiCurr.bHour = 0;

        if (++cbDays > bMAXDAYS_OFF) return FALSE;

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

    ShowMsgLCD2(0x80, szHi);
    ShowMsgLCD2(0xC0, szLo);

    tiPrev = tiCurr;
  }
}



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

  PrintString("\n 3min.   "); PrintInt(ibSoftMnt); PrintInt(ibHardMnt);
  PrintString("\n 30 min. "); PrintInt(ibSoftHou); PrintInt(iwHardHou);
  PrintString("\n day     "); PrintInt(ibSoftDay); PrintInt(ibHardDay);
  PrintString("\n month   "); PrintInt(ibSoftMon); PrintInt(ibHardMon);

  LoadTimeCurr();

  PrintString("\n tiCurr "); PrintTime(&tiCurr);
  PrintString("\n tiPrev "); PrintTime(&tiPrev);
}


void    DefaultRealtime(void)
{
  ibSoftMnt = 0;
  ibHardMnt = 0;

  ibSoftHou = 0;
  iwHardHou = 0;

  ibSoftDay = 0;
  ibHardDay = 0;

  ibSoftMon = 0;
  ibHardMon = 0;
}


void    InitRealtime(void)
{
//  if (GetLabelRTC() == 0) TestError(szBadRTC1);

  if (TrueCurrTimeDate(GetCurrTimeDate()) == false)
  {
    ShowHi(szAlarm);
    ShowLo(szBadRTC2);

    LongBeep();
    DelayMsg();

    enGlobal = GLB_PROGRAM;
    return;
  }

  if (enGlobal == GLB_WORK)
  {
    LoadRealtime();

    if (TrueCurrTimeDate(&tiCurr) == false)
    {
      ShowHi(szAlarm);
      ShowLo(szBadRTC2); // TODO

      LongBeep();
      DelayMsg();

      enGlobal = GLB_PROGRAM;
      return;
    }

    fSummer = 0;
    fWinter = 0;

    fSeason = 0;

    cbPowerOn++;
    tiPowerOff = tiCurr;

    AddSysRecord(EVE_PREVNEXTTIME2);
    if (RealtimeOffline() == TRUE) {
    } else {
    }
    AddSysRecord(EVE_POSTNEXTTIME);

    tiPowerOn = tiCurr;

    //RealtimeSeason();
  }
  else
  {
    DefaultRealtime();
  }

//  fProfile = 0;
//  fCurrent = 0;
}
