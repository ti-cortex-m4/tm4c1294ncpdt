/*------------------------------------------------------------------------------
GPS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../memory/mem_gps.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_program.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_correct1.h"
#include "../memory/mem_correct3.h"
#include "../realtime/realtime.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../flash/records.h"
#include "../time/rtc.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "../time/timedate_display.h"
#include "../time/decret.h"
#include "../settings.h"
#include "gps.h"



//                                         0123456789ABCDEF
char const              szTimeGPS[]      = "Время GPS       ",
                        szDeltaTimeGPS[] = "Время GPS       ",
                        szTimeDateGPS[]  = "Дата GPS        ",
                        szVersionGPS[]   = "Версия GPS      ",
                        szBadFormatGPS[] = "ошибка формата !",
                        szBadDateGPS[]   = " ошибка даты !  ",
                        szBadTimeGPS[]   = "ошибка режима ! ";



cache const             chPortGps = {PORT_GPS, &bPortGps, sizeof(uchar)};
cache const             chGmtGps = {GMT_GPS, &bGmtGps, sizeof(uchar)};
cache const             chSeasonGps = {SEASON_GPS, &boSeasonGps, sizeof(bool)};



void    InitGPS(void)
{
  LoadCacheChar(&chPortGps, 0, bPORTS, 0);
  LoadCacheChar(&chGmtGps, 0, 13, 2);
  LoadCacheBool(&chSeasonGps, true);
}



void    ResetGPS(void)
{
  bPortGps = 0;
  SaveCache(&chPortGps);

  uchar i;
  for (i=0; i<48; i++) mpboGpsSchedule[i] = false;
  mpboGpsSchedule[12] = true;
  mpboGpsSchedule[36] = true;

  bGmtGps = 2;
  SaveCache(&chGmtGps);

  boSeasonGps = true;
  SaveCache(&chSeasonGps);
}



bool    ShowStatusGPS(void)
{
  if (bStatusGps == 0) return(1);

  Clear(); sprintf(szLo+2,"состояние: %u",bStatusGps);

  DelayMsg(); Clear();
  return(0);
}



void    QueryTimeGPS(void)
{
  InitPush(0);

  PushChar(0xD0);          
  PushChar(0x0D);
  PushChar(7);
  PushChar(0);
  PushChar(1);         

  QueryIO(5+15+2, 5+0+2);
}



time    CalcGMT(time  ti)
{
  uchar j = bGmtGps;
  if ((bSeasonCurr == 0) && (boSeasonGps == true)) j++;

  uchar i;
  for (i=0; i<j; i++)
  {
    if (++ti.bHour >= 24)
    {
      ti.bHour = 0;
      if (++ti.bDay > GetDaysInMonthYM(ti.bYear, ti.bMonth))
      {
        ti.bDay = 1;
        if (++ti.bMonth > 12)
        {
          ti.bMonth = 1;
          ti.bYear++;
        }
      }
    }
  }

  return ti;
}



time    ReadTimeGPS(void)
{
  bSeasonCurr = SeasonCurr();

  InitPop(5);
  bStatusGps = PopChar();

  time ti;

  ti.bSecond = PopChar();
  ti.bMinute = PopChar();
  ti.bHour   = PopChar();
  ti.bDay    = PopChar();
  ti.bMonth  = PopChar();
  ti.bYear   = PopChar();

  tiGps = ti;
  bVersionMaxGps = PopChar();
  bVersionMinGps = PopChar();

  return CalcGMT(ti);
}



time2   ReadTimeDateGPS(void)
{
  ibPort = bPortGps-1;

  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {    
    Delay(100);
    QueryTimeGPS();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return GetTime2(tiZero, false);
  }

  if (i == bMINORREPEATS) return GetTime2(tiZero, false);

  return GetTime2(ReadTimeGPS(), true);
}



void    ShowTimeDateGPS(bool  fShowTimeDate)
{
  (fShowTimeDate) ? ShowHi(szTimeDateGPS) : ShowHi(szTimeGPS);

  sprintf(szHi+12,"+%02u",bGmtGps);
  if ((SeasonCurr() == 0) && (boSeasonGps == true)) szHi[15] = '*';

  enKeyboard = KBD_ENTER;
  Clear();

  time2 ti2 = ReadTimeDateGPS();
  if (ti2.fValid == false)
    Error();
  else
  {
    if (ShowStatusGPS() == 1)
    {
      Clear();
      (fShowTimeDate) ? ShowTimeDate(ti2.tiValue) : ShowTime(ti2.tiValue);
    }
  }
}



void    SetupTimeGPS(void)
{
  time2 ti2 = ReadTimeDateGPS();
  time ti = ti2.tiValue;

  if (ti2.fValid == false)
  {
    Error(); DelayInf(); Clear();
  }
  else
  {
    if (ShowStatusGPS() == 1)
    {
      SetCurrTimeDate(ti);    // дата установлена правильно

      ReadTimeGPS();

      SetCurrTimeDate(ti);    // дата и время установлены правильно

      boSetTime = true;
      SaveCache(&chSetTime);

      boSetDate = true;
      SaveCache(&chSetDate);

      OK(); DelayMsg();
    }
  }
}



void    CalcCorrect(ulong  dw)
{
  if (dw <   2) mpcwGpsSchedule[9]++;
  if (dw <   5) mpcwGpsSchedule[10]++;
  if (dw >   5) mpcwGpsSchedule[11]++;
  if (dw >  60) mpcwGpsSchedule[12]++;
  if (dw > 600) mpcwGpsSchedule[13]++;
}



bool    SetTimeGPS(void)
{
  mpcwGpsSchedule[0]++;

  time2 ti2 = ReadTimeDateGPS();
  time ti = ti2.tiValue;

  if (ti2.fValid == false)
  {    
    Error(); DelayInf(); Clear(); 
    AddKeyRecord(EVE_GPS_BADLINK); mpcwGpsSchedule[1]++;
  }
  else
  {
    AddKeyRecord(EVE_GPS_GOODLINK); mpcwGpsSchedule[2]++;

    if (ShowStatusGPS() == 0)
    { 
      AddKeyRecord(EVE_GPS_BADGPS); mpcwGpsSchedule[3]++;
    }
    else
    {
      AddKeyRecord(EVE_GPS_GOODGPS_1); mpcwGpsSchedule[4]++;
      AddKeyRecord(EVE_GPS_GOODGPS_2);

      if (ValidTimeDate(ti) == 0)
      { 
        ShowLo(szBadFormatGPS); DelayMsg(); Clear(); 
        AddKeyRecord(EVE_GPS_BADFORMAT); mpcwGpsSchedule[5]++; 
      }
      else if ((tiCurr.bDay   != ti.bDay)   ||
               (tiCurr.bMonth != ti.bMonth) ||
               (tiCurr.bYear  != ti.bYear))
      { 
        ShowLo(szBadDateGPS); DelayMsg(); Clear(); 
        AddKeyRecord(EVE_GPS_BADDATE); mpcwGpsSchedule[6]++; 
      }
      else if (GetCurrHouIndex() != (ti.bHour*2 + ti.bMinute/30))
      { 
        ShowLo(szBadTimeGPS); DelayMsg(); Clear(); 
        AddKeyRecord(EVE_GPS_BADTIME); mpcwGpsSchedule[7]++; 
       }
      else
      {
        tiPrevCorrect = tiCurr;
        tiPostCorrect = ti;


        SetCurrTime(ti);
        tiPrev = ti;
              
        OK(); DelayMsg(); Clear(); 
        AddKeyRecord(EVE_GPS_OK); mpcwGpsSchedule[8]++;


        ti = tiPostCorrect;
        ulong dw = GetSecondIndex(ti);

        ti = tiPrevCorrect;
        if (dw > GetSecondIndex(ti))
        {
          dw = dw - GetSecondIndex(ti);

          Correct1.mpwPosValueCurr[0] += (uint)dw;
          Correct1.mpwPosValueCurr[1] += (uint)dw;
          Correct1.mpwPosCountCurr[0]++;
          Correct1.mpwPosCountCurr[1]++;

          CalcCorrect(dw);
        }
        else
        {
          dw = GetSecondIndex(ti) - dw;

          Correct1.mpwNegValueCurr[0] += (uint)dw;
          Correct1.mpwNegValueCurr[1] += (uint)dw;
          Correct1.mpwNegCountCurr[0]++;
          Correct1.mpwNegCountCurr[1]++;

          CalcCorrect(dw);
        }

        return 1;
      }
    }
  }

  return 0;
}



void    CorrectTimeGPS(void)
{
  cdwAbsCorrect3++;
  if (SetTimeGPS() == 1) 
  { 
    cdwPosCorrect3++;
    tiPosCorrect3 = *GetCurrTimeDate();
  }
  else 
  {
    cdwPosCorrect3 = 0;
    tiNegCorrect3 = *GetCurrTimeDate();
  }
}



void    RunGPS(void)
{
uchar   i;

  if ((bPortGps == 0) || (bPortGps > bPORTS)) return;

  if ((tiCurr.bDay   == tiSummer.bDay) &&
      (tiCurr.bMonth == tiSummer.bMonth)) return;

  if ((tiCurr.bDay   == tiWinter.bDay) &&
      (tiCurr.bMonth == tiWinter.bMonth)) return;

  i = tiCurr.bMinute/15;
  if ((i == 0) || (i == 2)) return;

  if (mpboGpsSchedule[ GetCurrHouIndex() ] == false) return;

  AddKeyRecord(EVE_GPS_AUTO);
  CorrectTimeGPS();
}

