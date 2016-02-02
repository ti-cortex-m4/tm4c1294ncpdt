/*------------------------------------------------------------------------------
CNTMON31.C


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
#include "automatic31.h"
#include "device31.h"
#include "cntmon31.h"



#ifndef SKIP_31


// сумма энергии по мес€цам
static double           mpdbEngSum[6];

// индексы доступных мес€цев
static uchar            mpbIdxMon[13];

// энерги€ за мес€ц
static double           mpdbEngMon[6];

// энерги€ по временным интервалам
static double           mpdbEngAbs[6],
                        mpdbEngMonCurr[6], mpdbEngMonPrev[6],
                        mpdbEngDayCurr[6], mpdbEngDayPrev[6];



static void QueryEngVar(uchar  ibTrf) // энерги€ за текущий/предыдущий мес€ц и текущие/предыдущие сутки
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(0x04); // "накопленна€ энерги€ (по тарифам)"
  PushCharCod(0x00);
  PushCharCod(ibTrf);

  Query31(3+4+8*24+2+1, 3+3+1);
}


static void QueryEngAbs(uchar  ibTrf) // энерги€ всего
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(0x05); // "накопленна€ энерги€ всего (по тарифам)"
  PushCharCod(0x00);
  PushCharCod(ibTrf);

  Query31(3+4+8*6+2+1, 3+3+1);
}


static void QueryEngMon(uchar  ibMon, uchar  ibTrf) // энерги€ по мес€цам
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(26); // "срез энергии"

  uint w = ibMon * 72 + ibTrf;
  PushCharCod(w / 0x100);
  PushCharCod(w % 0x100);

  Query31(3+102+1, 3+3+1);
}



static double PopEng(void)
{
  return PopDouble31()/1000;
}


static bool ValidPackTime(void)
{
  time ti = ReadPackTime31();

  if ((ti.bSecond == 0) &&
      (ti.bMinute == 0) &&
      (ti.bHour   == 0) &&
      (ti.bDay    == 0) &&
      (ti.bMonth  == 0) &&
      (ti.bYear   == 0)) return false;

  return true;
}



static bool ReadEngVar_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<6; i++)
  {
    mpdbEngMonCurr[i] = 0;
    mpdbEngMonPrev[i] = 0;
    mpdbEngDayCurr[i] = 0;
    mpdbEngDayPrev[i] = 0;
  }

  uchar t;
  for (t=0; t<bTARIFFS; t++) // в счЄтчике 72 тарифа
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryEngVar(t);

      ShowPercent(bPercent+t);

      if (Input31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    else
    {
      if (ValidPackTime() == 0) break; // тариф не используетс€
      else
      {
        uint wCRC = MakeCrc16Bit31InBuff(3, 196);
        if (wCRC != InBuff(199) + InBuff(200)*0x100) { ShowLo(szBadCRC); Delay(1000); return false; }

        for (i=0; i<6; i++)
        {
          mpdbEngMonCurr[i] += PopEng();
          mpdbEngMonPrev[i] += PopEng();
          mpdbEngDayCurr[i] += PopEng();
          mpdbEngDayPrev[i] += PopEng();
        }
      }
    }
  }

  if (UseMonitor())
  {
    MonitorString("\n eng mon.curr/prev day.curr/prev");
    for (i=0; i<6; i++)
    {
      MonitorString("\n i="); MonitorCharDec(i+1);
      MonitorString(" "); MonitorLongDec(mpdbEngMonCurr[i]*1000);
      MonitorString(" ");MonitorLongDec(mpdbEngMonPrev[i]*1000);
      MonitorString(" ");MonitorLongDec(mpdbEngDayCurr[i]*1000);
      MonitorString(" ");MonitorLongDec(mpdbEngDayPrev[i]*1000);
    }
  }

  return true;
}


bool    ReadEngAbs_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<6; i++)
  {
    mpdbEngAbs[i] = 0;
  }

  uchar t;
  for (t=0; t<bTARIFFS; t++) // в счЄтчике 72 тарифа
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryEngAbs(t);

      ShowPercent(bPercent+t);

      if (Input31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    else
    {
      if (ValidPackTime() == 0) break; // тариф не используетс€
      else
      {
        uint wCRC = MakeCrc16Bit31InBuff(3, 52);
        if (wCRC != InBuff(55) + InBuff(56)*0x100) { ShowLo(szBadCRC); Delay(1000); return false; }

        for (i=0; i<6; i++)
        {
          mpdbEngAbs[i] += PopEng();
        }
      }
    }
  }

  if (UseMonitor())
  {
    MonitorString("\n eng abs.");
    for (i=0; i<6; i++)
    {
      MonitorString("\n i="); MonitorCharDec(i+1);
      MonitorString(" "); MonitorLongDec(mpdbEngAbs[i]*1000);
    }
  }

  return true;
}


static double2 ReadCntCurrMonCan(void)
{
  if (ReadEngAbs_Full(60) == false) return GetDouble2Error();

  if (ReadEngVar_Full(70) == false) return GetDouble2Error();


  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<6; i++)
  {
    mpdbChannelsC[i] = mpdbEngAbs[i] - mpdbEngDayCurr[i]; // энерги€ всего минус энерги€ за текущие сутки равно энергии на начало текущих суток
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  if (UseMonitor())
  {
    MonitorString("\n cnt mon.curr");
    for (i=0; i<6; i++)
    {
      MonitorString("\n i="); MonitorCharDec(i+1);
      MonitorString(" "); MonitorLongDec(mpdbEngAbs[i]*1000);
      MonitorString("-"); MonitorLongDec(mpdbEngDayCurr[i]*1000);
      MonitorString("="); MonitorLongDec((mpdbEngAbs[i] - mpdbEngDayCurr[i])*1000);
    }
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
      QueryEngMon(m, 0);

      if (Input31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    else
    {
      uint wCRC = MakeCrc16Bit31InBuff(3, 100);
      if (wCRC != InBuff(103) + InBuff(104)*0x100) { ShowLo(szBadCRC); Delay(1000); return false; }

      MonitorString("\n month "); MonitorCharDec(m);

      time ti = ReadPackTime31();
      MonitorString(" time "); MonitorTime(ti);

      if (ti.bMonth == 0)
        mpbIdxMon[m] = 0;
      else
        mpbIdxMon[m] = (10 + ti.bMonth)%12 + 1;

      MonitorString(" index "); MonitorCharDec(mpbIdxMon[m]);

      if (ti.bMonth != 0)
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


static bool  ReadEngMon_Full(uchar  ibMon)
{
  uchar i;
  for (i=0; i<6; i++)
  {
    mpdbEngMon[i] = 0;
  }

  uchar t;
  for (t=0; t<bTARIFFS; t++) // в счЄтчике 72 тарифа
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryEngMon(ibMon, t);

      if (Input31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    else
    {
      uint wCRC = MakeCrc16Bit31InBuff(3, 100);
      if (wCRC != InBuff(103) + InBuff(104)*0x100) { ShowLo(szBadCRC); Delay(1000); return false; }

      time ti = ReadPackTime31();
      MonitorString("\n time "); MonitorTime(ti);

      for (i=0; i<6; i++)
      {
        mpdbEngMon[i] += PopEng();
      }
    }
  }

  if (UseMonitor())
  {
    MonitorString("\n eng mon."); MonitorCharDec(ibMon);
    for (i=0; i<6; i++)
    {
      MonitorString("\n i="); MonitorCharDec(i+1);
      MonitorString(" "); MonitorLongDec(mpdbEngMon[i]*1000);
    }
  }

  return true;
}


static double2 ReadCntPrevMonCan(uchar  ibMon, time  ti)
{
  if (ReadEngMonIdx_Full() == 0) return GetDouble2Error();
  Clear();


  uchar i;
  for (i=0; i<6; i++)
  {
    mpdbEngSum[i] = 0;
  }


  uchar m = ibMon+1;
  uchar a = 0;
  do
  {
    if ((m%12 + 1) == ti.bMonth)
    {
      if (ReadEngVar_Full(80) == 0) return GetDouble2Error();

      MonitorString("\n eng mon.curr");
      for (i=0; i<6; i++)
      {
        MonitorString("\n i="); MonitorCharDec(i+1);
        double db = mpdbEngMonCurr[i];
        MonitorString(" +"); MonitorLongDec(db*1000);
        mpdbEngSum[i] += db;
      }
    }
    else
    {
      uchar idx = SearchEngMonIdx(m%12 + 1);
      MonitorString("\n index "); MonitorCharDec(idx);
      if (idx == 0xFF) { Clear(); sprintf(szLo+2,"отсутствует !"); Delay(1000); return GetDouble2Error(); }
      Clear();
      if (ReadEngMon_Full(idx) == 0) return GetDouble2Error();

      MonitorString("\n eng mon"); MonitorCharDec(ibMon);
      for (i=0; i<6; i++)
      {
        MonitorString("\n i="); MonitorCharDec(i+1);
        double db = mpdbEngMon[i];
        MonitorString(" +"); MonitorLongDec(db*1000);
        mpdbEngSum[i] += db;
      }
    }
    ShowPercent(80 + a++);
  }
  while ((bMONTHS + ti.bMonth - ++m) % bMONTHS != 0);


  if (ReadEngAbs_Full(90) == false) return GetDouble2Error();
  ShowPercent(99);


  double dbTrans = mpdbTransCnt[ibDig];

  for (i=0; i<6; i++)
  {
    mpdbChannelsC[i] = mpdbEngAbs[i] - mpdbEngSum[i];
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  if (UseMonitor())
  {
    MonitorString("\n cnt mon."); MonitorCharDec(ibMon);
    for (i=0; i<6; i++)
    {
      MonitorString("\n i="); MonitorCharDec(i+1);
      MonitorString(" "); MonitorLongDec(mpdbEngAbs[i]*1000);
      MonitorString("-"); MonitorLongDec(mpdbEngSum[i]*1000);
      MonitorString("="); MonitorLongDec((mpdbEngAbs[i] - mpdbEngSum[i])*1000);
    }
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



double2 ReadCntMonCan31(uchar  ibMon)
{
  if (QueryOpen31_Full(25) == 0) GetDouble2Error();

  time2 ti2 = QueryTime31_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;


  if (NewVersion31())
  {
    if (ti.bMonth != ibMon+1) // значение счЄтчиков на начало всех мес€цев, кроме текущего
    {
      if (GetVersion31() == 49)
        return ReadCntPrevMonCan(ibMon, ti);
      else
      {
        Clear(); sprintf(szLo+3,"необходима"); Delay(1000);
        Clear(); sprintf(szLo+3,"верси€ 49"); Delay(1000);
        return GetDouble2Error();
      }
    }
    else // значение счЄтчиков на начало текущих суток
    {
      return ReadCntCurrMonCan();
    }
  }
  else
  {
    ShowLo(szNoVersion); Delay(1000); return GetDouble2Error();
  }
}


#endif
