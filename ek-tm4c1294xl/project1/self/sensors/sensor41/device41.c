/*------------------------------------------------------------------------------
device41.c

Ёнергомера CE318S35M
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../time/calendar.h"
#include "../../devices/devices_init.h"
#include "io38.h"
#include "dff.h"
#include "device41.h"



void    PushAddress41(void)
{
  PushLongLtl(mpdwAddress1[diCurr.bAddress-1]);
}


/*
void    QueryEngAbs41(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress41();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0A); // GET_DATA_SINGLE_EX
  PushChar(0x00);

  PushChar(0x01); // A+
  PushChar(0x02);
  PushChar(0x00);

  PushChar(0x02); // A-
  PushChar(0x02);
  PushChar(0x00);

  PushChar(0x03); // R+
  PushChar(0x02);
  PushChar(0x00);

  PushChar(0x04); // R-
  PushChar(0x02);
  PushChar(0x00);

  Query41(250, 25);
}


// значени€ счетчиков на начало суток
void    QueryEngDay41(uchar  ibDayRel)
{
//  MonitorString("\n QueryEngDay38 "); MonitorCharDec(ibDayRel);

  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress41();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0B); // GET_DATA_MULTIPLE_EX
  PushChar(0x00);

  PushChar(0x01); // A+
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibDayRel);
  PushChar(ibDayRel);

  PushChar(0x02); // A-
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibDayRel);
  PushChar(ibDayRel);

  PushChar(0x03); // R+
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibDayRel);
  PushChar(ibDayRel);

  PushChar(0x04); // R-
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibDayRel);
  PushChar(ibDayRel);

  Query41(250, 33);
}


// значени€ счетчиков на начало мес€ца
void    QueryEngMon41(uchar  ibMonRel)
{
//  MonitorString("\n QueryEngMon38 "); MonitorCharDec(ibMonRel);

  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress41();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0B); // GET_DATA_MULTIPLE_EX
  PushChar(0x00);

  PushChar(0x09); // A+
  PushChar(0x02);
  PushChar(0x00); // обща€ энерги€
  PushChar(ibMonRel);
  PushChar(ibMonRel);

  PushChar(0x0A); // A-
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibMonRel);
  PushChar(ibMonRel);

  PushChar(0x0B); // R+
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibMonRel);
  PushChar(ibMonRel);

  PushChar(0x0C); // R-
  PushChar(0x02);
  PushChar(0x00);
  PushChar(ibMonRel);
  PushChar(ibMonRel);

  Query41(250, 33);
}



void    QueryNumber41(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress41();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(6);
  PushChar(0);
  PushChar(5);

  Query41(250, 14);
}


ulong   ReadNumber41(void)
{
  int64_t ddw = 0;
  DffDecodePositive(InBuffPtr(11), &ddw);
  return ddw % 0x100000000;
}



bool    GoodStatus41(uchar  bStatus)
{
  if (boIgnoreStatus38)
  {
    if (bStatus == 0)
      return true;
    else if (bStatus == 2)
      return true;
    else
      return false;
  }
  else
  {
    return bStatus == 0;
  }
}
*/
