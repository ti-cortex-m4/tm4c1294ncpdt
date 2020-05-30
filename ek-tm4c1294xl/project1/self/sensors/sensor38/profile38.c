/*------------------------------------------------------------------------------
profile38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../serial/ports.h"
//#include "../../serial/ports_stack.h"
//#include "../../serial/ports_devices.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_ports.h"
//#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_realtime.h"
//#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_limits.h"
#include "../../display/display.h"
//#include "../../keyboard/time/key_timedate.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_common.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
//#include "../../devices/devices_time.h"
//#include "../../digitals/current/current_run.h"
#include "../../digitals/digitals.h"
#include "../../digitals/limits.h"
//#include "../../special/special.h"
//#include "../../hardware/watchdog.h"
#include "io38.h"
#include "dff.h"
#include "device38.h"
#include "profile38.h"



uint                    wProfile38;

time                    tiValue38;
ulong                   dwValue38;



void    InitHeader38(void)
{
  if (!UseBounds())
    wProfile38 = 0;
  else
  {
    wProfile38 = (mpcwStartRelCan[ibDig] / 6) * 6;
    sprintf(szLo," ������ %04u:%02u ",wProfile38,(uchar)(wProfile38/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;

  uchar i = tiDigPrev.bHour*2 + tiDigPrev.bMinute/30;
  i = (i / 6) * 6;

  tiDigPrev.bHour = i / 2;
  tiDigPrev.bMinute = (i % 2)*30;
}



void    QueryProfile38(uchar  ib30MinRel)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0B); // GET_DATA_MULTIPLE_EX
  PushChar(0x00);

  PushChar(0xD5); // 213
  PushChar(0x03);
  PushChar(ib30MinRel);
  PushChar(ib30MinRel + 1);

  PushChar(0xD6); // 214
  PushChar(0x03);
  PushChar(ib30MinRel);
  PushChar(ib30MinRel + 1);

  PushChar(0xD7); // 215
  PushChar(0x03);
  PushChar(ib30MinRel);
  PushChar(ib30MinRel + 1);

  PushChar(0xD8); // 216
  PushChar(0x03);
  PushChar(ib30MinRel);
  PushChar(ib30MinRel + 1);

  Query38(250, 29);
}


void    QueryHeader38(void)
{
  HideCurrTime(1);

  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wProfile38;
  tiDig = HouIndexToDate(dw);


  szHi[10] = 'A' + ibLine38;
  szHi[11] = ' ';


  bMaxLine38 = GetMaxLine38(ibDig);
  QueryProfile38(0); // TODO
}



void    ReadHeader38(void)
{
  InitPop(1);

  uchar h;
  for (h=0; h<6; h++)
  {
    mpdbBuffCanHou[ibLine38][h] = PopDoubleQ()/2;
  }
}



void    MakeData38(uchar  h)
{
  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<bMaxLine38; i++)
  {
    double db = mpdbBuffCanHou[i][h];
    mpdbEngFracDigCan[ibDig][i] += db;

    uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse);
    mpwChannels[i] = w;

    mpdbEngFracDigCan[ibDig][i] -= (double)w/dbPulse;
  }
}



bool    ReadBlock38(uchar  ibBlock)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);
  MonitorString("\n time "); MonitorTime(tiDig);

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  MakeData38(ibBlock);

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return(MakeStopHou(0));
}



bool    ReadData38(void)
{
  uchar i;
  for (i=0; i<6; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);
    dw += 6-1;
    dw -= (wProfile38 + i);
    tiDig = HouIndexToDate(dw);

    if (dw < dwValue38) {
      if (ReadBlock38(6-1-i) == 0) return(0);
    }
  }

  wProfile38 += 6;
  if (wProfile38 > wHOURS) return(0);

  return(1);
}
