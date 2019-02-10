/*------------------------------------------------------------------------------
PROFILE34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy_spec.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../time/calendar.h"
#include "../../time/unix_time.h"
#include "../../display/display.h"
#include "unix_time_gmt34.h"
#include "profile34.h"



#ifndef SKIP_34

uchar                   ibJournal34;
time                    tiProfile34;
uchar                   ibDay34;
uint                    iwProfile34;



void    InitProfileOpen34(void)
{
  ibJournal34 = 0;
  tiProfile34 = tiCurr;
  ibDay34 = 0;
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

  QueryIO(250, 1+5+2); // ???
}


bool    ReadProfileRead34(void)
{
  InitPop(4);

  uint wSize = PopIntLtl();

  iwProfile34 = PopIntLtl();

  uchar s;
  for (s=0; s<wSize; s++) {
    uchar i;
    for (i=0; i<4; i++) {
      mpwChannels[i] = PopLongLtl() / 0x100;
    }

    time tm = UnixTimeToTimeFromGMT34(PopLongLtl());
    sprintf(szLo," %02u:%02u %02u.%02u.%02u", tm.bHour,tm.bMinute, tm.bDay,tm.bMonth,tm.bYear);

    uint w1 = PopIntLtl();
    uint w2 = PopIntLtl();
  }

  if (wSize == 10)
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
  if (++ibDay34 < wHOURS/48)
    return 1;
  else
    return 0;
}

#endif
