/*------------------------------------------------------------------------------
DEVICE31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../display/display.h"
#include "../../time/timedate.h"
#include "../../time/delay.h"
#include "../../devices/devices.h"
#include "../../digitals/current/current_run.h"
#include "../../digitals/digitals_messages.h"
#include "automatic31.h"
#include "device31.h"



#ifndef SKIP_N31

static uchar            bVersionN31;



uchar   GetVersion31(void)
{
  return bVersionN31;
}


bool    ExtVersion31(void)
{
  return ((bVersionN31 == 36) ||
          (bVersionN31 == 37) ||
          (bVersionN31 == 49));
}



float   PopFloat31(void)
{
  static combo32 co;

  co.mpbBuff[0] = PopChar();
  co.mpbBuff[1] = PopChar();
  co.mpbBuff[2] = PopChar();
  co.mpbBuff[3] = PopChar();

  return co.flBuff;
}


double  PopDouble31(void)
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


void    QueryClose31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x02);

  Query31(0, 3+1);
}


void    QueryOpen31(void)
{
  QueryClose31();
  DelayOff();

  memset(&mpbCoder, 0, sizeof(mpbCoder));

  InitPush(0);

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x03);

  PushLongBig(mpdwAddress1[diCurr.bAddress-1]);
  PushLongBig(mpdwAddress2[diCurr.bAddress-1]);

  Query31(3+8+1, 3+8+1);
}


bool    ReadOpen31(void)
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



void    QueryTime31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x07);

  Query31(3+8+1, 3+1);
}


time    ReadTime31(void)
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


time    ReadPackTime31(void)
{
  InitPop(3);

  uchar d = PopChar();
  uchar c = PopChar();
  uchar b = PopChar();
  uchar a = PopChar();

  time ti;

  ti.bHour   = (c & 0xF8) >> 3;
  ti.bMinute = ((0x100*c+d) >> 5) & 0x3F;
  ti.bSecond = (d & 0x1F) << 1;

  ti.bDay    = (b & 0x1F);
  ti.bMonth  = ((0x100*a+b) >> 5) & 0x0F;
  ti.bYear   = (a & 0xFE) >> 1;

  return ti;
}


void    QueryControl31(time  ti)
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

  Query31(3+1, 3+8+1);
}



void    QueryTrans31(void)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "чтение данных по идентификатору"

  PushCharCod(0x03); // "коэффициенты трансформации"
  PushCharCod(0x00);
  PushCharCod(0x00);

  Query31(3+25+1, 3+3+1);
}



void    QueryEngAbs31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x12); // "чтение сумарных энергий"

  Query31(3+48+1, 3+1);
}


void    ReadEng31(void)
{
  InitPop(3);

  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    mpdbChannelsC[i] = PopDouble31() / 1000;
    mpboChannelsA[i] = true;
  }
}



void    ReadCurrent31(void)
{
  ReadEng31();

  double dbPulse = mpdbPulseMnt[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    mpdwBaseDig[i] = mpdbChannelsC[i] * dbPulse;
  }

  MakeCurrent();
}

#endif
