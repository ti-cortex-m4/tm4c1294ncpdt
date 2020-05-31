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
  time          tiTime;
  uchar         bStatus;
  ulong         mpdwValue[4];
} profile38;



static uint             wProfile38;
static uint             wRelStart, wRelEnd;
static profile38        mpProfiles38[6];
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
    sprintf(szLo," ������ %04u:%02u ",wProfile38,(uchar)(wProfile38/48 + 1));
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



void    QueryProfile38(uchar  ib30MinRelStart, uchar  ib30MinRelEnd)
{
  MonitorString("\n QueryProfile38 "); MonitorCharDec(ib30MinRelStart); MonitorString(" "); MonitorCharDec(ib30MinRelEnd);

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
  PushChar(ib30MinRelStart);
  PushChar(ib30MinRelEnd);

  PushChar(0xD6); // 214
  PushChar(0x03);
  PushChar(ib30MinRelStart);
  PushChar(ib30MinRelEnd);

  PushChar(0xD7); // 215
  PushChar(0x03);
  PushChar(ib30MinRelStart);
  PushChar(ib30MinRelEnd);

  PushChar(0xD8); // 216
  PushChar(0x03);
  PushChar(ib30MinRelStart);
  PushChar(ib30MinRelEnd);

  Query38(250, 29);
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

  uchar i;
  for (i=0; i<4; i++)
  {
    double db = mpProfiles38[h].mpdwValue[i];// mpdbBuffCanHou[i][h];
    mpdbEngFracDigCan[ibDig][i] += db;

    uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse/10000);
    mpwChannels[i] = w;

    mpdbEngFracDigCan[ibDig][i] -= (double)w*10000/dbPulse;
  }
/*
  uchar i;
  for (i=0; i<4; i++)
  {
    ulong dw = mpProfiles38[h].mpdwValue[i];
    uint w = (uint)(dw*dbPulse/10000);

    mpwChannels[i] = w;
  }
*/
}



bool    ReadBlock38(uchar  ibBlock)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

#ifdef MONITOR_38
  if (tiDig.bMinute % 30 != 0) MonitorString(" ??? ");
  MonitorString(" effective="); MonitorTime(tiDig);
#endif

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  MakeData38(ibBlock);

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return(MakeStopHou(0));
}



bool    ReadData38(void)
{
  memset(&mpProfiles38, 0, sizeof(mpProfiles38));

  uchar ibIn = 10;

  uchar j;
  for (j=0; j<4; j++)
  {
    MonitorString("\n");
    ibIn++;

    uchar k;
    for (k=0; k<6; k++)
    {
      MonitorString("\n");
      ulong dw1 = 0;
      uchar i1 = pucDecodeBitArr((uchar *) &dw1, InBuffPtr(ibIn));
      ibIn += i1; //0xFF
//      MonitorString(" i1="); MonitorCharDec(i1); MonitorString(" ");
      time ti = LongToTime38(dw1);
      MonitorTime(ti);
      mpProfiles38[k].tiTime/*s[j]*/ = ti;

      ulong dw2 = 0;
      uchar i2 = pucDecodeBitArr((uchar *) &dw2, InBuffPtr(ibIn));
      ibIn += i2; //0xFF
//      MonitorString(" i2="); MonitorCharDec(i2); MonitorString(" ");

      uchar bStatus = (dw2 % 0x100) & 0x03;
      mpProfiles38[k].bStatus = bStatus;
      MonitorString(" #"); MonitorCharDec(bStatus); MonitorString(" ");

      ulong dwValue = dw2 >> 3;
      mpProfiles38[k].mpdwValue[j] = dwValue;
      MonitorLongDecimal4(dwValue);
    }
  }

  uchar h;
  for (h=0; h<6; h++) {

#ifdef MONITOR_38
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      MonitorLongDecimal4(mpProfiles38[h].mpdwValue[i]); MonitorString("  ");
    }
#endif

    ulong dw = DateToHouIndex(tiStart38);
    dw -= (wProfile38 + h);
    time tiVirtual = HouIndexToDate(dw);

    bool different = DifferentDateTime(tiVirtual,mpProfiles38[h].tiTime);

#ifdef MONITOR_38
    MonitorString(" virtual="); MonitorTime(tiVirtual);
    MonitorString(" actual="); MonitorTime(mpProfiles38[h].tiTime);
    MonitorBool(different);
    MonitorString(" #"); MonitorCharDec(mpProfiles38[h].bStatus); MonitorString(" ");
#endif

    if ((different == true) && (mpProfiles38[h].bStatus == 2))
      tiDig = tiVirtual;
    else if ((mpProfiles38[h].tiTime.bMinute % 30 != 0) && (mpProfiles38[h].bStatus == 0))
      tiDig = tiVirtual;
    else
      tiDig = mpProfiles38[h].tiTime;

    if (ReadBlock38(h) == false) return false;
  }

  wProfile38 += 6;
  if (wProfile38 > 100/*wHOURS*/) return false;

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
