/*------------------------------------------------------------------------------
AUTOMATIC31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_factors.h"
#include "../../hardware/watchdog.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../serial/input_wrapper.h"
#include "../../devices/devices.h"
#include "../../sensors/sensor31/unpack31.h"
#include "../../digitals/wait_answer.h"
#include "../automatic1.h"
#include "device31.h"
#include "automatic31.h"



#ifndef SKIP_31

uchar                   mpbCoder[4], ibCoder;



void    InitPushCod(void)
{
  InitPush(0);
  ibCoder = 0;
}


void    PushCharCod(uchar  bT)
{
  PushChar(bT ^ mpbCoder[ibCoder]);
  ibCoder = (ibCoder + 1)%4;
}



void    InitPopCod(void)
{
  InitPop(3);
  ibCoder = 0;
}


uchar   PopCharCod(void)
{
  uchar i = PopChar() ^ mpbCoder[ibCoder];
  ibCoder = (ibCoder + 1)%4;

  return i;
}


void    Query31(uint  cwIn, uchar  cbOut)
{
  uchar bCrc = MakeCrc8Bit31OutBuff(1, cbOut-2);

  InitPush(0);
  Skip(cbOut-1);

  PushChar(bCrc);

  Query(cwIn,cbOut,1);
}


serial  Input31(void)
{
  InputStart();
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_INPUT_MASTER)
    {
      if ((InBuff(0) == 0x7E) && (IndexInBuff() > 3) && (IndexInBuff() == InBuff(1)+4))
        mpSerial[ibPort] = SER_BADLINK;
    }

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      uchar bCrc = MakeCrc8Bit31InBuff(1, CountInBuff()-1);
      if (bCrc == 0)
      {
        Unpack31();
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if (mpSerial[ibPort] == SER_BADLINK)
    {
      uchar bCrc = MakeCrc8Bit31InBuff(1, IndexInBuff()-1);
      if (bCrc == 0)
      {
        Unpack31();
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if (mpSerial[ibPort] == SER_OVERFLOW) break;
  }

  MonitorIn();
  return mpSerial[ibPort];
}


bool    QueryOpen31_Full(uchar  bPercent)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryOpen31();

    if (Input31() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (r == MaxRepeats()) return false;
  ShowPercent(bPercent);

  if (ReadOpen31() == false) return false;

  return true;
}


time2   QueryTime31_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryTime31();

    if (Input31() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (r == MaxRepeats()) return GetTime2Error();
  ShowPercent(bPercent);

  return GetTime2(ReadTime31(), true);
}


double2 ReadTrans31_Full(void)
{
  if (QueryOpen31_Full(25) == false) return GetDouble2Error();


  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryTrans31();

    if (Input31() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == MaxRepeats()) return GetDouble2Error();
  ShowPercent(50);


  InitPop(3+4+4+1);

  double dbTransU = PopDouble31();
  double dbTransI = PopDouble31();

  return GetDouble2(dbTransU*dbTransI, true);
}


bool    Automatic31(void)
{
  double2 db2 = ReadTrans31_Full();
  if (db2.fValid == false) return false;

  ShowPercent(100);

  SetupFactors(GetFactors(db2.dbValue, 10000));

  return true;
}



bool    QueryEngAbs31_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryEngAbs31();

    if (Input31() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (r == MaxRepeats()) return false;
  ShowPercent(bPercent);

  ReadEng31();

  return true;
}

/*
bool    QueryEngMonW_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      QueryCloseW();
      QueryEngMonW(i,bTime);

      if (InputW() == SER_GOODCHECK) break;
      if (IndexInBuff() == 10)
      {
        Clear();
        sprintf(szLo+3, "мес€ц -%u ?",bTime);
        Delay(1000);
        return false;
      }
      if (fKey == true) return false;
    }

    if (r == MaxRepeats()) return false;
    ShowPercent(bPercent+i);

    ReadEngW(i);
  }

  QueryCloseW();

  return true;
}


bool    QueryEngDayW_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      QueryCloseW();
      QueryEngDayW(i,bTime);

      if (InputW() == SER_GOODCHECK) break;
      if (IndexInBuff() == 10)
      {
        Clear();
        sprintf(szLo+3, "сутки -%u ?",bTime);
        Delay(1000);
        return false;
      }
      if (fKey == true) return false;
    }

    if (r == MaxRepeats()) return false;
    ShowPercent(bPercent+i);

    ReadEngW(i);
  }

  QueryCloseW();

  return true;
}


status  QueryEngMonTrfW_Full(uchar  bTime, uchar  bPercent, uchar  ibTrf)
{
  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      QueryCloseW();
      QueryEngMonTrfW(i,bTime);

      if (InputW() == SER_GOODCHECK) break;
      if (IndexInBuff() == 10)
      {
        Clear();
        sprintf(szLo+3, "мес€ц -%u ?",bTime);
        Delay(1000);
        return ST_NOTPRESENTED;
      }
      if (fKey == true) return ST_OK;
    }

    if (r == MaxRepeats()) return ST_OK;
    ShowPercent(bPercent+i);

    ReadEngTrfW(i,ibTrf);
  }

  QueryCloseW();

  return ST_OK;
}
*/


time2   ReadTimeCan31(void)
{
  if (QueryOpen31_Full(25) == 0) GetTime2Error();

  time2 ti2 = QueryTime31_Full(50);
  if (ti2.fValid == false) return GetTime2Error();


  tiChannelC = ti2.tiValue;

  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    mpboChannelsA[i] = true;
  }

  return GetTime2(ti2.tiValue, true);
}



double2 ReadCntCurr31(void)
{
  if (QueryOpen31_Full(25) == 0) GetDouble2Error();

  if (QueryEngAbs31_Full(50) == 0) return GetDouble2Error();


  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

/*
double2 ReadCntMonCanW(uchar  ibMon)
{
  Clear();

  double2 db2 = QueryKtransW_Full(25);
  if (db2.fValid == false) return GetDouble2Error();
  double dbTrans = db2.dbValue;


  time2 ti2 = QueryTimeW_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMon+1)
  {
    uchar m = (12 + ti.bMonth - (ibMon+1) - 1) % 12;
    if (QueryEngMonW_Full(m, 75) == 0) return GetDouble2Error();
  }
  else
  {
    if (QueryEngDayW_Full(0, 75) == 0) return GetDouble2Error();
  }


  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}


status  ReadCntMonCanTariffW(uchar  ibMon, uchar  ibTrf) // на начало мес€ца
{
  Clear();

  double2 db2 = QueryKtransW_Full(25);
  if (db2.fValid == false) return ST_BADDIGITAL;
  double dbTrans = db2.dbValue;


  time2 ti2 = QueryTimeW_Full(50);
  if (ti2.fValid == false) return ST_BADDIGITAL;
  time ti = ti2.tiValue;


  uchar m = (12 + ti.bMonth - (ibMon+1)) % 12;
  status st = QueryEngMonTrfW_Full(m, 75+ibTrf, ibTrf);
  if (st != ST_OK) return st;


  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return ST_OK;
}
*/
#endif
