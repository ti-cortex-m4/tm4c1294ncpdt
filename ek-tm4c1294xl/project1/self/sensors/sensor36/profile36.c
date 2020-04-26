/*------------------------------------------------------------------------------
profile36!C

------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_ports.h"
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
#include "../../digitals/current/current_run.h"
#include "../../digitals/digitals.h"
#include "../../digitals/limits.h"
#include "../../special/special.h"
#include "../../hardware/watchdog.h"
#include "io36.h"
#include "../device_k.h"
#include "../device_q.h"
#include "current36.h"
#include "profile36.h"



uchar                   ibLine36, bMaxLine36;



void    InitHeader36(void)
{
  if (!UseBounds())
    wBaseCurr = 0; // счетчик суток
  else
  {
    wBaseCurr = mpcwStartAbs16Can[ibDig];
    Clear(); sprintf(szLo+3,"начало %2u",wBaseCurr);
    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;
}


void    QueryHeader36Internal(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('G');
  PushChar1Bcc('R');
  PushChar1Bcc('A');

  PushLineBcc(ibLine36);

  PushChar1Bcc('(');
  PushChar2Bcc(tiDig.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bYear);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQuery36(2000, 4+16+1, 48);
}


void    QueryHeader36(void)
{
  HideCurrTime(1);

  if (wBaseCurr == 0)
    tiDig = tiDigPrev;
  else
  {
    ulong dw = DateToDayIndex(tiDigPrev);
    dw -= wBaseCurr;
    tiDig = DayIndexToDate(dw);

    tiDig.bHour   = 23;
    tiDig.bMinute = 30;
  }

  szHi[10] = 'A' + ibLine36;

  bMaxLine36 = GetMaxLine36(ibDig);
  QueryHeader36Internal();
}



void    ReadHeader36(void)
{
  InitPop(1);

  uchar h;
  for (h=0; h<48; h++)
  {
    mpdbBuffCanHou[ibLine36][h] = PopDoubleQ()/2;
  }
}


void    ReadHeader36_SkipLine(uchar  ibLine)
{
  uchar h;
  for (h=0; h<48; h++)
  {
    mpdbBuffCanHou[ibLine][h] = 0;
  }
}



void    MakeData36(uchar  ibHou)
{
  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<bMaxLine36; i++)
  {
    double db = mpdbBuffCanHou[i][ibHou];
    mpdbEngFracDigCan[ibDig][i] += db;

    uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse);
    mpwChannels[i] = w;

    mpdbEngFracDigCan[ibDig][i] -= (double)w/dbPulse;
  }
}


bool    ReadData36(void)
{
uchar   j;

  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  if ((tiDig.bDay   == tiCurr.bDay)   &&
      (tiDig.bMonth == tiCurr.bMonth) &&
      (tiDig.bYear  == tiCurr.bYear))
    j = 47-(tiCurr.bHour*2+tiCurr.bMinute/30);
  else
    j = 0;

  ulong dwHouIndex = DateToHouIndex(tiDig);

  uchar h;
  for (h=j; h<48; h++)
  {
    ResetWatchdog();
    MakeData36(47-h);

    MakeSpecial(tiDig);
    if (MakeStopHou(0) == 0) return(0);

    dwHouIndex--;
    tiDig = HouIndexToDate(dwHouIndex);

    iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;
  }

  NewBoundsAbs16(++wBaseCurr);
  return(1);
}
