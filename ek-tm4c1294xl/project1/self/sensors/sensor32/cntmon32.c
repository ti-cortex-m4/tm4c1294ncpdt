/*------------------------------------------------------------------------------
CNTMON32.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../time/delay.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_messages.h"
#include "automatic32.h"
#include "device32.h"
#include "profile32.h"
#include "cntmon32.h"



#ifndef SKIP_32


// сумма энергии по мес€цам
static double           dbEngSum;

// индексы доступных мес€цев
static uchar            mpbIdxMon[13];

// энерги€ всего
static double           dbEngAbs;

// энерги€ за текущие сутки
static double           dbEngDayCurr;



void    QueryMonthIndexH(uchar  ibMon)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(32); // "энерги€ на расчЄтный период"
  PushCharCod(0);
  PushCharCod(ibMon*2);

  Query32(3+20+1, 3+3+1);
}



static status ReadTop_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    DelayOff();
    QueryTop32();

    ShowPercent(bPercent);

    if (Input32() == SER_GOODCHECK) break;
    if (fKey == true) return ST_BADDIGITAL;
  }

  if (r == bMINORREPEATS) return ST_BADDIGITAL;
  else
  {
//    if (Checksum32(14) == false) { Clear(); sprintf(szLo+1,"ошибка CRC: H5"); Delay(1000); return ST_BAD_CRC; }
  }

  return ST_OK;
}


static status ReadHeader_Full(void)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    DelayOff();
    QueryHeader32();

//    ShowPercent(bPercent);

    if (Input32() == SER_GOODCHECK) break;
    if (fKey == true) return ST_BADDIGITAL;
  }

  if (r == bMINORREPEATS) return ST_BADDIGITAL;
  else
  {
//    if (Checksum32(14) == false) { Clear(); sprintf(szLo+1,"ошибка CRC: H5"); Delay(1000); return ST_BAD_CRC; }
  }

  return ST_OK;
}



static bool ReadHeader(void)
{
  InitPop(3);

  time ti = ReadPackTime32();
  bool f = ((ti.bDay   == tiCurr.bDay)   &&
            (ti.bMonth == tiCurr.bMonth) &&
            (ti.bYear  == tiCurr.bYear));

  sprintf(szLo+1,"%02u:%02u %02u.%02u.%02u", ti.bHour,ti.bMinute, ti.bDay,ti.bMonth,ti.bYear);

  MonitorString("\n");
  MonitorTime(ti);

  uint w = PopIntBig();
  MonitorIntDec(w);

  if (f) dbEngDayCurr += (double)w/1000;

  return f;
}


static status ReadEngDayCurr_Full(uchar  bPercent)
{
  dbEngDayCurr = 0;

  status st;
  if ((st = ReadTop_Full(60)) != ST_OK) return st;

  if (ReadTop32() == false) return ST_OK;

  Clear();
  while (true)
  {
    if ((st = ReadHeader_Full()) != ST_OK) return st;
    if (ReadHeader() == false) break;

    if (DecIndex32() == false) return ST_OK;
  }

  return ST_OK;
}



static bool ReadEngAbs_Full(uchar  bPercent)
{
  dbEngAbs = 0;

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryEngAbs32(t);

      ShowPercent(bPercent+t);

      if (Input32() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    else
    {
//      if (Checksum32(14) == false) { Clear(); sprintf(szLo+1,"ошибка CRC: H5"); Delay(1000); return GetDouble2Error(); }

      InitPop(3);
      dbEngAbs += (double)PopLongBig()/1000;
    }
  }

  if (UseMonitor())
  {
    MonitorString("\n eng abs.");
    MonitorString("\n"); MonitorLongDec(dbEngAbs*1000);
  }

  return true;
}



static double2 ReadCntCurrMonCan(void)
{
  if (ReadEngAbs_Full(60) == false) return GetDouble2Error();

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
      QueryMonthIndexH(m);

      if (Input32() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    else
    {
//      if (ChecksumH(20) == 0) { sprintf(szLo," ошибка CRC: H0 "); Delay(1000); return(0); }

      InitPop(3+16);
      uchar bMon = PopChar();

      if (bMon == 0)
        mpbIdxMon[m] = 0;
      else
        mpbIdxMon[m] = (10 + bMon)%12 + 1;

      if (bMon != 0)
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



static double2 ReadCntPrevMonCan(uchar  ibMon, time  ti)
{
//  if (ReadEngMonIdx_Full() == 0) return GetDouble2Error();
//  Clear();


  dbEngSum = 0;


//  uchar m = ibMon+1;
//  uchar a = 0;
//  do
//  {
//    if ((m%12 + 1) == ti.bMonth)
//    {
//      if (ReadEngVar_Full(80) == 0) return GetDouble2Error();
//
//      MonitorString("\n eng mon.curr");
//      for (i=0; i<1; i++)
//      {
//        MonitorString("\n i="); MonitorCharDec(i+1);
//        double db = mpdbEngMonCurr[i];
//        MonitorString(" +"); MonitorLongDec(db*1000);
//        mpdbEngSum[i] += db;
//      }
//    }
//    else
//    {
//      uchar idx = SearchEngMonIdx(m%12 + 1);
//      MonitorString("\n index "); MonitorCharDec(idx);
//      if (idx == 0xFF) { Clear(); sprintf(szLo+2,"отсутствует !"); Delay(1000); return GetDouble2Error(); }
//      Clear();
//      if (ReadEngMon_Full(idx) == 0) return GetDouble2Error();
//
//      MonitorString("\n eng mon"); MonitorCharDec(ibMon);
//      for (i=0; i<1; i++)
//      {
//        MonitorString("\n i="); MonitorCharDec(i+1);
//        double db = mpdbEngMon[i];
//        MonitorString(" +"); MonitorLongDec(db*1000);
//        mpdbEngSum[i] += db;
//      }
//    }
//    ShowPercent(80 + a++);
//  }
//  while ((bMONTHS + ti.bMonth - ++m) % bMONTHS != 0);


  if (ReadEngAbs_Full(90) == false) return GetDouble2Error();
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



double2 ReadCntMonCan32(uchar  ibMon)
{
  if (QueryOpen32_Full(25) == 0) GetDouble2Error();

  time2 ti2 = QueryTime32_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;


//  if (NewVersion32())
//  {
    if (ti.bMonth != ibMon+1) // значение счЄтчиков на начало всех мес€цев, кроме текущего
    {
//      if (GetVersion32() == 49)
        return ReadCntPrevMonCan(ibMon, ti);
//      else
//      {
//        Clear(); sprintf(szLo+3,"необходима"); Delay(1000);
//        Clear(); sprintf(szLo+3,"верси€ 49"); Delay(1000);
//        return GetDouble2Error();
//      }
    }
    else // значение счЄтчиков на начало текущих суток
    {
      return ReadCntCurrMonCan();
    }
//  }
//  else
//  {
//    ShowLo(szNoVersion); Delay(1000); return GetDouble2Error();
//  }
}


#endif
