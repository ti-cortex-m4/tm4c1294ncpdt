/*------------------------------------------------------------------------------
DEVICE31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
//#include "../memory/mem_realtime.h"
//#include "../memory/mem_energy_spec.h"
//#include "../memory/mem_profile.h"
//#include "../memory/mem_limits.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
//#include "../serial/monitor.h"
#include "../../display/display.h"
//#include "../keyboard/time/key_timedate.h"
#include "../../time/timedate.h"
#include "../../time/delay.h"
#include "../../devices/devices.h"
//#include "../devices/devices_time.h"
#include "../../digitals/current/current_run.h"
//#include "../digitals/limits.h"
#include "../../digitals/digitals_messages.h"
//#include "../special/special.h"
#include "automatic31.h"
#include "device31.h"



#ifndef SKIP_N31

uchar                   bVersionN31;



double  PopDoubleN31(void)
{
  static combo64 co;

  co.mpbBuff[0] = PopChar();
  co.mpbBuff[1] = PopChar();
  co.mpbBuff[2] = PopChar();
  co.mpbBuff[3] = PopChar();
  co.mpbBuff[4] = PopChar();
  co.mpbBuff[5] = PopChar();
  co.mpbBuff[6] = PopChar();
  co.mpbBuff[7] = PopChar();

  return co.dbBuff;
}



void    QueryCloseN31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x02);

  QueryN31(0, 3+1);
}


void    QueryOpenN31(void)
{
  QueryCloseN31();
  DelayOff();

  memset(&mpbCoder, 0, sizeof(mpbCoder));

  InitPush(0);

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x03);

  PushLongBig(mpdwAddress1[diCurr.bAddress-1]);
  PushLongBig(mpdwAddress2[diCurr.bAddress-1]);

  QueryN31(3+8+1, 3+8+1);
}


bool    ReadOpenN31(void)
{
  InitPop(3);

  bVersionN31 = PopChar();

  mpbCoder[0] = PopChar();
  mpbCoder[1] = PopChar();
  mpbCoder[2] = PopChar();
  mpbCoder[3] = PopChar();

  Clear(); sprintf(szLo+3,"версия: %2u",bVersionN31);
  DelayInf(); Clear();

  if (bVersionN31 == 49) return true;

  ShowLo(szNoVersion);
  DelayInf(); Clear();

  return false;
}



void    QueryTimeN31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x07);

  QueryN31(3+8+1, 3+1);
}


time    ReadTimeN31(void)
{
  time ti;

  InitPop(3+1);

  ti.bDay    = PopChar();
  ti.bMonth  = PopChar();
  ti.bYear   = PopIntLtl() % 100;

  ti.bHour   = PopChar();
  ti.bMinute = PopChar();
  ti.bSecond = PopChar();

  return ti;
}


void    QueryControlN31(time  ti)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x08); // "запись времени и даты в счетчик"

  PushCharCod(GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay)); // "день недели (0..6, 0-понедельник)"

  PushCharCod(ti.bDay);
  PushCharCod(ti.bMonth);

  PushCharCod((2000 + ti.bYear) % 0x100);
  PushCharCod((2000 + ti.bYear) / 0x100);

  PushCharCod(ti.bHour);
  PushCharCod(ti.bMinute);
  PushCharCod(ti.bSecond);

  QueryN31(3+1, 3+8+1);
}



void    QueryTransN31(void)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "чтение данных по идентификатору"

  PushCharCod(0x03); // "коэффициенты трансформации"
  PushCharCod(0x00);
  PushCharCod(0x00);

  QueryN31(3+25+1, 3+3+1);
}



void    QueryEngAbsN31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x12); // "чтение сумарных энергий"

  QueryN31(3+48+1, 3+1);
}


void    ReadEngN31(void)
{
  InitPop(3);

  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    mpdbChannelsC[i] = PopDoubleN31() / 1000;
    mpboChannelsA[i] = true;
  }
}



void    ReadCurrentN31(void)
{
  ReadEngN31();

  double dbPulse = mpdbPulseMnt[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    mpdwBaseDig[i] = mpdbChannelsC[i] * dbPulse;
  }

  MakeCurrent();
}

#endif
