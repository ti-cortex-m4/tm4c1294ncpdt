/*------------------------------------------------------------------------------
AUTOMATIC32.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_factors.h"
#include "../../hardware/watchdog.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/wait_answer.h"
#include "../automatic1.h"
#include "device32.h"
#include "../sensor31/automatic31.h"
#include "automatic32.h"



#ifndef SKIP_32


void    Query32(uint  cwIn, uchar  cbOut)
{
  Query31(cwIn,cbOut);
}


serial  Input32(void)
{
  return Input31();
}


bool    QueryOpen32_Full(uchar  bPercent)
{
  Clear();

  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    DelayOff();
    QueryOpen32();

    if (Input32() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (r == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  if (ReadOpen32() == false) return false;

  return true;
}


time2   QueryTime32_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    DelayOff();
    QueryTime32();

    if (Input32() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (r == bMINORREPEATS) return GetTime2Error();
  ShowPercent(bPercent);

  return GetTime2(ReadTime32(), true);
}


//double2 ReadTrans32_Full(void)
//{
//  if (QueryOpen32_Full(25) == false) return GetDouble2Error();
//
//
//  uchar r;
//  for (r=0; r<bMINORREPEATS; r++)
//  {
//    DelayOff();
//    QueryTrans32();
//
//    if (Input32() == SER_GOODCHECK) break;
//    if (fKey == true) return GetDouble2Error();
//  }
//
//  if (r == bMINORREPEATS) return GetDouble2Error();
//  ShowPercent(50);
//
//
//  InitPop(3+4+4+1);
//
//  double dbTransU = PopDouble32();
//  double dbTransI = PopDouble32();
//
//  return GetDouble2(dbTransU*dbTransI, true);
//}


bool    Automatic32(void)
{
  if (QueryOpen32_Full(25) == false) return false;

  ShowPercent(100);

  SetupFactors(GetFactors(1, 10000));

  return true;
}



//bool    QueryEngAbs32_Full(uchar  bPercent)
//{
//  uchar r;
//  for (r=0; r<bMINORREPEATS; r++)
//  {
//    DelayOff();
//    QueryEngAbs32();
//
//    if (Input32() == SER_GOODCHECK) break;
//    if (fKey == true) return false;
//  }
//
//  if (r == bMINORREPEATS) return false;
//  ShowPercent(bPercent);
//
//  ReadEng32();
//
//  return true;
//}
//
///*
//bool    QueryEngMonW_Full(uchar  bTime, uchar  bPercent)
//{
//  uchar i;
//  for (i=0; i<MAX_LINE_N32; i++)
//  {
//    uchar r;
//    for (r=0; r<bMINORREPEATS; r++)
//    {
//      QueryCloseW();
//      QueryEngMonW(i,bTime);
//
//      if (InputW() == SER_GOODCHECK) break;
//      if (IndexInBuff() == 10)
//      {
//        Clear();
//        sprintf(szLo+3, "мес€ц -%u ?",bTime);
//        Delay(1000);
//        return false;
//      }
//      if (fKey == true) return false;
//    }
//
//    if (r == bMINORREPEATS) return false;
//    ShowPercent(bPercent+i);
//
//    ReadEngW(i);
//  }
//
//  QueryCloseW();
//
//  return true;
//}
//
//
//bool    QueryEngDayW_Full(uchar  bTime, uchar  bPercent)
//{
//  uchar i;
//  for (i=0; i<MAX_LINE_N32; i++)
//  {
//    uchar r;
//    for (r=0; r<bMINORREPEATS; r++)
//    {
//      QueryCloseW();
//      QueryEngDayW(i,bTime);
//
//      if (InputW() == SER_GOODCHECK) break;
//      if (IndexInBuff() == 10)
//      {
//        Clear();
//        sprintf(szLo+3, "сутки -%u ?",bTime);
//        Delay(1000);
//        return false;
//      }
//      if (fKey == true) return false;
//    }
//
//    if (r == bMINORREPEATS) return false;
//    ShowPercent(bPercent+i);
//
//    ReadEngW(i);
//  }
//
//  QueryCloseW();
//
//  return true;
//}
//
//
//status  QueryEngMonTrfW_Full(uchar  bTime, uchar  bPercent, uchar  ibTrf)
//{
//  uchar i;
//  for (i=0; i<MAX_LINE_N32; i++)
//  {
//    uchar r;
//    for (r=0; r<bMINORREPEATS; r++)
//    {
//      QueryCloseW();
//      QueryEngMonTrfW(i,bTime);
//
//      if (InputW() == SER_GOODCHECK) break;
//      if (IndexInBuff() == 10)
//      {
//        Clear();
//        sprintf(szLo+3, "мес€ц -%u ?",bTime);
//        Delay(1000);
//        return ST_NOTPRESENTED;
//      }
//      if (fKey == true) return ST_OK;
//    }
//
//    if (r == bMINORREPEATS) return ST_OK;
//    ShowPercent(bPercent+i);
//
//    ReadEngTrfW(i,ibTrf);
//  }
//
//  QueryCloseW();
//
//  return ST_OK;
//}
//*/


