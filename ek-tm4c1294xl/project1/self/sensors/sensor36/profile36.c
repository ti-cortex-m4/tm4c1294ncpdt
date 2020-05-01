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
#include "../../serial/monitor.h"
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



static uint             wProfile36;

time                    tiValue36;
ulong                   dwValue36;

uchar                   ibLine36, bMaxLine36;



bool    HasPassword36(void)
{
  return mpdwAddress2[diCurr.bAddress-1] != MAX_LONG;
}


void    QueryPassword36(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('P');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);
  PushChar1Bcc('(');

  uchar n = PushNumberBcc(mpdwAddress2[diCurr.bAddress-1]);

  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(2000+1+1, 5+n+2+1, 0);
}



void    QueryCorrect36(void)
{
  InitPush(0);

  PushChar1Bcc('/');
  PushChar1Bcc('?');

  PushChar1Bcc('C');
  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');
  PushChar1Bcc('!');

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  Query36(1000, 2+6+2, 1);
}


void    QueryControl36(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('W');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');
  PushChar1Bcc('_');

  PushChar1Bcc('(');
  PushChar2Bcc(tiCurr.bHour);
  PushChar1Bcc(':');
  PushChar2Bcc(tiCurr.bMinute);
  PushChar1Bcc(':');
  PushChar2Bcc(tiCurr.bSecond);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQuery36(2000+1+1, 4+16+1, 0);
}



void    QueryTimeProfile36(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');
  PushChar1Bcc('_');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(2000+1+17+2, 4+8+1, 0);
}


void    QueryDateProfile36(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('D');
  PushChar1Bcc('A');
  PushChar1Bcc('T');
  PushChar1Bcc('E');
  PushChar1Bcc('_');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(2000+1+20+2, 4+8+1, 0);
}



void    InitHeader36(void)
{
  if (!UseBounds())
    wProfile36 = 0;
  else
  {
    wProfile36 = (mpcwStartRelCan[ibDig] / 6) * 6;
    sprintf(szLo," начало %04u:%02u ",wProfile36,(uchar)(wProfile36/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;

  uchar i = tiDigPrev.bHour*2 + tiDigPrev.bMinute/30;
  i = (i / 6) * 6;

  tiDigPrev.bHour = i / 2;
  tiDigPrev.bMinute = (i % 2)*30;
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
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bHour*2 + 1);
  PushChar1Bcc('.');
  PushChar1Bcc('6');
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQuery36(2000, 4+21+1, 48);
}


void    QueryHeader36(void)
{
  MonitorString("\n *** QueryHeader36 "); MonitorCharDec(ibLine36);

  HideCurrTime(1);

  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wProfile36;
  tiDig = HouIndexToDate(dw);


  szHi[10] = 'A' + ibLine36;
  szHi[11] = ' ';


  bMaxLine36 = GetMaxLine36(ibDig);
  QueryHeader36Internal();
}



void    ReadHeader36(void)
{
  InitPop(1);

  uchar h;
  for (h=0; h<6; h++)
  {
    mpdbBuffCanHou[ibLine36][h] = PopDoubleQ()/2;
  }
}


void    ReadHeader36_SkipLine(uchar  ibLine)
{
  uchar h;
  for (h=0; h<6; h++)
  {
    mpdbBuffCanHou[ibLine][h] = 0;
  }
}



void    MakeData36(uchar  h)
{
  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<bMaxLine36; i++)
  {
    double db = mpdbBuffCanHou[i][h];
    mpdbEngFracDigCan[ibDig][i] += db;

    uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse);
    mpwChannels[i] = w;

    mpdbEngFracDigCan[ibDig][i] -= (double)w/dbPulse;
  }
}

/*
bool    ReadData36_(void)
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
*/


bool    ReadBlock36(uchar  ibBlock)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);
  MonitorString("\n time "); MonitorTime(tiDig);

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  MakeData36(ibBlock);

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return(MakeStopHou(0));
}



bool    ReadData36(void)
{
  uchar i;
  for (i=0; i<6; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);
    dw += 6-1;
    dw -= (wProfile36 + i);
    tiDig = HouIndexToDate(dw);

    if (dw < dwValue36) {
      if (ReadBlock36(6-1-i) == 0) return(0);
    }
  }

  wProfile36 += 6;
  if (wProfile36 > wHOURS) return(0);

  MonitorString("\n");
  return(1);
}
