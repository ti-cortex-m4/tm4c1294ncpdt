/*------------------------------------------------------------------------------
DEVICE35!C

Энергомера СЕ102 NNCL2
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_ports.h"
//#include "../../memory/mem_current.h"
//#include "../../memory/mem_factors.h"
//#include "../../memory/mem_realtime.h"
//#include "../../memory/mem_energy_spec.h"
//#include "../../memory/mem_profile.h"
//#include "../../memory/mem_limits.h"
#include "../../display/display.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
//#include "../../digitals/current/current_run.h"
//#include "../../digitals/limits.h"
//#include "../../special/special.h"
#include "../../hardware/watchdog.h"
#include "automatic35.h"
#include "device35.h"



#ifndef SKIP_35

void    PushAddress35(void)
{
  PushIntLtl(mpdwAddress1[diCurr.bAddress-1] % 0x10000);
  PushIntLtl(wPrivate);

  PushLongLtl(mpdwAddress2[diCurr.bAddress-1]);
}



void    QueryTime35(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddress35();

  PushChar(0xD0);
  PushChar(0x01);
  PushChar(0x20);

  Query35(100+18, 15);
}


time    ReadTime35(void)
{
  InitPop(9);

  time ti;

  ti.bSecond = FromBCD(PopChar());
  ti.bMinute = FromBCD(PopChar());
  ti.bHour   = FromBCD(PopChar());

  PopChar();

  ti.bDay    = FromBCD(PopChar());
  ti.bMonth  = FromBCD(PopChar());
  ti.bYear   = FromBCD(PopChar());

  return ti;
}


/*
void    QueryControl35(time  ti)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddress35();

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

  Query35(100+11, 22);
}



void    QueryConfig35(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddress35();

  PushChar(0xD0);
  PushChar(0x01);
  PushChar(0x01);

  Query35(100+16, 15);
}


void    ReadConfig35(void)
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



void    QueryVersion35(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddress35();

  PushChar(0xD0);
  PushChar(0x01);
  PushChar(0x00);

  Query35(100+17, 15);
}


void    ReadVersion35(void)
{
  InitPop(9);

  Clear();
  sprintf(szLo+1, "версия %u.%u.%u", PopChar(), PopChar(), PopChar());
}



void    QueryEngDay35(uchar  bDay)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddress35();

  PushChar(0xD1);
  PushChar(0x01);
  PushChar(0x2F);
  PushChar(bDay);

  Query35(100+15, 16);
}


void    QueryEngMon35(uchar  bMonth)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddress35();

  PushChar(0xD1);
  PushChar(0x01);
  PushChar(0x31);
  PushChar(bMonth);

  Query35(100+15, 16);
}


void    ReadEnergy35(void)
{
  InitPop(9);

  coEnergy.mpbBuff[0] = PopChar();
  coEnergy.mpbBuff[1] = PopChar();
  coEnergy.mpbBuff[2] = PopChar();
  coEnergy.mpbBuff[3] = PopChar();

  mpdwChannelsA[0] = coEnergy.dwBuff;
  mpboChannelsA[0] = true;
}



void    InitHeader35(void)
{
  if (!UseBounds())
    wBaseCurr = 0;
  else
  {
    wBaseCurr = (mpcwStartRelCan[ibDig] / 6) * 6;
    Clear(); sprintf(szLo+1,"начало %04u:%02u",wBaseCurr,(uchar)(wBaseCurr/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;

  uchar i = tiDigPrev.bHour*2 + tiDigPrev.bMinute/30;
  i = (i / 4) * 4;

  tiDigPrev.bHour = i / 2;
  tiDigPrev.bMinute = (i % 2)*30;
}


void    QueryHeader35(void)
{
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wBaseCurr;
  tiDig = HouIndexToDate(dw);


  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddress35();

  PushChar(0xD5);
  PushChar(0x01);
  PushChar(0x34);

  PushChar(ToBCD(tiDig.bDay));
  PushChar(ToBCD(tiDig.bMonth));
  PushChar(ToBCD(tiDig.bYear));
  PushChar(tiDig.bHour*2 + tiDig.bMinute/30);
  PushChar(4);

  Query35(100+23, 20);
}


static bool ReadData35(uchar  i)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if (SearchDefHouIndex(tiDig) == 0) return(1);


  ShowProgressDigHou();

  InitPop(9+i*3);

  ulong dw = PopChar();
  dw += PopChar()*0x100;
  dw += PopChar()*0x10000;

  if (dw != 0xFFFFFF)
  {
    double dbPulse = mpdbPulseHou[ibDig];

    double db = (double)dw/wDividerS;
    mpdbEngFrac[ibDig] += db;

    uint w;
    if ((ulong)(mpdbEngFrac[ibDig]*dbPulse) < 0xFFFF)
    { w = (uint)(mpdbEngFrac[ibDig]*dbPulse); }
    else
    { w = 0xFFFF; mpcwOverflowHhr[ibDig]++; }

    mpwChannels[0] = w;
    mpdbEngFrac[ibDig] -= (double)w/dbPulse;

    MakeSpecial(tiDig);
    return(MakeStopHou(0));
  }
  else
  {
    szLo[15] = '*';
    return(MakeStopHou(0));
  }
}


bool    ReadHeader35(void)
{
  uchar i;
  for (i=0; i<4; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);

    dw += 4-1;
    dw -= (wBaseCurr + i);

    tiDig = HouIndexToDate(dw);

    if (dw < dwValueS)
      if (ReadData35(4-1-i) == 0) return(0);
  }

  wBaseCurr += 4;
  if (wBaseCurr > wHOURS) return(0);

  return(1);
}



void    ReadCurrent35(void)
{
  ReadEnergy35();
  mpdwBaseDig[0] = coEnergy.dwBuff*mpdbPulseMnt[ibDig]/wDividerS;

  MakeCurrent();
}
*/
#endif

// device_24: чтение данных по сезонному времени
// поиск счетчиков
// признаки переполнения получасов - проверить изменение коэффициентов
// разрыв получасового опроса
