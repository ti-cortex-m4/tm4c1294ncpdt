/*------------------------------------------------------------------------------
AUTOMATIC_W!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../memory/mem_factors.h"
#include "../hardware/watchdog.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../serial/monitor.h"
#include "../devices/devices.h"
#include "../sensors/unpack_w.h"
#include "../digitals/wait_answer.h"
#include "device_w.h"
#include "automatic1.h"
#include "automatic_w.h"



#ifndef SKIP_W

void    QueryW(uint  cwIn, uchar  cbHeaderMax)
{
  ASSERT(GetPushSize() < 256);
  uchar cbOut = GetPushSize() + 1;

  cbHeaderBcc = cbHeaderMax;
  cwInBuffBcc = 0;

  InitPush(0);

  uchar bSum = 0;
  bool f = false;

  uchar i;
  for (i=0; i<cbOut-1; i++)
  {
    uchar b = SkipChar();
    if (f == true) bSum ^= b;
    if (((b & 0x7F) == 0x01) || ((b & 0x7F) == '!')) f = true;
  }

  PushChar1Bcc(bSum);

  Query(cwIn,cbOut,1);
}


bool    ChecksumW(void)
{
  InitPop(1);

  uchar bT = 0;

  uint i;
  for (i=0; i<CountInBuff()-2; i++)
  {
    bT ^= PopChar0Bcc();
  }

//  MonitorString("\n checksum "); MonitorCharHex(bT & 0x7F); MonitorString(" ? "); MonitorCharHex(PopChar0Bcc());

  return ((bT & 0x7F) == PopChar0Bcc());
}


serial  InputW(void)
{
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_INPUT_MASTER)
      UnpackW(false,3);

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if (ChecksumW())
        mpSerial[ibPort] = SER_GOODCHECK;
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  MonitorIn();
  return mpSerial[ibPort];
}



time2   QueryTimeW_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseW();
    QueryTimeW();

    if (InputW() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (r == bMINORREPEATS) return GetTime2Error();
  ShowPercent(bPercent);

  QueryCloseW();

  return GetTime2(ReadTimeW(), true);
}


double2 QueryTransW_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseW();
    QueryTransW(0);

    if (InputW() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == bMINORREPEATS) return GetDouble2Error();
  ShowPercent(bPercent+0);

  InitPop(1);
  double dbTransI = PopDoubleW();


  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseW();
    QueryTransW(1);

    if (InputW() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == bMINORREPEATS) return GetDouble2Error();
  ShowPercent(bPercent+1);

  InitPop(1);
  double dbTransU = PopDoubleW();


  QueryCloseW();

  return GetDouble2(dbTransI*dbTransU, true);
}


bool    AutomaticW(void)
{
  Clear();

  double2 db2 = QueryTransW_Full(25);
  if (db2.fValid == false) return false;
  double dbTrans = db2.dbValue;

  SetupFactors(GetFactors(dbTrans, 2000));


  Clear();

  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseW();
    QueryTypeW();

    if (InputW() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (r == bMINORREPEATS) return false;
  ReadTypeW();

  QueryCloseW();


  Delay(1000);

  return true;
}



bool    QueryEngAbsW_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<MAX_LINE_W; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseW();
      QueryEngAbsW(i);

      if (InputW() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    ShowPercent(bPercent);

    ReadEngW(i);
  }

  QueryCloseW();

  return true;
}


bool    QueryEngMonW_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MAX_LINE_W; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
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

    if (r == bMINORREPEATS) return false;
    ShowPercent(bPercent+i);

    ReadEngW(i);
  }

  QueryCloseW();

  return true;
}


bool    QueryEngDayW_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MAX_LINE_W; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
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

    if (r == bMINORREPEATS) return false;
    ShowPercent(bPercent+i);

    ReadEngW(i);
  }

  QueryCloseW();

  return true;
}


status  QueryEngMonTrfW_Full(uchar  bTime, uchar  bPercent, uchar  ibTrf)
{
  uchar i;
  for (i=0; i<MAX_LINE_W; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
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

    if (r == bMINORREPEATS) return ST_OK;
    ShowPercent(bPercent+i);

    ReadEngTrfW(i,ibTrf);
  }

  QueryCloseW();

  return ST_OK;
}


time2   ReadTimeCanW(void)
{
  Clear();

  time2 ti2 = QueryTimeW_Full(50);
  if (ti2.fValid == false) return GetTime2Error();


  tiChannelC = ti2.tiValue;

  uchar i;
  for (i=0; i<MAX_LINE_W; i++)
  {
    mpboChannelsA[i] = true;
  }

  return GetTime2(ti2.tiValue, true);
}



double2 ReadCntCurrW(void)
{
  Clear();

  double2 db2 = QueryTransW_Full(25);
  if (db2.fValid == false) return GetDouble2Error();
  double dbTrans = db2.dbValue;


  if (QueryEngAbsW_Full(50) == 0) return GetDouble2Error();


  uchar i;
  for (i=0; i<MAX_LINE_W; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}


double2 ReadCntMonCanW(uchar  ibMon)
{
  Clear();

  double2 db2 = QueryTransW_Full(25);
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
  for (i=0; i<MAX_LINE_W; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}


status  ReadCntMonCanTariffW(uchar  ibMon, uchar  ibTrf) // на начало мес€ца
{
  Clear();

  double2 db2 = QueryTransW_Full(25);
  if (db2.fValid == false) return ST_BADDIGITAL;
  double dbTrans = db2.dbValue;


  time2 ti2 = QueryTimeW_Full(50);
  if (ti2.fValid == false) return ST_BADDIGITAL;
  time ti = ti2.tiValue;


  uchar m = (12 + ti.bMonth - (ibMon+1)) % 12;
  status st = QueryEngMonTrfW_Full(m, 75+ibTrf, ibTrf);
  if (st != ST_OK) return st;


  uchar i;
  for (i=0; i<MAX_LINE_W; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return ST_OK;
}

#endif

