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



#include "../../memory/mem_serial3.h"
#include "../../keyboard/keyboard.h"
unsigned char  pucDecodeBitArr(unsigned char *pOut, unsigned char *pIn);


typedef struct
{
  bool          fPresent;
  time          tiTime;
  uchar         bStatus;
//  time          tiTimes[4];
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
//
//  ulong dw = DateToHouIndex(tiDigPrev);
//  dw -= wProfile38;
//  tiDig = HouIndexToDate(dw);
//

  QueryProfile38(wRelStart, wRelEnd);
}


/*
void    ReadHeader38(void)
{
  InitPop(1);

  uchar h;
  for (h=0; h<6; h++)
  {
    mpdbBuffCanHou[0/ *ibLine38* /][h] = 0; //PopDoubleQ()/2;
  }
}
*/


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
  MonitorString(" time="); MonitorTime(tiDig);

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  MakeData38(ibBlock);

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return(MakeStopHou(0));
}



bool    CompareTimes(time  ti1, time  ti2)
{
  if (ti1.bSecond != ti2.bSecond) return false;
  if (ti1.bMinute != ti2.bMinute) return false;
  if (ti1.bHour   != ti2.bHour)   return false;
  if (ti1.bDay    != ti2.bDay)    return false;
  if (ti1.bMonth  != ti2.bMonth)  return false;
  if (ti1.bYear   != ti2.bYear)   return false;
  return true;
}



bool    ReadData38(void)
{
/*
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
*/

  memset(&mpProfiles38, 0, sizeof(mpProfiles38));

  uchar ibIdx = 10;

  int count = wRelEnd - wRelStart + 1;
  MonitorString("\n count="); MonitorCharDec(count);

  uchar j;
  for (j=0; j<4; j++)
  {
    MonitorString("\n");
    ibIdx++;

    uchar k;
    for (k=0; k<count; k++)
    {
      MonitorString("\n");
      ulong dw1 = 0;
      uchar i1 = pucDecodeBitArr((uchar *) &dw1, &mpbInBuff3[ibIdx]);
      ibIdx += i1; //0xFF
//      MonitorString(" i1="); MonitorCharDec(i1); MonitorString(" ");
      time ti = SecIndexToDate(dw1);
      ti.bYear += 12;
      MonitorTime(ti);
      mpProfiles38[k].fPresent = true;
      mpProfiles38[k].tiTime/*s[j]*/ = ti;

      ulong dw2 = 0;
      uchar i2 = pucDecodeBitArr((uchar *) &dw2, &mpbInBuff3[ibIdx]);
      ibIdx += i2; //0xFF
//      MonitorString(" i2="); MonitorCharDec(i2); MonitorString(" ");

      uchar bStatus = (dw2 % 0x100) & 0x03;
      mpProfiles38[k].bStatus = bStatus;
      MonitorString(" #"); MonitorCharDec(bStatus); MonitorString(" ");
      ulong dwValue = dw2 >> 3;
      mpProfiles38[k].mpdwValue[j] = dwValue;
      MonitorLongDecimal4(dwValue);
    }
  }

  MonitorString("\n Result");

  uchar a;
  for (a=0; a<6; a++) {
    MonitorString("\n");

    MonitorBool(mpProfiles38[a].fPresent);
    MonitorString("   ");

    uchar b;
    for (b=0; b<4; b++) {
      MonitorLongDecimal4(mpProfiles38[a].mpdwValue[b]); MonitorString("   ");
    }

    ulong dw = DateToHouIndex(tiStart38);
    dw -= (wProfile38 + a);
    time tiVirtual = HouIndexToDate(dw);

    bool equal = CompareTimes(tiVirtual,mpProfiles38[a].tiTime);

    MonitorString(" vrt="); MonitorTime(tiVirtual);
    MonitorString(" act="); MonitorTime(mpProfiles38[a].tiTime);
    MonitorBool(equal);
    MonitorString(" #"); MonitorCharDec(mpProfiles38[a].bStatus); MonitorString(" ");

    if ((equal == false) && (mpProfiles38[a].bStatus == 2))
      tiDig = tiVirtual;
    else
      tiDig = mpProfiles38[a].tiTime;

    if (ReadBlock38(a) == false) return false;
  }

  wProfile38 += 6;
  if (wProfile38 > 100/*wHOURS*/) return false;

  wRelStart += 6;
  wRelEnd = wRelStart + 5;

  return true;
}



void    RunProfile38(void)
{
  QueryTime38();
  if (Input38() != SER_GOODCHECK) { MonitorString("\n error "); return; }

  tiValue38 = ReadTime38();
  dwValue38 = DateToHouIndex(tiValue38);

  InitHeader38();

  while (true) {
    QueryHeader38();
    if (Input38() != SER_GOODCHECK) { MonitorString("\n error "); return; }

    if (ReadData38() == false) { MonitorString("\n done "); return; }
    if (fKey == true) return;
  }
}
