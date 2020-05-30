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
unsigned char  pucDecodeBitArr(unsigned char *pOut, unsigned char *pIn);


typedef struct
{
  bool          fPresent;
  time          tiTime[4];
  ulong         mpdwValue[4];
} profile38;




uint                    wProfile38;
static uint             wRelStart, wRelEnd;

profile38               mpProfiles38[6];

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
  wRelStart = 0;

  uchar i = tiValue38.bHour*2 + tiValue38.bMinute/30;
  i = i % 6;
  if (i == 0) i = 6;

  wRelEnd = i;

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



void    ReadHeader38(void)
{
  InitPop(1);

  uchar h;
  for (h=0; h<6; h++)
  {
    mpdbBuffCanHou[0/*ibLine38*/][h] = 0; //PopDoubleQ()/2;
  }
}



void    MakeData38(uchar  h)
{
  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<4; i++)
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
      mpProfiles38[k].tiTime[j] = ti;

      ulong dw2 = 0;
      uchar i2 = pucDecodeBitArr((uchar *) &dw2, &mpbInBuff3[ibIdx]);
      ibIdx += i2; //0xFF
//      MonitorString(" i2="); MonitorCharDec(i2); MonitorString(" ");

      uchar bStatus = (dw2 % 0x100) & 0x03;
      MonitorString(" s="); MonitorCharDec(bStatus); MonitorString(" ");
      ulong dwValue = dw2 >> 3;
      mpProfiles38[k].mpdwValue[j] = dwValue;
      MonitorLongDecimal(dwValue, 10000);
    }
  }

  MonitorString("\n Result");

  uchar a;
  for (a=0; a<6; a++) {
    MonitorString("\n");

    MonitorBool(mpProfiles38[a].fPresent);

    uchar b;
    for (b=0; b<4; b++) {
      MonitorTime(mpProfiles38[a].tiTime[b]);
      MonitorLongDecimal(mpProfiles38[b].mpdwValue[b], 10000);
    }
  }

  return false;
}



void    RunProfile38(void)
{
  InitHeader38();

  while (true) {
    QueryHeader38();
    if (Input38() != SER_GOODCHECK) { MonitorString("\n error "); return; }

    if (ReadData38() == false) { MonitorString("\n done "); return; }
    Delay(500);
  }
}
