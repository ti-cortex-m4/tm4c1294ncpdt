/*------------------------------------------------------------------------------
PROFILE34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_limits.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy_spec.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../digitals/digitals.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../special/special.h"
#include "../../digitals/profile/profile_frac8.h"
#include "../../digitals/limits.h"
#include "../../time/delay.h"
#include "../../time/calendar.h"
#include "../../time/unix_time.h"
#include "../../display/display.h"
#include "unix_time_gmt34.h"
#include "monitor34.h"
#include "profile34.h"



#ifndef SKIP_34

static  uchar           ibJournal34;
static  time            tiProfile34;
static  uchar           ibDay34;
static  uint            iwProfile34;
static  uint            cwOffline;



void    InitProfileOpen34(void)
{
  ibJournal34 = diCurr.ibLine / 4;
  tiProfile34 = tiCurr;
  cwOffline = 0;

  if (!UseBounds())
    ibDay34 = 0;
  else
  {
    ibDay34 = mpcwStartRelCan[ibDig]/48;
    Clear();
    sprintf(szLo+4,"начало %u",ibDay34);
    if (boShowMessages == true) DelayMsg();
  }

#if MONITOR_34
  MonitorString("\n start day "); MonitorIntDec(ibDay34);
#endif
}


void    QueryProfileOpen34(void)
{
  time ti1 = DayIndexToDate(DateToDayIndex(tiProfile34) - ibDay34);
  time ti2 = DayIndexToDate(DateToDayIndex(ti1)         + 1);

  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x6B);
  PushChar(0);
  PushChar(ibJournal34);
  PushLongLtl(TimeToUnixTime(ti1));
  PushLongLtl(TimeToUnixTime(ti2));

  QueryIO(3+1+2, 1+11+2);
}



void    InitProfileRead34(void)
{
  iwProfile34 = 0;
}


void    QueryProfileRead34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x6B);
  PushChar(1);
  PushChar(ibJournal34);
  PushChar(iwProfile34 % 0x100);
  PushChar(iwProfile34 / 0x100);

  QueryIO(1000, 1+5+2);
}

/*
static unsigned short CRC(uchar  j) {
  static unsigned short mpwBuff[12];

  uint x = 4+2+2+24*(j-1);

  uchar i;
  for (i=0; i<12; i++) {
    uint y = x + i*2;
    mpwBuff[i] = InBuff(y) + InBuff(y+1)*0x100;
  }

  return CRC34(mpwBuff, 12);
}
*/

bool    ReadProfileRead34(void)
{
  InitPop(4);

  uint wCount = PopIntLtl();
  if (wCount == 0) {
    cwOffline++;
    if (cwOffline > 1) {
      sprintf(szLo," выключено: %-2u  ",cwOffline);
    }
  } else {
    cwOffline = 0;
  }

  iwProfile34 = PopIntLtl();

  uchar j;
  for (j=0; j<wCount; j++)
  {
    uchar k;
    for (k=0; k<4; k++)
    {
      uchar i = ibJournal34*4 + k;

      long dw = PopLongLtl();
      mpdbEngFracDigCan8[ibDig][i] += (double)dw/100;

      uint w = (uint)(mpdbEngFracDigCan8[ibDig][i]);
      mpwChannels[i] = w;

      mpdbEngFracDigCan8[ibDig][i] -= (double)w;
    }

    time tm = UnixTimeToTimeFromGMT34(PopLongLtl());
    sprintf(szLo," %02u:%02u %02u.%02u.%02u", tm.bHour,tm.bMinute, tm.bDay,tm.bMonth,tm.bYear);

    SearchDefHouIndex(tm);

    MakeSpecial(tm);

    uint w1 = PopIntLtl();
    uint w2 = PopIntLtl();
  }

  SaveProfileFrac8(ibDig);

  if (wCount > 0)
    return 1;
  else
    return 0;
}



void    QueryProfileClose34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x6B);
  PushChar(2);
  PushChar(ibJournal34);

  QueryIO(3+1+2, 1+3+2);
}


bool    ReadProfileClose34(void)
{
  ShowProgressDigHou();

  ibDay34++;
#if MONITOR_34
  MonitorString("\n day "); MonitorCharDec(ibDay34);
#endif

  if (cwOffline > 30) {
    #if MONITOR_34
      MonitorString("\n offline limit "); MonitorCharDec(cwOffline);
    #endif
    return 0;
  } else {
    if (cwOffline > 1) {
      time tm = DayIndexToDate(DateToDayIndex(tiProfile34) - ibDay34);
      #if MONITOR_34
        MonitorString("\n date "); MonitorTime(tm);
      #endif
      if (SearchDefHouIndex(tm)) {
        #if MONITOR_34
          MonitorString("\n day found ");
        #endif
        return MakeStopHou(0);
      } else {
        #if MONITOR_34
          MonitorString("\n day not found "); MonitorCharDec(ibDay34 < wHOURS/48);
        #endif
        return ibDay34 < wHOURS/48;
      }
    } else {
      #if MONITOR_34
        MonitorString("\n online ");
      #endif
      return MakeStopHou(0);
    }
  }
}



bool    ActualLine34(uchar  ibDig, uchar  ibCan)
{
  return ((GetDigitalDevice(ibDig) != 34) ||
          (GetDigitalLine(ibDig) / 4 == GetDigitalLine(ibCan) / 4));
}

#endif
