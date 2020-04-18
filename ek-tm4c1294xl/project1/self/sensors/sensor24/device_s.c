/*------------------------------------------------------------------------------
DEVICE_S!C

Энергомера СЕ102
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
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../digitals/current/current_run.h"
#include "../../digitals/limits.h"
#include "../../special/special.h"
#include "../../hardware/watchdog.h"
#include "automatic_s.h"
#include "device_s.h"



#ifndef SKIP_S

void    PushAddressS(void)
{
  PushIntLtl(mpdwAddress1[diCurr.bAddress-1] % 0x10000);
  PushIntLtl(wPrivate);

  PushLongLtl(mpdwAddress2[diCurr.bAddress-1]);
}



void    QueryTimeS(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD0);
  PushChar(0x01);
  PushChar(0x20);

  QueryS(100+18, 15);
}


time    ReadTimeS(void)
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

  QueryS(100+11, 22);
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

  QueryS(100+16, 15);
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

  QueryS(100+17, 15);
}


void    ReadVersionS(void)
{
  InitPop(9);

  Clear();
  sprintf(szLo+1, "версия %u.%u.%u", PopChar(), PopChar(), PopChar());
}



void    QueryEngDayS(uchar  bDay)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD1);
  PushChar(0x01);
  PushChar(0x2F);
  PushChar(bDay);

  QueryS(100+15, 16);
}


void    QueryEngMonS(uchar  bMonth)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD1);
  PushChar(0x01);
  PushChar(0x31);
  PushChar(bMonth);

  QueryS(100+15, 16);
}


void    ReadEnergyS(void)
{
  InitPop(9);

  coEnergy.mpbBuff[0] = PopChar();
  coEnergy.mpbBuff[1] = PopChar();
  coEnergy.mpbBuff[2] = PopChar();
  coEnergy.mpbBuff[3] = PopChar();

  mpdwChannelsA[0] = coEnergy.dwBuff;
  mpboChannelsA[0] = true;
}



void    InitHeaderS(void)
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


void    QueryHeaderS(void)
{
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wBaseCurr;
  tiDig = HouIndexToDate(dw);


  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD5);
  PushChar(0x01);
  PushChar(0x34);

  PushChar(ToBCD(tiDig.bDay));
  PushChar(ToBCD(tiDig.bMonth));
  PushChar(ToBCD(tiDig.bYear));
  PushChar(tiDig.bHour*2 + tiDig.bMinute/30);
  PushChar(4);

  QueryS(100+23, 20);
}


static bool ReadDataS(uchar  i)
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


bool    ReadHeaderS(void)
{
  uchar i;
  for (i=0; i<4; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);

    dw += 4-1;
    dw -= (wBaseCurr + i);

    tiDig = HouIndexToDate(dw);

    if (dw < dwValueS)
      if (ReadDataS(4-1-i) == 0) return(0);
  }

  wBaseCurr += 4;
  if (wBaseCurr > wHOURS) return(0);

  return(1);
}



void    ReadCurrentS(void)
{
  ReadEnergyS();
  mpdwBaseDig[0] = coEnergy.dwBuff*mpdbPulseMnt[ibDig]/wDividerS;

  MakeCurrent();
}

#endif

// device_24: чтение данных по сезонному времени
// поиск счетчиков
// признаки переполнения получасов - проверить изменение коэффициентов
// разрыв получасового опроса