time2   ReadTimeCan32(void)
{
  if (QueryOpen32_Full(25) == 0) GetTime2Error();

  time2 ti2 = QueryTime32_Full(50);
  if (ti2.fValid == false) return GetTime2Error();


  tiChannelC = ti2.tiValue;

  uchar i;
  for (i=0; i<MAX_LINE_N32; i++)
  {
    mpboChannelsA[i] = true;
  }

  return GetTime2(ti2.tiValue, true);
}



double2 ReadCntCurr32(void)
{
  if (QueryOpen32_Full(25) == 0) GetDouble2Error();


  mpdbChannelsC[0] = 0;


  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryEngAbs32(t);

      ShowPercent(50+t);

      if (Input32() == SER_GOODCHECK) break;
      if (fKey == true) return GetDouble2Error();
    }

    if (r == bMINORREPEATS) return GetDouble2Error();
    else
    {
      if (Checksum32(14) == false) { ShowLo(szBadCRC); Delay(1000); return GetDouble2Error(); }

      InitPop(3);
      mpdbChannelsC[0] += (double)PopLongBig()/1000;
    }
  }


  double dbTrans = mpdbTransCnt[ibDig];

  mpdbChannelsC[0] *= dbTrans;
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

///*
//double2 ReadCntMonCanW(uchar  ibMon)
//{
//  Clear();
//
//  double2 db2 = QueryKtransW_Full(25);
//  if (db2.fValid == false) return GetDouble2Error();
//  double dbTrans = db2.dbValue;
//
//
//  time2 ti2 = QueryTimeW_Full(50);
//  if (ti2.fValid == false) return GetDouble2Error();
//  time ti = ti2.tiValue;
//
//  if (ti.bMonth != ibMon+1)
//  {
//    uchar m = (12 + ti.bMonth - (ibMon+1) - 1) % 12;
//    if (QueryEngMonW_Full(m, 75) == 0) return GetDouble2Error();
//  }
//  else
//  {
//    if (QueryEngDayW_Full(0, 75) == 0) return GetDouble2Error();
//  }
//
//
//  uchar i;
//  for (i=0; i<MAX_LINE_N32; i++)
//  {
//    mpdbChannelsC[i] *= dbTrans;
//    mpboChannelsA[i] = true;
//  }
//
//  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
//}
//
//
//status  ReadCntMonCanTariffW(uchar  ibMon, uchar  ibTrf) // на начало мес€ца
//{
//  Clear();
//
//  double2 db2 = QueryKtransW_Full(25);
//  if (db2.fValid == false) return ST_BADDIGITAL;
//  double dbTrans = db2.dbValue;
//
//
//  time2 ti2 = QueryTimeW_Full(50);
//  if (ti2.fValid == false) return ST_BADDIGITAL;
//  time ti = ti2.tiValue;
//
//
//  uchar m = (12 + ti.bMonth - (ibMon+1)) % 12;
//  status st = QueryEngMonTrfW_Full(m, 75+ibTrf, ibTrf);
//  if (st != ST_OK) return st;
//
//
//  uchar i;
//  for (i=0; i<MAX_LINE_N32; i++)
//  {
//    mpdbChannelsC[i] *= dbTrans;
//    mpboChannelsA[i] = true;
//  }
//
//  return ST_OK;
//}
//*/
#endif
