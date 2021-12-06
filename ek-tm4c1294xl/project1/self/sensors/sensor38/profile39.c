/*------------------------------------------------------------------------------
profile39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_settings.h"
//#include "../../memory/mem_digitals.h"
//#include "../../memory/mem_ports.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy_spec.h"
//#include "../../memory/mem_profile.h"
//#include "../../memory/mem_limits.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
//#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_common.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
//#include "../../digitals/digitals.h"
//#include "../../digitals/limits.h"
#include "../../special/special.h"
#include "device38.h"
#include "time38.h"
#include "io38.h"
#include "dff.h"
#include "profile38.h"
#include "profile39.h"



extern uint             wProfile38;
extern uint             wRelStart38, wRelEnd38;
extern profile38        mpPrf38[6];
extern time             tiStart38;
extern ulong            dwHouStart38;



void    QueryProfile39(uint  iw30MinRelStart, uint  iw30MinRelEnd)
{
#ifdef MONITOR_38
  MonitorString("\n QueryProfile39 "); MonitorIntDec(iw30MinRelStart); MonitorString(" "); MonitorIntDec(iw30MinRelEnd);
#endif

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

  bSize += PushChar(0x19);
  bSize += PushChar(3);
  bSize += PushIndex(iw30MinRelStart);
  bSize += PushIndex(iw30MinRelEnd);

  bSize += PushChar(0x1A);
  bSize += PushChar(3);
  bSize += PushIndex(iw30MinRelStart);
  bSize += PushIndex(iw30MinRelEnd);

  bSize += PushChar(0x1B);
  bSize += PushChar(3);
  bSize += PushIndex(iw30MinRelStart);
  bSize += PushIndex(iw30MinRelEnd);

  bSize += PushChar(0x1C);
  bSize += PushChar(3);
  bSize += PushIndex(iw30MinRelStart);
  bSize += PushIndex(iw30MinRelEnd);

  Query38(250, bSize+3);
}


void    QueryHeader39(void)
{
  HideCurrTime(1);

#ifdef MONITOR_38
  MonitorString("\n QueryHeader39 ");
  MonitorString(" wProfile38="); MonitorIntDec(wProfile38);
  MonitorString(" wRelStart38="); MonitorIntDec(wRelStart38);
  MonitorString(" wRelEnd38="); MonitorIntDec(wRelEnd38);
#endif

  QueryProfile38(wRelStart38, wRelEnd38);
}



void    MakeData39(uchar  h)
{
  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];
/*
  uchar i;
  for (i=0; i<4; i++)
  {
    double db = mpPrf38[h].mpdwValue[i];
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



bool    ReadBlock39(uchar  ibBlock)
{
  if (tiDig.bYear == 0)
    sprintf(szLo," выключено: %-4u   ",cwShutdown38);
  else
    sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

#ifdef MONITOR_38
  if (tiDig.bMinute % 30 != 0) MonitorString(" ??? ");
  MonitorString(" eff.="); MonitorTime(tiDig);
#endif

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  MakeData39(ibBlock);

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return(MakeStopHou(0));
}



bool    ReadData39(void)
{
  memset(&mpPrf38, 0, sizeof(mpPrf38));

  uchar* pbIn = InBuffPtr(10);

  uchar c;
  for (c=0; c<4; c++)
  {
    uchar bCode = *pbIn;
    *(pbIn++);

    MonitorString("\n code="); MonitorCharHex(bCode);
    if (mbCodes[c] != bCode) {
      MonitorString("\n ***************************************** ");
    }
#ifdef MONITOR_38
    MonitorString(" pointer="); MonitorIntDec(pbIn - InBuffPtr(0));
    MonitorString(" size="); MonitorIntDec(IndexInBuff());
#endif

    uchar h;
    for (h=0; h<6; h++)
    {
      int64_t ddw = 0;
      pbIn = DffDecodePositive(pbIn, &ddw);

      if (ddw == 2) {
         mpPrf38[h].tiTime = tiZero;
         cwShutdown38++;
      } else {
         mpPrf38[h].tiTime = SecondsToTime38(ddw % 0x100000000);
         cwShutdown38 = 0;
      }

      ddw = 0;
      pbIn = DffDecodePositive(pbIn, &ddw);

      mpPrf38[h].bStatus = (ddw % 0x100) & 0x03;
      mpPrf38[h].mpdwValue[c] = (ddw >> 3) % 0x100000000;

#ifdef MONITOR_38
      MonitorString("\n "); MonitorTime(mpPrf38[h].tiTime);
      MonitorString(" "); MonitorLongDec(mpPrf38[h].mpdwValue[c]);
      MonitorString(" "); MonitorCharDec(mpPrf38[h].bStatus);
#endif
    }
  }


  ulong dwHouNow = DateToHouIndex(tiCurr);
  uchar d = dwHouNow - dwHouStart;

#ifdef MONITOR_38
  MonitorString("\n delta="); MonitorCharDec(d);
#endif


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
    dw -= (wProfile38 + h - d);
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

    if (ReadBlock39(h) == false) return false;
  }

  wProfile38 += 6;
  if (wProfile38 > wHOURS) return false;

  wRelStart38 += 6;
  wRelEnd38 = wRelStart38 + 5;

  return true;
}



#ifdef MONITOR_38

void    RunProfile39(void)
{
  QueryTime38();
  if (Input38() != SER_GOODCHECK) { MonitorString("\n error 1"); return; }

  tiValue38 = ReadTime38();
  dwValue38 = DateToHouIndex(tiValue38);

  InitHeader38();

  while (true) {
    QueryHeader39();
    if (Input38() != SER_GOODCHECK) { MonitorString("\n error 2"); return; }

    if (ReadData39() == false) { MonitorString("\n finish "); return; }
    if (fKey == true) return;
  }
}

#endif
