/*------------------------------------------------------------------------------
DEVICE_Q!C

Энергомера СЕ304
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
//#include "../memory/mem_settings.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_current.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_limits.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
#include "../devices/devices_time.h"
#include "../digitals/current/current_run.h"
#include "../digitals/limits.h"
#include "../special/special.h"
#include "../hardware/watchdog.h"
#include "../display/display.h"
#include "../keyboard/time/key_timedate.h"
//#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../time/delay.h"
#include "device_k.h"
#include "device_q.h"



#ifndef SKIP_Q

double  PopDoubleQ(void)
{
double  dbA,dbB;

  uchar a = 0;
  uchar b = 0;

  uchar i;
  for (i=0; i<40; i++)
  {
    uchar bT = PopChar() & 0x7F;

    if (a == 0)
    {
      if (bT == '(') a = i+1;

      dbA = 0;
      dbB = 1;
    }
    else
    {
      if (bT == '.') { b = i-1; continue; }

      if ((bT == ')') || (bT == ','))
      {
        for (i=a; i<b; i++) dbA *= 10;
        return dbA;
      }

      if ((bT >= '0') && (bT <= '9'))
        bT -= '0';
      else
        break;

      dbA += dbB*bT;
      dbB /= 10;
    }
  }

  return 0;
}


void    QueryCloseQ(void)
{
  QueryCloseK();
}



void    QueryOptionQ(void)
{
  InitPush(0);
  PushChar1Bcc(0x06);

  uchar i;
  switch (mppoPorts[ diCurr.ibPort ].ibBaud)
  {
    case 0:  i = '2'; break;
    case 1:  i = '3'; break;
    case 2:  i = '4'; break;
    case 3:  i = '5'; break;
    case 4:  i = '6'; break;
    default: i = '7'; break;
  }

  PushChar1Bcc('0');
  PushChar1Bcc(i);
  PushChar1Bcc('1');

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  Query(1+6+2, 4+2, 1);
}


void    QueryCorrectQ(void)
{
  InitPush(0);

  PushChar1Bcc('/');
  PushChar1Bcc('?');

  PushChar1Bcc('C');
  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');

  PushChar1Bcc('(');
  PushChar2Bcc(tiCurr.bHour);
  PushChar1Bcc(':');
  PushChar2Bcc(tiCurr.bMinute);
  PushChar1Bcc(':');
  PushChar2Bcc(tiCurr.bSecond);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQueryIO(1000, 2+16+1, 0);
}



void    QueryEnergyAbsQ(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('T');
  PushChar1Bcc('0');
  PushChar1Bcc('0');

  PushChar1Bcc('(');
  PushChar1Bcc('1');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+6*28+2, n+9+1, 6);
}


void    QueryEnergyDayQ(time  ti)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('D');
  PushChar1Bcc('0');
  PushChar1Bcc('0');

  PushChar1Bcc('(');
  PushChar2Bcc(ti.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(ti.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(ti.bYear);
  PushChar1Bcc(',');
  PushChar1Bcc('1');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+6*28+2, n+18+1, 6);
}


void    QueryEnergyMonQ(time  ti)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('M');
  PushChar1Bcc('0');
  PushChar1Bcc('0');

  PushChar1Bcc('(');
  PushChar2Bcc(ti.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(ti.bYear);
  PushChar1Bcc(',');
  PushChar1Bcc('1');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+6*28+2, n+15+1, 6);
}


void    QueryEnergySpecQ(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('T');
  PushChar1Bcc('0');
  PushChar1Bcc('0');

  PushChar1Bcc('(');
  PushChar1Bcc('1');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+6*28+2, 4+9+1, 6);
}


void    ReadEnergyQ(void)
{
  InitPop(1);

  uchar i;
  for (i=0; i<MAX_LINE_Q; i++)
  {
    mpdbChannelsC[i] = PopDoubleQ();
  }
}



void    InitHeaderQ(void)
{
  if (!UseBounds())
    wBaseCurr = 0;
  else
  {
    wBaseCurr = mpcwStartRelCan[ibDig];
    Clear(); sprintf(szLo+1,"начало %04u:%02u",wBaseCurr,(uchar)(wBaseCurr/48 + 1));
    DelayMsg();
  }

  tiDigPrev = tiCurr;
}


void    QueryHeaderQ_22(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('V');
  PushChar1Bcc('P');
  PushChar1Bcc('R');

  if (ibMinor == 0)
  {
    PushChar1Bcc('0');
    PushChar1Bcc('1');
  }
  else if (ibMinor == 1)
  {
    PushChar1Bcc('0');
    PushChar1Bcc('2');
  }
  else if (ibMinor == 2)
  {
    PushChar1Bcc('0');
    PushChar1Bcc('3');
  }
  else if (ibMinor == 3)
  {
    PushChar1Bcc('0');
    PushChar1Bcc('4');
  }

  PushChar1Bcc('(');
  PushChar2Bcc(tiDig.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bYear);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQueryIO(2000, 4+16+1, 48);
}


void    QueryHeaderQ(void)
{
  HideCurrTime(1);

  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wBaseCurr;
  tiDig = HouIndexToDate(dw);


  szHi[10] = 'A' + ibMinor;


  ibMinorMax = 4;
  QueryHeaderQ_22();
}


void    ReadHeaderQ(void)
{
  InitPop(1);

  uchar i;
  for (i=0; i<48; i++)
  {
    mpflBuffCanHou[ibMinor][i] = PopDoubleQ()/2;
  }
}



void    MakeDataQ(uchar  ibHou)
{
  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<ibMinorMax; i++)
  {
    float fl = mpflBuffCanHou[i][ibHou];
    mpflEngFracDigCan[ibDig][i] += fl;

    uint w = (uint)(mpflEngFracDigCan[ibDig][i]*dbPulse);
    mpwChannels[i] = w;

    mpflEngFracDigCan[ibDig][i] -= (float)w/dbPulse;
  }

  wBaseCurr++;
}


bool    ReadDataQ(void)
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

  uchar i;
  for (i=j; i<48; i++)
  {
    ResetWatchdog();
    MakeDataQ(47-i);

    MakeSpecial(tiDig);
    if (MakeStopHou(0) == 0) return(0);


    ulong dw = DateToHouIndex(tiDigPrev);
    dw -= wBaseCurr;
    tiDig = HouIndexToDate(dw);


    iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;
  }

  return(1);
}



void    ReadCurrentQ(void)
{
  uchar i;
  for (i=0; i<MAX_LINE_Q; i++)
  {
    mpdwBaseDig[i] = mpdbChannelsC[i] * mpdbPulseHou[ibDig];
  }

  MakeCurrent();
}

#endif

