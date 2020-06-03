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
#include "io38.h"
#include "dff.h"
#include "device38.h"
#include "profile38.h"



#include "../../keyboard/keyboard.h"
unsigned char  pucDecodeBitArr(unsigned char *pOut, unsigned char *pIn);



typedef struct
{
  time          ti;
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
//  PushIntBig(0);
//  SkipBack(-2);

  int64_t ddw = iw30MinRel;
//  ulong dw = 0;
  uchar n = EncodeInt(ddw, OutBuffPtr(GetPush()));
  MonitorString(" n="); MonitorCharDec(n);

//  PushChar((dw % 0x10000) % 0x1000);
//  PushChar((dw % 0x10000) / 0x1000);
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
/*
  PushChar(0xD6); // 214
  PushChar(0x01);
  PushChar(0x03);
  PushIndex(iw30MinRelStart);
  PushIndex(iw30MinRelEnd);

  PushChar(0xD7); // 215
  PushChar(0x01);
  PushChar(0x03);
  PushIndex(iw30MinRelStart);
  PushIndex(iw30MinRelEnd);

  PushChar(0xD8); // 216
  PushChar(0x01);
  PushChar(0x03);
  PushIndex(iw30MinRelStart);
  PushIndex(iw30MinRelEnd);
*/
  Query38(250, bSize+3/*41*/);
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

  uchar ibIn = 10;

  uchar j;
  for (j=0; j<1/*4*/; j++)
  {
    ibIn++;

    uchar k;
    for (k=0; k<6; k++)
    {
      ulong dw1 = 0;
      uchar i1 = pucDecodeBitArr((uchar *) &dw1, InBuffPtr(ibIn));
      ibIn += i1; //0xFF

      time ti = LongToTime38(dw1);
      MonitorString("\n ti "); MonitorTime(ti);
      mpPrf38[k].ti = ti;

      ulong dw2 = 0;
      uchar i2 = pucDecodeBitArr((uchar *) &dw2, InBuffPtr(ibIn));
      MonitorString("\n vl "); MonitorLongDec(dw2);
      ibIn += i2; //0xFF

      uchar bStatus = (dw2 % 0x100) & 0x03;
      mpPrf38[k].bStatus = bStatus;

      ulong dwValue = dw2 >> 3;
      mpPrf38[k].mpdwValue[j] = dwValue;
    }
  }

  uchar h;
  for (h=0; h<6; h++) {

#ifdef MONITOR_38
    MonitorString("\n");

    uchar i;
    for (i=0; i<1/*4*/; i++) {
      MonitorLongDecimal4(mpPrf38[h].mpdwValue[i]); MonitorString("  ");
    }
#endif

    ulong dw = DateToHouIndex(tiStart38);
    dw -= (wProfile38 + h);
    time tiVirtual = HouIndexToDate(dw);

    bool different = DifferentDateTime(tiVirtual,mpPrf38[h].ti);

#ifdef MONITOR_38
    MonitorString(" vrt.="); MonitorTime(tiVirtual);
    MonitorString(" act.="); MonitorTime(mpPrf38[h].ti);
    MonitorBool(different);
    MonitorString(" #"); MonitorCharDec(mpPrf38[h].bStatus); MonitorString(" ");
#endif

    if ((different == true) && (mpPrf38[h].bStatus == 2))
      tiDig = tiVirtual;
    else if ((mpPrf38[h].ti.bMinute % 30 != 0) && (mpPrf38[h].bStatus == 0))
      tiDig = tiVirtual;
    else
      tiDig = mpPrf38[h].ti;

    if (ReadBlock38(h) == false) return false;
  }

  wProfile38 += 6;
  if (wProfile38 > 200/*wHOURS*/) return false;

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
