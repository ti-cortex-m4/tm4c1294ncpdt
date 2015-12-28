/*------------------------------------------------------------------------------
AUTOMATIC_W!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
//#include "../memory/mem_profile.h"
#include "../memory/mem_factors.h"
////#include "../time/delay.h"
//#include "../time/timedate.h"
#include "../hardware/watchdog.h"
//#include "../kernel/crc_v.h"
#include "../serial/ports.h"
//#include "../serial/ports2.h"
#include "../serial/ports_devices.h"
#include "../serial/monitor.h"
#include "../devices/devices.h"
#include "../sensors/unpack_w.h"
////#include "../digitals/digitals.h"
#include "../digitals/wait_answer.h"
////#include "automatic1.h"
#include "device_w.h"
#include "automatic_w.h"



#ifndef SKIP_W

void    QueryW(uint  cwIn, uchar  cbHeaderMax)
{
  ASSERT(GetPushSize() < 256);
  uchar cbOut = GetPushSize();

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
    if ((b & 0x7F) == '!') f = true;
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


/*
bool    QueryConfigS_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryConfigS();

    if (InputV() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadConfigS();
  return(1);
}
*/

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


bool    QueryEngAbsW_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<4; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseW();
      QueryEngAbsW(i);

      if (InputW() == SER_GOODCHECK) break;
      if (fKey == true) return(0);
    }

    if (r == bMINORREPEATS) return(0);
    ShowPercent(bPercent);

    ReadEngW(i);
  }

  return(1);
}


bool    QueryEngMonW_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<4; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseW();
      QueryEngMonW(i,bTime);

      if (InputW() == SER_GOODCHECK) break;
      if (fKey == true) return(0);
    }

    if (r == bMINORREPEATS) return(0);
    ShowPercent(bPercent);

    ReadEngW(i);
  }

  return(1);
}


bool    QueryEngDayW_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<4; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseW();
      QueryEngDayW(i,bTime);

      if (InputW() == SER_GOODCHECK) break;
      if (fKey == true) return(0);
    }

    if (r == bMINORREPEATS) return(0);
    ShowPercent(bPercent);

    ReadEngW(i);
  }

  return(1);
}



time2   ReadTimeCanW(void)
{
  Clear();

  time2 ti2 = QueryTimeW_Full(50);
  if (ti2.fValid == false) return GetTime2Error();

  tiChannelC = ti2.tiValue;

  uchar i;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;

  return GetTime2(ti2.tiValue, true);
}



double2 ReadCntCurrW(void)
{
  Clear();

  if (QueryEngAbsW_Full(50) == 0) return GetDouble2Error();

  QueryCloseW();


  double dbTrans = mpdbTransCnt[ibDig];

  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}


double2 ReadCntMonCanW(uchar  ibMonth)
{
  Clear();

  time2 ti2 = QueryTimeW_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMonth+1)
  {
    if (QueryEngMonW_Full(0, 75) == 0) return GetDouble2Error();
  }
  else
  {
    if (QueryEngDayW_Full(0, 75) == 0) return GetDouble2Error();
  }

  QueryCloseW();


  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif

