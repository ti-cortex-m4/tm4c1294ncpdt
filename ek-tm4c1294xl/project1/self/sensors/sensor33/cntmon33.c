/*------------------------------------------------------------------------------
CNTMON33.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../time/delay.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_messages.h"
#include "../sensor31/automatic31.h"
#include "automatic33.h"
#include "device33.h"
#include "profile33.h"
#include "cntmon33.h"



#ifndef SKIP_33

// сумма энергии по мес€цам
static double           dbEngSum;

// индексы доступных мес€цев
static uchar            mpbIdxMon[13];

// энерги€ за мес€ц
static double           dbEngMon;

// энерги€ всего
static double           dbEngAbs;

// энерги€ за текущий мес€ц
static double           dbEngMonCurr;

// энерги€ за текущие сутки
static double           dbEngDayCurr;



static void QueryEngMonIdx(uchar  ibMon)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  (GetVersion33() == 16) ? PushCharCod(24) : PushCharCod(32); // "энерги€ на расчЄтный период"

  uint w = ibMon*2;
  PushCharCod(w / 0x100);
  PushCharCod(w % 0x100);

  Query33(3+20+1, 3+3+1);
}



static status ReadTop_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    DelayOff();
    QueryTop33();

    ShowPercent(bPercent);

    if (Input33() == SER_GOODCHECK) break;
    if (fKey == true) return ST_BADDIGITAL;
  }

  if (r == bMINORREPEATS) return ST_BADDIGITAL;
  else
  {
    if (Checksum33(GetVersion33() == 16 ? 6 : 8) == false) { ShowLo(szBadCRC); Delay(1000); return ST_BAD_CRC; }
  }

  return ST_OK;
}


static status ReadHeader_Full(void)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    DelayOff();
    QueryHeader33();

    if (Input33() == SER_GOODCHECK) break;
    if (fKey == true) return ST_BADDIGITAL;
  }

  if (r == bMINORREPEATS) return ST_BADDIGITAL;
  else
  {
    if (Checksum33(GetVersion33() == 16 ? 8 : 6) == false) { ShowLo(szBadCRC); Delay(1000); return ST_BAD_CRC; }
  }

  return ST_OK;
}



static bool ReadHeader(void)
{
  InitPop(3);

  time ti = ReadPackTime33();
  bool f = ((ti.bDay   == tiCurr.bDay)   &&
            (ti.bMonth == tiCurr.bMonth) &&
            (ti.bYear  == tiCurr.bYear));

  MonitorString("\n");
  MonitorTime(ti);

  ulong dw = (GetVersion33() == 16) ? PopLong33() : PopInt33();
  MonitorLongDec(dw);

  if (f)
  {
    sprintf(szLo+1,"%02u:%02u %02u.%02u.%02u", ti.bHour,ti.bMinute, ti.bDay,ti.bMonth,ti.bYear);
    dbEngDayCurr += (double)dw/1000;
  }

  return f;
}


static status ReadEngDayCurr_Full(uchar  bPercent)
{
  dbEngDayCurr = 0;

  status st;
  if ((st = ReadTop_Full(60)) != ST_OK) return st;

  if (ReadTop33() == false) return ST_OK;

  Clear();
  while (true)
  {
    if ((st = ReadHeader_Full()) != ST_OK) return st;
    if (ReadHeader() == false) break;

    if (DecIndex33() == false) return ST_OK;
  }

  return ST_OK;
}



static bool ReadEngVar_Full(uchar  bPercent)
{
  dbEngAbs = 0;
  dbEngMonCurr = 0;

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryEngAbs33(t);

      ShowPercent(bPercent+t);

      if (Input33() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    else
    {
      if (Checksum33(14) == false) { ShowLo(szBadCRC); Delay(1000); return false; }

      InitPop(3);
      dbEngAbs += (double)PopLong33()/1000;
      dbEngMonCurr += (double)PopLong33()/1000;
    }
  }

  if (UseMonitor())
  {
    MonitorString("\n eng abs.");
    MonitorString("\n"); MonitorLongDec(dbEngAbs*1000);
    MonitorString("\n eng mon.curr");
    MonitorString("\n"); MonitorLongDec(dbEngMonCurr*1000);
  }

  return true;
}



static double2 ReadCntCurrMonCan(void)
{
  if (ReadEngVar_Full(60) == false) return GetDouble2Error();

  if (ReadEngDayCurr_Full(70) != ST_OK) return GetDouble2Error();


  double dbTrans = mpdbTransCnt[ibDig];

  mpdbChannelsC[0] = dbEngAbs - dbEngDayCurr; // энерги€ всего минус энерги€ за текущие сутки равно энергии на начало текущих суток
  mpdbChannelsC[0] *= dbTrans;
  mpboChannelsA[0] = true;

  if (UseMonitor())
  {
    MonitorString("\n cnt mon.curr");
    MonitorString("\n"); MonitorLongDec(dbEngAbs*1000);
    MonitorString("-"); MonitorLongDec(dbEngDayCurr*1000);
    MonitorString("="); MonitorLongDec((dbEngAbs - dbEngDayCurr)*1000);
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



static bool ReadEngMonIdx_Full(void)
{
  uchar m;
  for (m=0; m<=12; m++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryEngMonIdx(m);

      if (Input33() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    else
    {
      if (Checksum33(20) == 0) { ShowLo(szBadCRC); Delay(1000); return false; }

      MonitorString("\n month "); MonitorCharDec(m);

      InitPop(3+16);

      uchar bMonth = PopChar();
      uchar bYear  = PopChar();
      MonitorString(" time "); MonitorCharDec(bMonth); MonitorString("."); MonitorCharDec(bYear);

      if ((bMonth == 0) || (bYear == 0))
        mpbIdxMon[m] = 0;
      else
      {
        ulong i1 = DateToMonIndex(tiCurr);

        time ti = tiZero;
        ti.bMonth = bMonth;
        ti.bYear  = bYear;
        ulong i2 = DateToMonIndex(ti);

        MonitorString("\n"); MonitorLongDec(i1); MonitorString(" ? "); MonitorLongDec(i2);

        if ((i2 <= i1) && (i2 + 12 > i1))
          mpbIdxMon[m] = (10 + bMonth)%12 + 1;
        else
          mpbIdxMon[m] = 0;
      }

      MonitorString(" index "); MonitorCharDec(mpbIdxMon[m]);

      if (bMonth != 0)
        { Clear(); sprintf(szLo+2,"найдено: %-2u", mpbIdxMon[m]); }
      else
        { Clear(); sprintf(szLo+1,"пусто: %2u-%-2u",m,12); }
    }
  }

  return(1);
}


static uchar SearchEngMonIdx(uchar  bMon)
{
  Clear(); sprintf(szLo+1,"требуетс€: %-2u", bMon); DelayInf();

  uchar m;
  for (m=0; m<=12; m++)
    if (mpbIdxMon[m] == bMon)
      return m;

  return 0xFF;
}



static bool ReadEngMon_Full(uchar  ibMon)
{
  dbEngMon = 0;

  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryEngMonIdx(ibMon);

      if (Input33() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    else
    {
      if (Checksum33(20) == 0) { ShowLo(szBadCRC); Delay(1000); return false; }

      InitPop(3);
      dbEngMon += (double)PopLong33()/1000;
      dbEngMon += (double)PopLong33()/1000;
      dbEngMon += (double)PopLong33()/1000;
      dbEngMon += (double)PopLong33()/1000;
    }
  }

  if (UseMonitor())
  {
    MonitorString("\n eng mon."); MonitorCharDec(ibMon);
    MonitorString(" "); MonitorLongDec(dbEngMon*1000);
  }

  return true;
}



static double2 ReadCntPrevMonCan(uchar  ibMon, time  ti)
{
  if (ReadEngMonIdx_Full() == 0) return GetDouble2Error();
  Clear();


  dbEngSum = 0;


  uchar m = ibMon+1;
  uchar a = 0;
  do
  {
    if ((m%12 + 1) == ti.bMonth)
    {
      if (ReadEngVar_Full(80) == 0) return GetDouble2Error();

      MonitorString("\n eng mon.curr");
      double db = dbEngMonCurr;
      MonitorString(" +"); MonitorLongDec(db*1000);
      dbEngSum += db;
    }
    else
    {
      uchar idx = SearchEngMonIdx(m%12 + 1);
      MonitorString("\n index "); MonitorCharDec(idx);
      if (idx == 0xFF) { Clear(); sprintf(szLo+2,"отсутствует !"); Delay(1000); return GetDouble2Error(); }
      Clear();
      if (ReadEngMon_Full(idx) == 0) return GetDouble2Error();

      MonitorString("\n eng mon."); MonitorCharDec(ibMon);
      double db = dbEngMon;
      MonitorString(" +"); MonitorLongDec(db*1000);
      dbEngSum += db;
    }
    ShowPercent(80 + a++);
  }
  while ((bMONTHS + ti.bMonth - ++m) % bMONTHS != 0);


  if (ReadEngVar_Full(90) == false) return GetDouble2Error();
  ShowPercent(99);


  double dbTrans = mpdbTransCnt[ibDig];

  mpdbChannelsC[0] = dbEngAbs - dbEngSum;
  mpdbChannelsC[0] *= dbTrans;
  mpboChannelsA[0] = true;

  if (UseMonitor())
  {
    MonitorString("\n cnt mon."); MonitorCharDec(ibMon);
    MonitorString("\n"); MonitorLongDec(dbEngAbs*1000);
    MonitorString("-"); MonitorLongDec(dbEngSum*1000);
    MonitorString("="); MonitorLongDec((dbEngAbs - dbEngSum)*1000);
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



double2 ReadCntMonCan33(uchar  ibMon)
{
  if (QueryOpen33_Full(25) == 0) GetDouble2Error();

  time2 ti2 = QueryTime33_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;


    if (ti.bMonth != ibMon+1) // значение счЄтчиков на начало всех мес€цев, кроме текущего
    {
      if ((GetVersion33() == 16) || (GetVersion33() == 18))
        return ReadCntPrevMonCan(ibMon, ti);
      else
      {
        Clear(); sprintf(szLo+3,"необходимы"); Delay(1000);
        Clear(); sprintf(szLo+2,"версии 16,18"); Delay(1000);
        return GetDouble2Error();
      }
    }
    else // значение счЄтчиков на начало текущих суток
    {
      return ReadCntCurrMonCan();
    }
}

#endif
