/*------------------------------------------------------------------------------
DEVICE_W!C

Rovalant МЭС-3
------------------------------------------------------------------------------*/

#include "../main.h"
//#include "../memory/mem_settings.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_current.h"
#include "../memory/mem_factors.h"
//#include "../memory/mem_realtime.h"
//#include "../memory/mem_energy_spec.h"
//#include "../memory/mem_profile.h"
//#include "../memory/mem_limits.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
//#include "../serial/monitor.h"
#include "../display/display.h"
//#include "../keyboard/time/key_timedate.h"
//#include "../time/timedate.h"
//#include "../time/calendar.h"
#include "../time/delay.h"
#include "../devices/devices.h"
//#include "../devices/devices_time.h"
#include "../digitals/current/current_run.h"
//#include "../digitals/limits.h"
//#include "../special/special.h"
#include "automatic_w.h"
#include "device_k.h"
#include "device_w.h"



#ifndef SKIP_W

uchar                   ibLineW;

time                    tiProfileW;



double  PopDoubleW(void)
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
      if (bT == ')')
      {
        b = i-1;
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



void    QueryCloseW(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('B');
  PushChar1Bcc('0');
  PushChar1Bcc(0x03);

  QueryW(0, 0);
  DelayOff();
}



uchar   PushAddress1W(void)
{
  InitPush(0);
  PushChar1Bcc('/');
  PushChar1Bcc('?');

  uchar n = PushNumberBcc(mpdwAddress1[diCurr.bAddress-1]);

  PushChar1Bcc('!');
  return 2+n+1;
}


uchar   PushAddress2W(void)
{
  uchar n = PushAddress1W();

  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  return n+3;
}



void    QueryOpenW(void)
{
  QueryCloseW();

  uchar n = PushAddress1W();

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  Query(2000, n+2, 1);
}



void    QueryTypeW(void)
{
  PushAddress2W();

  PushStringBcc("0-0:");
  PushStringBcc("96.53.0");
  PushChar1Bcc(0x03);

  QueryW(1000, 1);
}


void    ReadTypeW(void)
{
  Clear();
  InitPop(1);

  bool f = false;

  uchar i = 0;
  while (true)
  {
    uchar b = PopChar0Bcc();

    if (b == ')') break;
    if (i >= 16) break;

    if (b == '\\') b = '/';
    if (f) szLo[i++] = b;

    if (b == '(') f = true;
  }
}


void    QueryTimeW_Profile(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushStringBcc("1-0:0.9.1");
  PushChar1Bcc(0x03);

  QueryW(1+28+2, 0);
}


void    QueryTimeW(void)
{
  uchar n = PushAddress2W();

  PushStringBcc("1-0:0.9.1");
  PushChar1Bcc(0x03);

  QueryW(1+28+2, 0);
}


time    ReadTimeW(void)
{
  InitPop(11);

  time ti;

  ti.bYear   = PopChar2Bcc(); PopChar();
  ti.bMonth  = PopChar2Bcc(); PopChar();
  ti.bDay    = PopChar2Bcc(); PopChar();
  ti.bHour   = PopChar2Bcc(); PopChar();
  ti.bMinute = PopChar2Bcc(); PopChar();
  ti.bSecond = PopChar2Bcc(); PopChar();

  return ti;
}


void    QueryControlW(time  ti)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('W');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushStringBcc("1-0:0.9.1");

  PushChar1Bcc('(');
  PushChar2Bcc(ti.bYear);
  PushChar1Bcc('-');
  PushChar2Bcc(ti.bMonth);
  PushChar1Bcc('-');
  PushChar2Bcc(ti.bDay);
  PushChar1Bcc(' ');
  PushChar2Bcc(ti.bHour);
  PushChar1Bcc(':');
  PushChar2Bcc(ti.bMinute);
  PushChar1Bcc(':');
  PushChar2Bcc(ti.bSecond);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  QueryW(1+1, 0);
}



void    QueryGetCorrectW(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushStringBcc("0-0:96.52.0");

  PushChar1Bcc(0x03);

  QueryW(1000, 1);
}


uint    ReadGetCorrectW(void)
{
  return PopDoubleW();
}


void    QuerySetCorrectW(sint  wSecond)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('W');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushStringBcc("0-0:96.51.0");
  PushChar1Bcc('(');
  if (wSecond < 0) PushChar1Bcc('-');
  PushNumberBcc(AbsInt(wSecond));
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  QueryW(1000, 1);
}


void    QueryOptionW(void)
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

  cbHeaderBcc = 1;
  cwInBuffBcc = 0;

  Query(1000, 4+2, 1);
}


void    QueryPasswordW(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('P');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);
  PushChar1Bcc('(');

  PushNumberBcc(mpdwAddress2[diCurr.bAddress-1]);

  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  QueryW(1+1, 0);
}



void    QueryKtransW(uchar  ibKtrans)
{
  ASSERT(ibKtrans < 2);

  PushAddress2W();

  PushStringBcc("0-0:");
  PushStringBcc("96.68.");
  PushChar1Bcc('0'+ibKtrans);
  PushChar1Bcc(0x03);

  QueryW(1000, 1);
}
//
//
//
//void    QueryVersionV(void)
//{
//  InitPush(2);
//
//  PushChar(0x20);
//  PushChar(0x00);
//
//  PushAddressV(0x30);
//
//  QueryV(100+42, 15);
//}
//
//
//bool    ReadVersionV(void)
//{
//  Clear();
//
//  uchar a = InBuff(9);
//  uchar b = InBuff(13);
//  sprintf(szLo+2, "версия %2X.%2X", a, b);
//
//  return ((b == 0x01) |
//          (b == 0x02) |
//          (b == 0x03) |
//          (b == 0x04) |
//          (b == 0x0C) |
//          (b == 0x0D) |
//          (b == 0x11) |
//          (b == 0x12));
//}


