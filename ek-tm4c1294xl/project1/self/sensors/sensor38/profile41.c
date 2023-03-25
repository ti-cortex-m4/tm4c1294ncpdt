/*------------------------------------------------------------------------------
profile38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_limits.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_common.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../digitals/digitals.h"
#include "../../digitals/limits.h"
#include "../../special/special.h"
#include "device38.h"
#include "time38.h"
#include "io38.h"
#include "dff.h"
#include "profile38_include.h"
#include "profile41.h"



uint                    wProfile41;
uint                    wRelStart41, wRelEnd41;
profile41               mpPrf41[6];
time                    tiStart41;
ulong                   dwHouStart41;

time                    tiValue41;
ulong                   dwValue41;

uint                    cwShutdown41;



void    InitHeader41(void)
{
  if (!UseBounds())
    wProfile41 = 0;
  else
  {
    wProfile41 = (mpcwStartRelCan[ibDig] / 6) * 6;
    sprintf(szLo," начало %04u:%02u ",wProfile41,(uchar)(wProfile41/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  tiStart41 = tiValue41;
  dwHouStart41 = DateToHouIndex(tiCurr);

  wRelStart41 = wProfile41;
  wRelEnd41 = wRelStart41 + 5;

#ifdef MONITOR_38
  MonitorString("\n QueryProfile41 ");
  MonitorString(" wProfile41="); MonitorIntDec(wProfile41);
  MonitorString(" tiStart41="); MonitorTime(tiStart41);
  MonitorString(" wRelStart41="); MonitorIntDec(wRelStart41);
  MonitorString(" wRelEnd41="); MonitorIntDec(wRelEnd41);
#endif
}



uchar   PushIndex41(uint  iw30MinRel)
{
  int64_t ddw = iw30MinRel;
  uchar n = DffEncode(ddw, OutBuffPtr(GetPush()));
  Skip(n);
  return n;
}


void    QueryProfile41(uint  iw30MinRelStart, uint  iw30MinRelEnd)
{
#ifdef MONITOR_38
  MonitorString("\n QueryProfile41 "); MonitorIntDec(iw30MinRelStart); MonitorString(" "); MonitorIntDec(iw30MinRelEnd);
#endif

  InitPush(0);

  uchar bSize = 0;

  bSize += PushChar(0xC0);
  bSize += PushChar(0x06);

  PushAddress41();
  bSize += 4;

  bSize += PushChar(0x00);
  bSize += PushChar(0x06);

  bSize += PushChar(0x0B); // GET_DATA_MULTIPLE_EX

  if ((iw30MinRelStart < 0x100) && (iw30MinRelEnd < 0x100))
  {
    bSize += PushChar(0x00);

    bSize += PushChar(0xD5); // 213
    bSize += PushChar(0x03);
    bSize += PushChar(iw30MinRelStart);
    bSize += PushChar(iw30MinRelEnd);
  }
  else
  {
    bSize += PushChar(0x80);

    bSize += PushChar(0xD5); // 213
    bSize += PushChar(0x01);
    bSize += PushChar(0x03);
    bSize += PushIndex41(iw30MinRelStart);
    bSize += PushIndex41(iw30MinRelEnd);
  }
/*
  bSize += PushChar(0xD6); // 214
  bSize += PushChar(0x01);
  bSize += PushChar(0x03);
  bSize += PushIndex41(iw30MinRelStart);
  bSize += PushIndex41(iw30MinRelEnd);

  bSize += PushChar(0xD7); // 215
  bSize += PushChar(0x01);
  bSize += PushChar(0x03);
  bSize += PushIndex41(iw30MinRelStart);
  bSize += PushIndex41(iw30MinRelEnd);

  bSize += PushChar(0xD8); // 216
  bSize += PushChar(0x01);
  bSize += PushChar(0x03);
  bSize += PushIndex41(iw30MinRelStart);
  bSize += PushIndex41(iw30MinRelEnd);
*/
  Query41(250, bSize+3);
}


void    QueryHeader41(void)
{
  HideCurrTime(1);

#ifdef MONITOR_38
  MonitorString("\n QueryHeader41 ");
  MonitorString(" wProfile41="); MonitorIntDec(wProfile41);
  MonitorString(" wRelStart41="); MonitorIntDec(wRelStart41);
  MonitorString(" wRelEnd41="); MonitorIntDec(wRelEnd41);
#endif

  QueryProfile41(wRelStart41, wRelEnd41);
}



