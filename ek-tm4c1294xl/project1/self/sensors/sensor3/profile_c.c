/*------------------------------------------------------------------------------
PROFILE_C!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_limits.h"
#include "../../display/display.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/calendar.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../digitals/limits.h"
#include "../../digitals/max_shutdown.h"
#include "../../digitals/profile/profile_interval.h"
#include "../../special/special.h"
#include "profile_c.h"



static uint             wProfileC;
static uint             cwShutdownC;



void    InitHeaderC1(void)
{
  cwShutdownC = 0;

  if (!UseBounds())
    wProfileC = 0;
  else
  {
    wProfileC = mpcwStartRelCan[ibDig];
    sprintf(szLo," начало %04u:%02u ",wProfileC,(uchar)(wProfileC/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;
}


void    InitHeaderC6(void)
{
uchar i;

  if (!UseBounds())
    wProfileC = 0;
  else
  {
    wProfileC = (mpcwStartRelCan[ibDig] / 6) * 6;
    sprintf(szLo," начало %04u:%02u ",wProfileC,(uchar)(wProfileC/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;

  i = tiDigPrev.bHour*2 + tiDigPrev.bMinute/30;
  i = (i / 6) * 6;

  tiDigPrev.bHour = i / 2;
  tiDigPrev.bMinute = (i % 2)*30;
}


void    QueryHeaderC1(void)
{
  HideCurrTime(1);

  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wProfileC;
  tiDig = HouIndexToDate(dw);


  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);
  PushChar(36);

  PushChar(tiDig.bMonth);
  PushChar(tiDig.bDay);
  PushChar(tiDig.bHour*2 + tiDig.bMinute/30);

  RevQueryIO(4+8+2, 3+3+2);
}


void    QueryHeaderC6(void)
{
  HideCurrTime(1);

  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wProfileC;
  tiDig = HouIndexToDate(dw);


  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);
  PushChar(40);

  PushChar(tiDig.bMonth);
  PushChar(tiDig.bDay);
  PushChar(tiDig.bHour*2 + tiDig.bMinute/30);

  RevQueryIO(4+8*6+2, 3+3+2);
}


bool    ReadHeaderC(uchar  ibBlock)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);
  MonitorString("\n time "); MonitorTime(tiDig);

  if (SearchDefHouIndex(tiDig) == 0) return(1);


  ShowProgressDigHou();

  InitPop(4+ibBlock*8);

  uchar i;
  for (i=0; i<4; i++)
  {
    uint w = PopChar();
    w += PopChar()*0x100;

    mpwChannels[i] = w;
  }

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return(MakeStopHou(0));
}


bool    ReadHeaderC1(void)
{
  cwShutdownC = 0;

  if (ReadHeaderC(0) == 0)
    return(0);
  else if (++wProfileC > wHOURS)
    return(0);
  else {
    MonitorString("\n");
    return(1);
  }
}

bool    ReadHeaderC1_Shutdown(void)
{
  if (++cwShutdownC > GetMaxShutdown())
    return(0);
  else
  {
    Clear(); sprintf(szLo+1,"выключено: %-4u",cwShutdownC);

    iwDigHou = (wHOURS+iwHardHou-wProfileC)%wHOURS;
    ShowProgressDigHou();

    MonitorString("\n");

    if (MakeStopHou(0) == 0)
      return(0);
    else if (++wProfileC > wHOURS)
      return(0);
    else
      return(1);
  }
}


bool    ReadHeaderC6(void)
{
  uchar i;
  for (i=0; i<6; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);
    dw += 5;
    dw -= (wProfileC + i);
    tiDig = HouIndexToDate(dw);

    if (dw < dwValueC)
      if (ReadHeaderC(5-i) == 0) return(0);
  }

  wProfileC += 6;
  if (wProfileC > wHOURS) return(0);

  if ((boProfileInterval == true) && IsStopProfileInterval())
  {
    ShowLo(" приостановка...");
    return(0);
  }
  else
  {
    MonitorString("\n");
    return(1);
  }
}
