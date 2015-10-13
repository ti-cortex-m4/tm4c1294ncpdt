/*------------------------------------------------------------------------------
DEVICE_V!C

Счетчик МИРТЕК
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_digitals.h"
//#include "../memory/mem_ports.h"
#include "../memory/mem_current.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_limits.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../display/display.h"
#include "../keyboard/time/key_timedate.h"
//#include "../time/timedate.h"
#include "../time/calendar.h"
//#include "../time/delay.h"
//#include "../serial/ports_stack.h"
//#include "../serial/ports_devices.h"
//#include "../serial/ports_common.h"
#include "../devices/devices.h"
#include "../devices/devices_time.h"
#include "../digitals/current/current_run.h"
#include "../digitals/limits.h"
#include "../special/special.h"
//#include "../hardware/watchdog.h"
#include "automatic_v.h"
#include "device_v.h"



#ifndef SKIP_V

uint                    wDividerV;

ulong                   dwValueV;



void    PushAddressV(uchar  bCode)
{
  PushIntLtl(mpdwAddress1[diCurr.bAddress-1] % 0x10000);
  PushIntLtl(wPrivate);

  PushChar(bCode);

  PushLongLtl(mpdwAddress2[diCurr.bAddress-1]);
}



void    QueryTimeV(void)
{
  InitPush(2);

  PushChar(0x20);
  PushChar(0x00);

  PushAddressV(0x1C);

  QueryV(100+22, 15);
}


time    ReadTimeV(void)
{
  InitPop(13);

  time ti;

  ti.bSecond = PopChar();
  ti.bMinute = PopChar();
  ti.bHour   = PopChar();

  PopChar();

  ti.bDay    = PopChar();
  ti.bMonth  = PopChar();
  ti.bYear   = PopChar();

  return ti;
}


/*
void    QueryControlS(time  ti)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD7);
  PushChar(0x01);
  PushChar(0x21);

  PushChar(ToBCD(tiCurr.bSecond));
  PushChar(ToBCD(tiCurr.bMinute));
  PushChar(ToBCD(tiCurr.bHour));

  PushChar((GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay) + 1) % 7);

  PushChar(ToBCD(tiCurr.bDay));
  PushChar(ToBCD(tiCurr.bMonth));
  PushChar(ToBCD(tiCurr.bYear));

  QueryS_IO(100+11, 22);
}



void    QueryConfigS(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD0);
  PushChar(0x01);
  PushChar(0x01);

  QueryS_IO(100+16, 15);
}


void    ReadConfigS(void)
{
  InitPop(9);

  switch (PopChar() & 0x03)
  {
    case 0x00: wDividerS = 1; break;
    case 0x01: wDividerS = 10; break;
    case 0x02: wDividerS = 100; break;
    default:   wDividerS = 1000; break;
  }
}



void    QueryVersionS(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD0);
  PushChar(0x01);
  PushChar(0x00);

  QueryS_IO(100+17, 15);
}


void    ReadVersionS(void)
{
  InitPop(9);

  Clear();
  sprintf(szLo+1, "версия %u.%u.%u", PopChar(), PopChar(), PopChar());
}
*/


void    QueryEngAbsV(void)
{
  InitPush(2);

  PushChar(0x20);
  PushChar(0x00);

  PushAddressV(0x05);

  QueryV(100+41, 15);
}


void    QueryEngMonV(uchar  bMonth, uchar  bYear)
{
  InitPush(2);

  PushChar(0x22);
  PushChar(0x00);

  PushAddressV(0x24);

  PushChar(bMonth);
  PushChar(bYear);

  QueryV(100+39, 17);
}


void    QueryEngDayV(uchar  bDay, uchar  bMonth, uchar  bYear)
{
  InitPush(2);

  PushChar(0x23);
  PushChar(0x00);

  PushAddressV(0x25);

  PushChar(bDay);
  PushChar(bMonth);
  PushChar(bYear);

  QueryV(100+40, 18);
}


static void ReadEngV(uchar  ibPop)
{
  InitPop(ibPop);

  mpdwChannelsA[0] = PopLongLtl();
  mpboChannelsA[0] = true;

  switch (PopChar() & 0x03)
  {
    case 0x00: wDividerV = 1; break;
    case 0x01: wDividerV = 10; break;
    case 0x02: wDividerV = 100; break;
    default:   wDividerV = 1000; break;
  }
}


void    ReadEngAbsV(void)
{
  ReadEngV(13);
}


void    ReadEngMonV(void)
{
  ReadEngV(13+2);
}


void    ReadEngDayV(void)
{
  ReadEngV(13+3);
}



void    InitHeaderV(void)
{
//  if (!UseBounds())
    wBaseCurr = 0;
//  else
//  {
//    wBaseCurr = (mpcwStartRelCan[ibDig] / 6) * 6;
//    sprintf(szLo," начало %04u:%02u ",wBaseCurr,(uchar)(wBaseCurr/48 + 1));
//    if (boShowMessages == true) DelayMsg();
//  }

  tiDigPrev = tiCurr;

  uchar i = tiDigPrev.bHour*2 + tiDigPrev.bMinute/30;
  i = (i / 8) * 8;

  tiDigPrev.bHour = i / 2;
  tiDigPrev.bMinute = (i % 2)*30;
}


void    QueryHeaderV(void)
{
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wBaseCurr;
  tiDig = HouIndexToDate(dw);


  InitPush(2);

  PushChar(0x24);
  PushChar(0x00);

  PushAddressV(0x26);

  PushChar(tiDig.bDay);
  PushChar(tiDig.bMonth);
  PushChar(tiDig.bYear);

  uchar i = tiDig.bHour*2 + tiDig.bMinute/30;
  PushChar(i/8 + 1);

  QueryV(100+37, 19);
}


bool    ReadDataV(uchar  i)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if (SearchDefHouIndex(tiDig) == 0) return(1);


  ShowProgressDigHou();

  InitPop(17+i*2);
  mpwChannels[0] = PopIntLtl();

  MakeSpecial(tiDig);
  return(MakeStopHou(0));
}


bool    ReadHeaderV(void)
{
  uchar i;
  for (i=0; i<8; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);

    dw += 8-1;
    dw -= (wBaseCurr + i);

    tiDig = HouIndexToDate(dw);

    if (dw < dwValueV)
      if (ReadDataV(8-1-i) == 0) return(0);
  }

  wBaseCurr += 8;
  if (wBaseCurr > wHOURS) return(0);

  return(1);
}



void    ReadCurrentV(void)
{
  ReadEngAbsV();
  mpdwBaseDig[0] = mpdwChannelsA[0]*mpdbPulseMnt[ibDig]/wDividerV;

  MakeCurrent();
}

#endif
