/*------------------------------------------------------------------------------
GPS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_gps.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_correct3.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../keyboard/keyboard.h"
#include "../display/display.h"
#include "../flash/records.h"
#include "../time/rtc.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "gps.h"
//#include        "xdata.h"
//#include        "delay.h"
//#include        "keyboard.h"
//#include        "display.h"
//#include        "ports.h"
//#include        "timedate.h"
//#include        "engine.h"
//#include        "nexttime.h"
//#include        "rtc.h"
//#include        "record.h"



//                                         0123456789ABCDEF
static char const       szTimeGPS[]      = "Время GPS       ",
                        szDeltaTimeGPS[] = "Время GPS       ",
                        szTimeDateGPS[]  = "Дата GPS        ",
                        szVersionGPS[]   = "Версия GPS      ",
                        szBadFormatGPS[] = "ошибка формата !",
                        szBadDateGPS[]   = " ошибка даты !  ",
                        szBadTimeGPS[]   = "ошибка режима ! ";



void    InitGPS(void)
{
  if (bPortGPS > bPORTS) bPortGPS = 0;
}



void    ResetGPS(void)
{
uchar   i;

  bPortGPS = 0;

  for (i=0; i<48; i++) mpboGPSRun[i] = false;
  mpboGPSRun[12] = true;
  mpboGPSRun[36] = true;

  bGMT = 2;

  boSeasonGPS = true;
}



bool    ShowStatusGPS(void)
{
  if (bStatusGPS == 0) return(1);

  Clear();
  sprintf(szLo+2,"состояние: %bu",bStatusGPS);

  DelayMsg(); Clear();
  return(0);
}



void    QueryTimeGPS(void)
{
  InitPush();

  PushChar(0xD0);          
  PushChar(0x0D);
  PushChar(7);
  PushChar(0);
  PushChar(1);         

  QueryIO(5+15+2, 5+0+2);
}



void    CalcGMT(void)
{
uchar   i,j;

  j = bGMT;
  if ((bSeasonCurr == 0) && (boSeasonGPS == true)) j++;

  for (i=0; i<j; i++)
  {
    if (++tiAlt.bHour >= 24)
    {
      tiAlt.bHour = 0;
      if (++tiAlt.bDay > DaysInMonth())
      {
        tiAlt.bDay = 1;
        if (++tiAlt.bMonth > 12)
        {
          tiAlt.bMonth = 1;
          tiAlt.bYear++;
        }
      }
    }
  }
}



void    ReadTimeAltGPS(void)
{
  bSeasonCurr = SeasonCurr();

  InitPop(5);
  bStatusGPS = PopChar();

  tiAlt.bSecond = PopChar();
  tiAlt.bMinute = PopChar();
  tiAlt.bHour   = PopChar();
  tiAlt.bDay    = PopChar();
  tiAlt.bMonth  = PopChar();
  tiAlt.bYear   = PopChar();

  tiGPS = tiAlt;
  bVersionMaxGPS = PopChar();
  bVersionMinGPS = PopChar();

  CalcGMT();
}



uchar   ReadTimeDateGPS(void)
{
uchar   i;

  ibPort = bPortGPS-1;

  for (i=0; i<bMINORREPEATS; i++)
  {    
    Delay(100);
    QueryTimeGPS();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(2);
  }

  if (i == bMINORREPEATS) return(0);

  ReadTimeAltGPS();
  return(1);
}



void    ShowTimeDateGPS(bool fShow)
{
  (fShow) ? ShowHi(szTimeDateGPS) : ShowHi(szTimeGPS);

  sprintf(szHi+12,"+%02bu",bGMT);
  if ((SeasonCurr() == 0) && (boSeasonGPS == true)) szHi[15] = '*';

  enKeyboard = KBD_ENTER;
  Clear();

  if (ReadTimeDateGPS() != 1) 
    Error();
  else
  {
    if (ShowStatusGPS() == 1)
    {
      Clear();
      (fShow) ? ShowTimeDate() : ShowTime();
    }
  }
}



void    SetupTimeGPS(void)
{
  if (ReadTimeDateGPS() != 1)
  {
    Error(); 
    DelayInf(); Clear();
  }
  else
  {
    if (ShowStatusGPS() == 1)
    {
      tiSetRTC = tiAlt;
      SetCurrTimeDate();    // дата установлена правильно 

      ReadTimeAltGPS();         

      tiSetRTC = tiAlt;
      SetCurrTimeDate();    // дата и время установлены правильно

      boSetTime = true;
      boSetDate = true;

      OK(); DelayMsg();
    }
  }
}



void    CalcCorrect(void)
{
  if (dwBuffC <   2) mpcwGPSRun[9]++;
  if (dwBuffC <   5) mpcwGPSRun[10]++;
  if (dwBuffC >   5) mpcwGPSRun[11]++;
  if (dwBuffC >  60) mpcwGPSRun[12]++;
  if (dwBuffC > 600) mpcwGPSRun[13]++;
}



bool    SetTimeGPS(void)
{
  mpcwGPSRun[0]++;
  if (ReadTimeDateGPS() != 1)
  {    
    Error(); DelayInf(); Clear(); 
    AddKeyRecord(EVE_GPS_BADLINK); mpcwGPSRun[1]++;
  }
  else
  {
    AddKeyRecord(EVE_GPS_GOODLINK); mpcwGPSRun[2]++;

    if (ShowStatusGPS() == 0)
    { 
      AddKeyRecord(EVE_GPS_BADGPS); mpcwGPSRun[3]++;
    }
    else
    {
      AddKeyRecord(EVE_GPS_GOODGPS_1); mpcwGPSRun[4]++;
      AddKeyRecord(EVE_GPS_GOODGPS_2);

      if (TrueTimeDate() == 0)
      { 
        ShowLo(szBadFormatGPS); DelayMsg(); Clear(); 
        AddKeyRecord(EVE_GPS_BADFORMAT); mpcwGPSRun[5]++; 
      }
      else if ((tiCurr.bDay   != tiAlt.bDay)   ||
               (tiCurr.bMonth != tiAlt.bMonth) ||
               (tiCurr.bYear  != tiAlt.bYear))
      { 
        ShowLo(szBadDateGPS); DelayMsg(); Clear(); 
        AddKeyRecord(EVE_GPS_BADDATE); mpcwGPSRun[6]++; 
      }
      else if (GetCurrHouIndex() != (tiAlt.bHour*2 + tiAlt.bMinute/30))
      { 
        ShowLo(szBadTimeGPS); DelayMsg(); Clear(); 
        AddKeyRecord(EVE_GPS_BADTIME); mpcwGPSRun[7]++; 
       }
      else
      {
        tiPrevCorrect = tiCurr;
        tiPostCorrect = tiAlt;


        tiSetRTC = tiAlt;
        SetCurrTime();
        tiPrev = tiAlt;
              
        OK(); DelayMsg(); Clear(); 
        AddKeyRecord(EVE_GPS_OK); mpcwGPSRun[8]++;


        tiAlt = tiPostCorrect;
        dwBuffC = GetSecondIndex();

        tiAlt = tiPrevCorrect;
        if (dwBuffC > GetSecondIndex())
        {
          dwBuffC = dwBuffC - GetSecondIndex();

          mpcwPosValueCurr[0] += (uint)dwBuffC;
          mpcwPosValueCurr[1] += (uint)dwBuffC;
          mpcwPosCountCurr[0]++;
          mpcwPosCountCurr[1]++;

          CalcCorrect();
        }
        else
        {
          dwBuffC = GetSecondIndex() - dwBuffC;

          mpcwNegValueCurr[0] += (uint)dwBuffC;
          mpcwNegValueCurr[1] += (uint)dwBuffC;
          mpcwNegCountCurr[0]++;
          mpcwNegCountCurr[1]++;

          CalcCorrect();
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

  if ((bPortGPS == 0) || (bPortGPS > bPORTS)) return;

  if ((tiCurr.bDay   == tiSummer.bDay) &&
      (tiCurr.bMonth == tiSummer.bMonth)) return;

  if ((tiCurr.bDay   == tiWinter.bDay) &&
      (tiCurr.bMonth == tiWinter.bMonth)) return;

  i = tiCurr.bMinute/15;
  if ((i == 0) || (i == 2)) return;

  if (mpboGPSRun[ GetCurrHouIndex() ] == false) return;

  AddKeyRecord(EVE_GPS_AUTO);
  CorrectTimeGPS();
}

