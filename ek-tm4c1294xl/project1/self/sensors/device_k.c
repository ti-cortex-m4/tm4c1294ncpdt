/*------------------------------------------------------------------------------
DEVICE_K!C

Энергомера ЦЭ6850М
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_settings.h"
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
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../time/delay.h"
#include "device_k.h"



#ifndef SKIP_K

double  PopDoubleK(void)
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

      if (bT == ')')
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

  return -1;
}



uchar   PushAddress1Bcc(void)
{
  InitPush(0);
  PushChar1Bcc('/');
  PushChar1Bcc('?');

  uchar n = PushNumberBcc(mpdwAddress1[diCurr.bAddress-1]);

  PushChar1Bcc('!');
  return 2+n+1;
}


uchar   PushAddress2Bcc(void)
{
  uchar n = PushAddress1Bcc();

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  return n+4;
}



void    PushLineBcc(uchar  ibLine)
{
  switch (ibLine)
  {
    case 0: PushChar1Bcc('P'); PushChar1Bcc('E'); break;
    case 1: PushChar1Bcc('P'); PushChar1Bcc('I'); break;
    case 2: PushChar1Bcc('Q'); PushChar1Bcc('E'); break;
    case 3: PushChar1Bcc('Q'); PushChar1Bcc('I'); break;
    default: ASSERT(false);
  }
}



void    QueryCloseK(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('B');
  PushChar1Bcc('0');
  PushChar1Bcc(0x03);

  BccQueryIO(0, 4+1, 0);
  DelayOff();
}


void    QueryOpenK(void)
{
  QueryCloseK();

  uchar n = PushAddress1Bcc();

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  Query(2000, n+2, 1);
}


void    ReadOpenK(void)
{
  Clear();
  InitPop(1);

  uchar i;
  for (i=0; i<16; i++)
  {
    uchar b = PopChar0Bcc();

    if ((b == '\r') || (b == '\n')) break;
    szLo[i] = b;
  }
}



void    QueryEnergySpecK(uchar  ibLine)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('E');
  PushChar1Bcc('T');
  PushChar1Bcc('0');

  PushLineBcc(ibLine);

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+6*28+2, 4+8+1, 6);
}


void    QueryEnergyAbsK(uchar  ibLine)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('T');
  PushChar1Bcc('0');

  PushLineBcc(ibLine);

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+6*28+2, n+8+1, 6);
}


void    ReadEnergyK(uchar  ibLine)
{
  InitPop(1);

  mpdbChannelsC[ibLine] = PopDoubleK();
  mpboChannelsA[ibLine] = true;
}



void    QueryOptionK(void)
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

  Query(1+13+2, 4+2, 1);
}


bool    HasPasswordK(void)
{
  return mpdwAddress2[diCurr.bAddress-1] != MAX_LONG;
}


void    QueryPasswordK(void)
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

  BccQueryIO(1+1, 5+n+2+1, 0);
}



void    QueryTimeK(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');
  PushChar1Bcc('_');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+17+2, n+8+1, 0);
}


void    QueryTimeSpecK(void)
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

  BccQueryIO(1+17+2, 4+8+1, 0);
}


time    ReadTimeK(void)
{
  InitPop(7);

  time ti;
  ti.bHour   = PopChar2Bcc(); PopChar();
  ti.bMinute = PopChar2Bcc(); PopChar();
  ti.bSecond = PopChar2Bcc(); PopChar();

  return ti;
}



void    QueryDateK(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('D');
  PushChar1Bcc('A');
  PushChar1Bcc('T');
  PushChar1Bcc('E');
  PushChar1Bcc('_');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+20+2, n+8+1, 0);
}


void    QueryDateSpecK(void)
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

  BccQueryIO(1+20+2, 4+8+1, 0);
}


time    ReadDateK(time  ti)
{
  InitPop(7+3);

  ti.bDay   = PopChar2Bcc(); PopChar();
  ti.bMonth = PopChar2Bcc(); PopChar();
  ti.bYear  = PopChar2Bcc(); PopChar();

  return ti;
}



void    QueryCorrectK(void)
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

  Query(1000, 2+6+2, 1);
}


void    QueryControlK(void)
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

  BccQueryIO(1+1, 4+16+1, 0);
}



void    QueryHeaderK_13(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('G');
  PushChar1Bcc('R');
  PushChar1Bcc('A');

  PushLineBcc(ibMinor);

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


void    QueryHeaderK_14(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('G');
  PushChar1Bcc('R');
  PushChar1Bcc('A');

  PushLineBcc(ibMinor);

  PushChar1Bcc('(');
  PushChar2Bcc(tiDig.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bMonth);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQueryIO(2000, 4+13+1, 48);
}



void    QueryHeaderK(void)
{
  HideCurrTime(1);

  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wBaseCurr;
  tiDig = HouIndexToDate(dw);


  szHi[10] = 'A' + ibMinor;


  if (diCurr.bDevice == 14)
    ibMinorMax = 1;
  else
    ibMinorMax = 4;

  if (diCurr.bDevice == 14)
    QueryHeaderK_14();
  else
    QueryHeaderK_13();
}


void    ReadHeaderK(uchar  ibLine)
{
  InitPop(1);

  uchar h;
  for (h=0; h<48; h++)
  {
    mpflBuffCanHou[ibLine][h] = PopDoubleK()/2;
  }
}



void    MakeDataK(uchar  ibHou)
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


bool    ReadDataK(void)
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

  uchar h;
  for (h=j; h<48; h++)
  {
    ResetWatchdog();
    MakeDataK(47-h);

    MakeSpecial(tiDig);
    if (MakeStopHou(0) == 0) return(0);


    ulong dw = DateToHouIndex(tiDigPrev);
    dw -= wBaseCurr;
    tiDig = HouIndexToDate(dw);


    iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;
  }

  return(1);
}



void    ReadCurrentK(uchar  bMaxLine)
{
  uchar i;
  for (i=0; i<bMaxLine; i++)
  {
    mpdwBaseDig[i] = mpdbChannelsC[i] * mpdbPulseMnt[ibDig];
  }

  MakeCurrent();
}

#endif