void    MakeData41(uchar  h)
{
  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<1; i++)
  {
    double db = mpPrf41[h].mpdwValue[i];
    mpdbEngFracDigCan[ibDig][i] += db;

    uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse/10000);
    mpwChannels[i] = w;

    mpdbEngFracDigCan[ibDig][i] -= (double)w*10000/dbPulse;
  }
/*
  uchar i;
  for (i=0; i<1; i++)
  {
    ulong dw = mpPrf41[h].mpdwValue[i];
    uint w = (uint)(dw*dbPulse/10000);

    mpwChannels[i] = w;
  }
*/
}



bool    ReadBlock41(uchar  ibBlock)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

#ifdef MONITOR_38
  if (tiDig.bMinute % 30 != 0) MonitorString(" ??? ");
  MonitorString(" eff.="); MonitorTime(tiDig);
#endif

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  MakeData41(ibBlock);

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return(MakeStopHou(0));
}



bool    ReadData41(void)
{
  memset(&mpPrf41, 0, sizeof(mpPrf41));

  uchar* pbIn = InBuffPtr(10);

  uchar c;
  for (c=0; c<1; c++)
  {
    *(pbIn++);

#ifdef MONITOR_38
    MonitorString("\n ");
#endif

    uchar h;
    for (h=0; h<6; h++)
    {
      int64_t ddw = 0;
      pbIn = DffDecodePositive(pbIn, &ddw);

      mpPrf41[h].tiTime = SecondsToTime41(ddw % 0x100000000);

      ddw = 0;
      pbIn = DffDecodePositive(pbIn, &ddw);

      mpPrf41[h].bStatus = (ddw % 0x100) & 0x03;
      mpPrf41[h].mpdwValue[c] = (ddw >> 3) % 0x100000000;

#ifdef MONITOR_38
      MonitorString("\n "); MonitorTime(mpPrf41[h].tiTime);
      MonitorString(" "); MonitorLongDec(mpPrf41[h].mpdwValue[c]);
      MonitorString(" "); MonitorCharDec(mpPrf41[h].bStatus);
#endif
    }
  }


  ulong dwHouNow = DateToHouIndex(tiCurr);
  uchar d = dwHouNow - dwHouStart41;

#ifdef MONITOR_38
  MonitorString("\n delta="); MonitorCharDec(d);
#endif


  uchar h;
  for (h=0; h<6; h++) {

#ifdef MONITOR_38
    MonitorString("\n");

    uchar i;
    for (i=0; i<1; i++) {
      MonitorLongDec4(mpPrf41[h].mpdwValue[i]); MonitorString("  ");
    }
#endif

    ulong dw = DateToHouIndex(tiStart41);
    dw -= (wProfile41 + h - d);
    time tiVirtual = HouIndexToDate(dw);

    bool difference = DifferentDateTime(tiVirtual, mpPrf41[h].tiTime);

#ifdef MONITOR_38
    MonitorString(" vrt.="); MonitorTime(tiVirtual);
    MonitorString(" act.="); MonitorTime(mpPrf41[h].tiTime);
    MonitorBool(difference);
    MonitorString(" #"); MonitorCharDec(mpPrf41[h].bStatus); MonitorString(" ");
#endif

    if ((difference == true) && (mpPrf41[h].bStatus == 2))
      tiDig = tiVirtual;
    else if ((mpPrf41[h].tiTime.bMinute % 30 != 0) && (mpPrf41[h].bStatus == 0))
      tiDig = tiVirtual;
    else
      tiDig = mpPrf41[h].tiTime;

    if (ReadBlock41(h) == false) return false;
  }

  wProfile41 += 6;
  if (wProfile41 > wHOURS) return false;

  wRelStart41 += 6;
  wRelEnd41 = wRelStart41 + 5;

  return true;
}



#ifdef MONITOR_38

void    RunProfile41(void)
{
  QueryTime41();
  if (Input41() != SER_GOODCHECK) { MonitorString("\n error 1"); return; }

  tiValue41 = ReadTime41();
  dwValue41 = DateToHouIndex(tiValue41);

  InitHeader41();

  while (true) {
    QueryHeader41();
    if (Input41() != SER_GOODCHECK) { MonitorString("\n error 2"); return; }

    if (ReadData41() == false) { MonitorString("\n finish "); return; }
    if (fKey == true) return;
  }
}

#endif
