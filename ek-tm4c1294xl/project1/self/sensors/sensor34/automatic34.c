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
#include "time34.h"
#include "energy34.h"
#include "energy_dates34.h"
#include "energy_day34.h"
#include "energy_mon34.h"
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

  ReadEngWithTrans34();

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



time2   ReadTimeCan34(void)
{
  time2 ti2 = QueryTime34_Full(50);
  if (ti2.fValid == false) return GetTime2Error();


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

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



double2 ReadCntMonCan34(uchar  ibMon)
{
  time2 ti2 = QueryTime34_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();

  if (QueryEngDates34_Full(60) == 0) return GetDouble2Error();

  if (ti2.tiValue.bMonth != ibMon+1) // �������� ��������� �� ����� ���� �������, ����� ��������
  {
    time ti = ti2.tiValue;
    ti.bSecond = 0;
    ti.bMinute = 0;
    ti.bHour   = 0;
    ti.bDay    = 1;

    uchar m = (ibMon+1) % 12 + 1;
    ti.bYear   = (m > ti.bMonth) ? ti.bYear-1 : ti.bYear;
    ti.bMonth  = m;

    if (HasEngMon34(ti) == 0) {
      Clear();
      sprintf(szLo+1,"����� %02u.%02u ?", ti.bMonth,ti.bYear);
      Delay(1000);
      return GetDouble2Error();
    } else {
      return QueryEngMon34_Full(ti, 80);
    }
  }
  else // �������� ��������� �� ������ ������� �����
  {
    time ti = ti2.tiValue;
    ti.bSecond = 0;
    ti.bMinute = 0;
    ti.bHour   = 0;

    if (HasEngDay34(ti) == 0) {
      Clear();
      sprintf(szLo+1,"����� %02u.%02u.%02u ?", ti.bDay,ti.bMonth,ti.bYear);
      Delay(1000);
      return GetDouble2Error();
    } else {
      return QueryEngDay34_Full(ti, 70);
    }
  }
}

#endif
