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

void    QueryW(uint  cwIn, uchar  cbOut, uchar  cbHeaderMax)
{
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

/*
bool    QueryEngAbsW_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEngAbsW();

    if (InputW() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEngAbsW();
  return(1);
}


bool    QueryEngMonW_Full(uchar  bMonth, uchar  bYear, uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEngMonV(bMonth,bYear);

    if (InputV() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEngMonV();
  return(1);
}


bool    QueryEngDayW_Full(uchar  bDay, uchar  bMonth, uchar  bYear, uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEngDayV(bDay,bMonth,bYear);

    if (InputV() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEngDayV();
  return(1);
}
*/

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

  uchar i;
  for (i=0; i<4; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      ShowPercent(50 + i);
      QueryCloseW();
      QueryEngAbsW(i);

      if (InputW() == SER_GOODCHECK) break;
      if (fKey == true) return GetDouble2Error();
    }

    if (r == bMINORREPEATS) return GetDouble2Error();
    ReadEngAbsW(i);
  }

  QueryCloseW();


  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

/*
double2 ReadCntMonCanV(uchar  ibMonth)
{
  Clear();

//  if (QueryConfigS_Full(25) == 0) return GetDouble2Error();

  time2 ti2 = QueryTimeW_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMonth+1)
  {
    ti.bMonth = ibMonth+2;
    ti.bYear = (ibMonth+2 > ti.bMonth) ? ti.bYear-1 : ti.bYear;

    if (QueryEngMonW_Full(ti.bMonth, ti.bYear, 75) == 0) return GetDouble2Error();
  }
  else
  {
    if (QueryEngDayW_Full(ti.bDay, ti.bMonth, ti.bYear, 75) == 0) return GetDouble2Error();
  }

  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / wDividerV;
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
}
*/
#endif

