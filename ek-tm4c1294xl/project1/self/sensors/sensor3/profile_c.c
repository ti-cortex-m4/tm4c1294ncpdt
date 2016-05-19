/*------------------------------------------------------------------------------
PROFILE_C!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
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
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../digitals/current/current2.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/limits.h"
#include "../../digitals/profile/refill.h"
#include "../../special/special.h"
#include "../../flash/records.h"
#include "../../energy.h"
#include "device_c.h"



#ifndef SKIP_C

uint                    cwShutdownC;



void    InitHeaderC1(void)
{
  cwShutdownC = 0;

  if (!UseBounds())
    wBaseCurr = 0;
  else
  {
    wBaseCurr = mpcwStartRelCan[ibDig];
    sprintf(szLo," начало %04u:%02u ",wBaseCurr,(uchar)(wBaseCurr/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;
}


void    InitHeaderC6(void)
{
uchar i;

  if (!UseBounds())
    wBaseCurr = 0;
  else
  {
    wBaseCurr = (mpcwStartRelCan[ibDig] / 6) * 6;
    sprintf(szLo," начало %04u:%02u ",wBaseCurr,(uchar)(wBaseCurr/48 + 1));
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
  dw -= wBaseCurr;
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
  dw -= wBaseCurr;
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
  return ReadHeaderC(0);
}


bool    ReadHeaderC6(void)
{
uchar i;

  for (i=0; i<6; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);
    dw += 5;
    dw -= (wBaseCurr + i);
    tiDig = HouIndexToDate(dw);

    if (dw < dwValueC)
      if (ReadHeaderC(5-i) == 0) return(0);
  }

  wBaseCurr += 6;
  if (wBaseCurr > wHOURS) return(0);

  return(1);
}

#endif
