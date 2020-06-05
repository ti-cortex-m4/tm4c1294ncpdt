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
#include "io38.h"
#include "dff.h"
#include "profile38.h"



typedef struct
{
  time          tiTime;
  uchar         bStatus;
  ulong         mpdwValue[4];
} profile38;



static uint             wProfile38;
static uint             wRelStart, wRelEnd;
static profile38        mpPrf38[6];
static time             tiStart38;

time                    tiValue38;
ulong                   dwValue38;



void    InitHeader38(void)
{/*
  if (!UseBounds())
    wProfile38 = 0;
  else
  {
    wProfile38 = (mpcwStartRelCan[ibDig] / 6) * 6;
    sprintf(szLo," начало %04u:%02u ",wProfile38,(uchar)(wProfile38/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;

  uchar i = tiDigPrev.bHour*2 + tiDigPrev.bMinute/30;
  i = (i / 6) * 6;

  tiDigPrev.bHour = i / 2;
  tiDigPrev.bMinute = (i % 2)*30;
*/
  wProfile38 = 0;
  tiStart38 = tiValue38;

  wRelStart = 0;
  wRelEnd = wRelStart + 5;

  MonitorString("\n QueryProfile38 ");
  MonitorTime(tiValue38);
  MonitorString(" wRelStart="); MonitorIntDec(wRelStart);
  MonitorString(" wRelEnd="); MonitorIntDec(wRelEnd);
}



uchar   PushIndex(uint  iw30MinRel)
{
  int64_t ddw = iw30MinRel;
  uchar n = EncodeInt(ddw, OutBuffPtr(GetPush()));
  Skip(n);
  return n;
}


void    QueryProfile38(uint  iw30MinRelStart, uint  iw30MinRelEnd)
{
  MonitorString("\n QueryProfile38 "); MonitorIntDec(iw30MinRelStart); MonitorString(" "); MonitorIntDec(iw30MinRelEnd);

  InitPush(0);

  uchar bSize = 0;

  bSize += PushChar(0xC0);
  bSize += PushChar(0x06);

  PushAddress38();
  bSize += 4;

  bSize += PushChar(0x00);
  bSize += PushChar(0x06);

  bSize += PushChar(0x0B); // GET_DATA_MULTIPLE_EX
  bSize += PushChar(0x80);

  bSize += PushChar(0xD5); // 213
  bSize += PushChar(0x01);
  bSize += PushChar(0x03);
  bSize += PushIndex(iw30MinRelStart);
  bSize += PushIndex(iw30MinRelEnd);

  bSize += PushChar(0xD6); // 214
  bSize += PushChar(0x01);
  bSize += PushChar(0x03);
  bSize += PushIndex(iw30MinRelStart);
  bSize += PushIndex(iw30MinRelEnd);

  bSize += PushChar(0xD7); // 215
  bSize += PushChar(0x01);
  bSize += PushChar(0x03);
  bSize += PushIndex(iw30MinRelStart);
  bSize += PushIndex(iw30MinRelEnd);

  bSize += PushChar(0xD8); // 216
  bSize += PushChar(0x01);
  bSize += PushChar(0x03);
  bSize += PushIndex(iw30MinRelStart);
  bSize += PushIndex(iw30MinRelEnd);

  Query38(250, bSize+3);
}


void    QueryHeader38(void)
{
  HideCurrTime(1);

  QueryProfile38(wRelStart, wRelEnd);
}



void    MakeData38(uchar  h)
{
  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];
/*
  uchar i;
  for (i=0; i<4; i++)
  {
    double db = mpPrf38[h].mpdwValue[i];// mpdbBuffCanHou[i][h];
    mpdbEngFracDigCan[ibDig][i] += db;

    uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse/10000);
    mpwChannels[i] = w;

    mpdbEngFracDigCan[ibDig][i] -= (double)w*10000/dbPulse;
  }
*/
  uchar i;
  for (i=0; i<4; i++)
  {
    ulong dw = mpPrf38[h].mpdwValue[i];
    uint w = (uint)(dw*dbPulse/10000);

    mpwChannels[i] = w;
  }
}



bool    ReadBlock38(uchar  ibBlock)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

#ifdef MONITOR_38
  if (tiDig.bMinute % 30 != 0) MonitorString(" ??? ");
  MonitorString(" eff.="); MonitorTime(tiDig);
#endif

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  MakeData38(ibBlock);

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return(MakeStopHou(0));
}



bool    ReadData38(void)
{
  memset(&mpPrf38, 0, sizeof(mpPrf38));

  uchar* pbIn = InBuffPtr(10);

  uchar j;
  for (j=0; j<4; j++)
  {
    *(pbIn++);

    uchar h;
    for (h=0; h<6; h++)
    {
      int64_t ddw1 = 0;
      pbIn = DffDecodePositive(pbIn, &ddw1);
      ulong dw1 = ddw1 % 0x100000000;

      time tiTime = LongToTime38(dw1);
      mpPrf38[h].tiTime = tiTime;

      int64_t ddw2 = 0;
      pbIn = DffDecodePositive(pbIn, &ddw2);
      ulong dw2 = ddw2 % 0x100000000;

      uchar bStatus = (dw2 % 0x100) & 0x03;
      mpPrf38[h].bStatus = bStatus;

      ulong dwValue = dw2 >> 3;
      mpPrf38[h].mpdwValue[j] = dwValue;

#ifdef MONITOR_38
      MonitorString("\n "); MonitorTime(tiTime);
      MonitorString(" "); MonitorLongDec(dwValue);
      MonitorString(" "); MonitorCharDec(bStatus);
#endif
    }
  }

  uchar h;
  for (h=0; h<6; h++) {

#ifdef MONITOR_38
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      MonitorLongDec4(mpPrf38[h].mpdwValue[i]); MonitorString("  ");
    }
#endif

    ulong dw = DateToHouIndex(tiStart38);
    dw -= (wProfile38 + h);
    time tiVirtual = HouIndexToDate(dw);

    bool difference = DifferentDateTime(tiVirtual, mpPrf38[h].tiTime);

#ifdef MONITOR_38
    MonitorString(" vrt.="); MonitorTime(tiVirtual);
    MonitorString(" act.="); MonitorTime(mpPrf38[h].tiTime);
    MonitorBool(difference);
    MonitorString(" #"); MonitorCharDec(mpPrf38[h].bStatus); MonitorString(" ");
#endif

    if ((difference == true) && (mpPrf38[h].bStatus == 2))
      tiDig = tiVirtual;
    else if ((mpPrf38[h].tiTime.bMinute % 30 != 0) && (mpPrf38[h].bStatus == 0))
      tiDig = tiVirtual;
    else
      tiDig = mpPrf38[h].tiTime;

    if (ReadBlock38(h) == false) return false;
  }

  wProfile38 += 6;
  if (wProfile38 > wHOURS) return false;

  wRelStart += 6;
  wRelEnd = wRelStart + 5;

  return true;
}



#ifdef MONITOR_38

void    RunProfile38(void)
{
  QueryTime38();
  if (Input38() != SER_GOODCHECK) { MonitorString("\n error 1"); return; }

  tiValue38 = ReadTime38();
  dwValue38 = DateToHouIndex(tiValue38);

  InitHeader38();

  while (true) {
    QueryHeader38();
    if (Input38() != SER_GOODCHECK) { MonitorString("\n error 2"); return; }

    if (ReadData38() == false) { MonitorString("\n finish "); return; }
    if (fKey == true) return;
  }
}

#endif
