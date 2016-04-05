/*------------------------------------------------------------------------------
DEVICE33.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_realtime.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../display/display.h"
#include "../../time/timedate.h"
#include "../../time/delay.h"
#include "../../devices/devices.h"
#include "../../digitals/current/current_run.h"
#include "../../digitals/digitals_messages.h"
#include "../sensor31/automatic31.h"
#include "automatic33.h"
#include "device33.h"



#ifndef SKIP_33

static uchar            bVersion33;


/*
ulong   PopChar3Big33(void)
{
  return PopChar()*0x10000 + PopChar()*0x100 + PopChar();
}
*/


void    QueryClose33(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x02);

  Query33(0, 3+1);
}


void    QueryOpen33(void)
{
  QueryClose33();
  DelayOff();

  memset(&mpbCoder, 0, sizeof(mpbCoder));

  InitPush(0);

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x03);

  PushLongBig(mpdwAddress1[diCurr.bAddress-1]);
  PushLongBig(mpdwAddress2[diCurr.bAddress-1]);

  Query33(3+8+1, 3+8+1);
}


bool    ReadOpen33(void)
{
  InitPop(3);

  bVersion33 = PopChar();

  mpbCoder[0] = PopChar();
  mpbCoder[1] = PopChar();
  mpbCoder[2] = PopChar();
  mpbCoder[3] = PopChar();

  Clear(); sprintf(szLo+3,"версия: %2u",bVersion33);
  DelayInf(); Clear();

  if ((bVersion33 == 16) ||
      (bVersion33 == 18))
    return true;

  ShowLo(szNoVersion);
  DelayInf(); Clear();

  return false;
}


uchar   GetVersion33(void)
{
  return bVersion33;
}

/*
bool    OldVersion33(void)
{
  return false;
}
*/


void    QueryTime33(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x07);

  Query33(3+8+1, 3+1);
}


time    ReadTime33(void)
{
  InitPop(3);

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


time    ReadPackTime33(void)
{
  InitPop(3);

  uchar b = PopChar();
  uchar a = PopChar();

  time ti;

  ti.bHour   = (b >> 2) & 0x1F;
  ti.bMinute = (b & 0x03)*15;
  ti.bSecond = 0;

  ti.bDay    = ((0x100*a+b) >> 7) & 0x1F;
  ti.bMonth  = (a >> 4) & 0x0F;
  ti.bYear   = (ti.bMonth > tiCurr.bMonth) ? tiCurr.bYear-1 : tiCurr.bYear;

  return ti;
}


/*
void    QueryControl33(time  ti)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x08); // "запись времени и даты в счетчик"

  PushCharCod(ti.bSecond);
  PushCharCod(ti.bMinute);
  PushCharCod(ti.bHour);

  PushCharCod(GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay) + 1); // "день недели (1..7, 1-понедельник)"

  PushCharCod(ti.bDay);
  PushCharCod(ti.bMonth);

  PushCharCod(ti.bYear);
  PushCharCod(20);

  Query33(3+1, 3+8+1);
}
*/


void    QueryEngAbs33(uchar  ibTrf)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(0x04); // "потреблённая энергия по тарифам"
  PushCharCod(0x00);
  PushCharCod(ibTrf);

  Query33(3+14+1, 3+3+1);
}



bool    Checksum33(uchar  bSize)
{
  uint wCRC = MakeCrc16Bit32InBuff(3, bSize-2);
  return (wCRC == InBuff(3+bSize-2) + InBuff(3+bSize-1)*0x100);
}

#endif
