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
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_realtime.h"
#include "../../display/display.h"
//#include "../../keyboard/time/key_timedate.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
//#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../digitals/current/current_run.h"
//#include "../../digitals/limits.h"
//#include "../../special/special.h"
#include "../../hardware/watchdog.h"
#include "io35.h"
#include "device35.h"



#ifndef SKIP_35

static uint             wDivider35;



void    PushAddress35(void)
{
  PushIntLtl(22966 /*mpdwAddress1[diCurr.bAddress-1] % 0x10000*/);  // TODO 35
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
    case 0x00: wDivider35 = 1; break;
    case 0x01: wDivider35 = 10; break;
    case 0x02: wDivider35 = 100; break;
    default:   wDivider35 = 1000; break;
  }
}


uint    GetDivider35(void)
{
  return wDivider35;
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


void    ReadCurrent35(void)
{
  ReadEnergy35();
  mpdwBaseDig[0] = coEnergy.dwBuff*mpdbPulseMnt[ibDig]/GetDivider35();

  MakeCurrent();
}

#endif

// device_24: чтение данных по сезонному времени
// поиск счетчиков
// признаки переполнения получасов - проверить изменение коэффициентов
// разрыв получасового опроса
