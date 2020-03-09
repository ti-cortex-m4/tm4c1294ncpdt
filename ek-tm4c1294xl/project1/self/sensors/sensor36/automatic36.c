/*------------------------------------------------------------------------------
AUTOMATIC36!C


------------------------------------------------------------------------------*/
/*
#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
#include "../../sensors/automatic1.h"
#include "../../digitals/digitals.h"
#include "device35.h"
#include "io35.h"
#include "automatic35.h"



bool    QueryConfig35_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryConfig35();

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadConfig35();
  return(1);
}


bool    Automatic35(void)
{
  Clear();

  if (QueryConfig35_Full(50) == 0) return(0);

  dbKpulse = GetDivider35();            // K преобразования
  dbKtrans = 1;                         // K трансформации
  SetAllFactors(dbKpulse,dbKtrans);     // сохранение К преобразования и К трансформации

  return(1);
}



time2   QueryTime35_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryTime35();

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (i == MaxRepeats()) return GetTime2Error();
  ShowPercent(bPercent);

  return GetTime2(ReadTime35(), true);
}


bool    QueryEngDay35_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngDay35(bTime);

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadEnergy35();
  return(1);
}


bool    QueryEngMon35_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngMon35(bTime);

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadEnergy35();
  return(1);
}



time2   ReadTimeCan35(void)
{
  Clear();

  time2 ti2 = QueryTime35_Full(50);
  if (ti2.fValid == false) return GetTime2Error();

  tiChannelC = ti2.tiValue;
  mpboChannelsA[0] = true;

  return GetTime2(ti2.tiValue, true);
}


time2   ReadTimeCan35_Short(void)
{
  DelayOff();
  QueryTime35();

  if (Input35() != SER_GOODCHECK) return GetTime2Error();


  return GetTime2(ReadTime35(), true);
}


double2 ReadCntCurr35(void)
{
  Clear();

  if (QueryConfig35_Full(50) == 0) return GetDouble2Error();

  if (QueryEngMon35_Full(0, 75) == 0) return GetDouble2Error();

  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / GetDivider35();
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
}


double2 ReadCntMonCan35(uchar  ibMon)
{
  Clear();

  if (QueryConfig35_Full(25) == 0) return GetDouble2Error();

  time2 ti2 = QueryTime35_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMon+1)
  {
    if (QueryEngMon35_Full((bMONTHS+ti.bMonth-1-ibMon) % bMONTHS, 75) == 0) return GetDouble2Error();
  }
  else
  {
    if (QueryEngDay35_Full(1, 75) == 0) return GetDouble2Error();
  }

  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / GetDivider35();
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
}
*/