void    QueryEngAbsW_Current(uchar  ibLine)
{
  ASSERT(ibLine < 4);

  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushStringBcc("1-1:");
  PushChar1Bcc('1'+ibLine);
  PushStringBcc(".8.0");
  PushStringBcc("(1)");
  PushChar1Bcc(0x03);

  QueryW(1000, 2);
}


void    QueryEngAbsW(uchar  ibLine)
{
  ASSERT(ibLine < 4);

  PushAddress2W();

  PushStringBcc("1-1:");
  PushChar1Bcc('1'+ibLine);
  PushStringBcc(".8.0");
  PushStringBcc("(1)");
  PushChar1Bcc(0x03);

  QueryW(1000, 2);
}


void    QueryEngMonW(uchar  ibLine, uchar  bTime)
{
  ASSERT(ibLine < 4);

  PushAddress2W();

  PushStringBcc("1-1:");
  PushChar1Bcc('1'+ibLine);
  PushStringBcc(".129.0*");
  PushNumberBcc(bTime);
  PushStringBcc("(1)");
  PushChar1Bcc(0x03);

  QueryW(1000, 2);
}


void    QueryEngDayW(uchar  ibLine, uchar  bTime)
{
  ASSERT(ibLine < 4);

  PushAddress2W();

  PushStringBcc("1-1:");
  PushChar1Bcc('1'+ibLine);
  PushStringBcc(".128.0*");
  PushNumberBcc(bTime);
  PushStringBcc("(1)");
  PushChar1Bcc(0x03);

  QueryW(1000, 2);
}


//static void ReadEngV(uchar  ibPop)
//{
//  InitPop(ibPop);
//
//  mpdwChannelsA[0] = PopLongLtl();
//  mpboChannelsA[0] = true;
//
//  switch (PopChar() & 0x03)
//  {
//    case 0x00: wDividerV = 1; break;
//    case 0x01: wDividerV = 10; break;
//    case 0x02: wDividerV = 100; break;
//    default:   wDividerV = 1000; break;
//  }
//}


void    ReadEngW(uchar  ibLine)
{
  ASSERT(ibLine < 4);

  InitPop(1);
  mpdbChannelsC[ibLine] = PopDoubleW()/1000;
}



//void    InitHeaderV(void)
//{
//  if (!UseBounds())
//    wBaseCurr = 0;
//  else
//  {
//    wBaseCurr = (mpcwStartRelCan[ibDig] / 8) * 8;
//    sprintf(szLo," начало %04u:%02u ",wBaseCurr,(uchar)(wBaseCurr/48 + 1));
//    if (boShowMessages == true) DelayMsg();
//  }
//
//  tiCurrV = tiCurr;
//
//  uchar i = tiCurrV.bHour*2 + tiCurrV.bMinute/30;
//  i = (i / 8) * 8;
//
//  tiCurrV.bHour = i / 2;
//  tiCurrV.bMinute = (i % 2)*30;
//}
//
//
//void    QueryHeaderV(void)
//{
//  HideCurrTime(1);
//
//
//  ulong dw = DateToHouIndex(tiCurrV);
//  dw -= wBaseCurr;
//  time ti = HouIndexToDate(dw);
//
//  MonitorString("\n\n");
//  MonitorTime(tiCurrV); MonitorString("- ");
//  MonitorIntDec(wBaseCurr); MonitorString(" = ");
//  MonitorTime(ti);
//
//
//  InitPush(2);
//
//  PushChar(0x24);
//  PushChar(0x00);
//
//  PushAddressV(0x26);
//
//  PushChar(ti.bDay);
//  PushChar(ti.bMonth);
//  PushChar(ti.bYear);
//
//  uchar i = ti.bHour*2 + ti.bMinute/30;
//  i = i/8 + 1;
//  PushChar(i);
//
//  MonitorString("\n");
//  MonitorCharDec(ti.bDay); MonitorString(".");
//  MonitorCharDec(ti.bMonth); MonitorString(".");
//  MonitorCharDec(ti.bYear); MonitorString(" ");
//  MonitorCharDec(i);
//
//  QueryV(100+37, 19);
//}
//
//
//static bool ReadDataV(uchar  i, time  tiDig)
//{
//  MonitorString("\n"); MonitorTime(tiDig);
//
//  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);
//
//  if (SearchDefHouIndex(tiDig) == 0) return(1);
//
//
//  ShowProgressDigHou();
//
//  InitPop(19+i*2);
//  int w = PopIntLtl();
//
//  MonitorIntDec(w);
//  mpwChannels[0] = w;
//
//  MakeSpecial(tiDig);
//  return(MakeStopHou(0));
//}
//
//
//bool    ReadHeaderV(void)
//{
//  uchar i;
//  for (i=0; i<8; i++)
//  {
//    ulong dw = DateToHouIndex(tiCurrV);
//
//    dw += 8-1;
//    dw -= (wBaseCurr + i);
//
//    time ti = HouIndexToDate(dw);
//
//    if (dw < dwTimeV)
//      if (ReadDataV(8-1-i, ti) == 0) return(0);
//  }
//
//  wBaseCurr += 8;
//  if (wBaseCurr > wHOURS) return(0);
//
//  return(1);
//}



void    ReadCurrentW(void)
{
  uchar i;
  for (i=0; i<MAX_LINE_W; i++)
  {
    mpdwBaseDig[i] = mpdbChannelsC[i] * mpdbPulseMnt[ibDig];
  }

  MakeCurrent();
}

#endif
