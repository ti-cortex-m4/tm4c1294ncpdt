/*------------------------------------------------------------------------------
AUTOMATIC34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "../../time/calendar.h"
#include "device34.h"
#include "automatic34.h"



void    SetupFactors(factors  fc);



#ifndef SKIP_34

double2 QueryConfig34_Full(void)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryConfig34();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == MaxRepeats()) return GetDouble2Error();
  ShowPercent(50);


  InitPop(27);

  return GetDouble2(PopFloat34(), true);
}


bool    Automatic34(void)
{
  double2 db2 = QueryConfig34_Full();
  if (db2.fValid == false) return false;

  ShowPercent(100);

  mpdbTransEng[ibDig] = db2.dbValue;
  mpdbTransCnt[ibDig] = db2.dbValue;

  mpdbPulseHou[ibDig] = 10000;
  mpdbPulseMnt[ibDig] = 10000;

  return true;
}



time2   QueryTime34_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryTime34();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (r == MaxRepeats()) return GetTime2Error();
  ShowPercent(bPercent);

  return GetTime2(ReadTime34(), true);
}



double2 QueryEngAbs34_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryEngAbs34();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == MaxRepeats()) return GetDouble2Error();
  ShowPercent(bPercent);

  ReadEng34();

  uchar i;
  for (i=0; i<MAX_LINE_N34; i++)
  {
    mpdbChannelsC[i] = (double)mpddwChannels34[i] / 1000000;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



time2   ReadTimeCan34(void)
{
  time2 ti2 = QueryTime34_Full(50);
  if (ti2.fValid == false) return GetTime2Error();


  ti2.tiValue = SecIndexToDate(DateToSecIndex(ti2.tiValue) + (ulong)3600*bTimeZone34);
  tiChannelC = ti2.tiValue;

  uchar i;
  for (i=0; i<MAX_LINE_N34; i++)
  {
    mpboChannelsA[i] = true;
  }

  return GetTime2(ti2.tiValue, true);
}



double2 ReadCntCurr34(void)
{
  double2 db2 = QueryEngAbs34_Full(50);
  if (db2.fValid == false) return GetDouble2Error();


  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_N34; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif
