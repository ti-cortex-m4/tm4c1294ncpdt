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


// энерги€ всего
static double           dbEngAbs;

// энерги€ за текущие сутки
static double           dbEngDayCurr;



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


static status ReadHeader_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    DelayOff();
    QueryHeader32();

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



static void ReadHeader(void)
{
  InitPop(3);
  time ti = ReadPackTime32();

  MonitorString("\n");
  MonitorTime(ti);

  uint w = PopIntBig();
  MonitorIntDec(w);

  dbEngDayCurr += w;
}


static status ReadEngDayCurr_Full(uchar  bPercent)
{
  dbEngDayCurr = 0;

  status st;
  if ((st = ReadTop_Full(60)) != ST_OK) return st;

  if (ReadTop32() == false) return ST_OK;

  while (true)
  {
    if ((st = ReadHeader_Full(60)) != ST_OK) return st;
    ReadHeader();

    if (DecIndex32() == false) return ST_OK;
  }

//  return ST_OK;
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



double2 ReadCntMonCan32(uchar  ibMon)
{
  if (QueryOpen32_Full(25) == 0) GetDouble2Error();

//  time2 ti2 = QueryTime32_Full(50);
//  if (ti2.fValid == false) return GetDouble2Error();
//  time ti = ti2.tiValue;


//  if (NewVersion32())
//  {
//    if (ti.bMonth != ibMon+1) // значение счЄтчиков на начало всех мес€цев, кроме текущего
//    {
//      if (GetVersion32() == 49)
//        return ReadCntPrevMonCan(ibMon, ti);
//      else
//      {
//        Clear(); sprintf(szLo+3,"необходима"); Delay(1000);
//        Clear(); sprintf(szLo+3,"верси€ 49"); Delay(1000);
//        return GetDouble2Error();
//      }
//    }
//    else // значение счЄтчиков на начало текущих суток
//    {
      return ReadCntCurrMonCan();
//    }
//  }
//  else
//  {
//    ShowLo(szNoVersion); Delay(1000); return GetDouble2Error();
//  }
}


#endif
