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
#include "cntmon32.h"



#ifndef SKIP_32


// энерги€ всего
static double           mpdbEngAbs[MAX_LINE_N32];

// энерги€ за текущие сутки
static double           mpdbEngDayCurr[MAX_LINE_N32];



bool    ReadEngAbs_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<MAX_LINE_N32; i++)
  {
    mpdbEngAbs[i] = 0;
  }

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
      for (i=0; i<MAX_LINE_N32; i++)
      {
        mpdbEngAbs[i] += PopLong32();
      }
    }
  }

  if (UseMonitor())
  {
    MonitorString("\n eng abs.");
    for (i=0; i<MAX_LINE_N32; i++)
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

//  if (ReadEngDayCurr_Full(70) == false) return GetDouble2Error();


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
