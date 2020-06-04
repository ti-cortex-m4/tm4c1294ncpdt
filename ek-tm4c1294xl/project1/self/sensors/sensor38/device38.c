/*------------------------------------------------------------------------------
device38.c

Ёнергомера CE318
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "io38.h"
#include "dff.h"
#include "device38.h"



#include "../../time/calendar.h"
#include "../../serial/monitor.h"



void    PushAddress38(void)
{
  PushLongLtl(mpdwAddress1[diCurr.bAddress-1]);
}


void    QueryTime38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x01);

  Query38(100+18, 14);
}


time    LongToTime38(ulong  dw)
{
  time ti = SecIndexToDate(dw);
  ti.bYear += 12;
  return ti;
}


time    ReadTime38(void)
{
//  uint w = DFF_Decoder(&mpbInBuff3[11], 0); // TODO
  uint64_t ddw = DffDecodePositive_(InBuffPtr(11)); // TODO

  ulong dw = ddw % 0x100000000;

//  MonitorIn();
//  InitPop(11);
//  ulong dw = PopLongLtl();

  return LongToTime38(dw);
}



void    QueryEngAbs38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

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

  Query38(250, 25);
}


uint64_t ReadEng38(uchar  ibInBuff)
{
  uint64_t ddw = DffDecodePositive_(InBuffPtr(ibInBuff)); // TODO

  ulong dw = ddw % 0x100000000;
  MonitorString("\n"); MonitorLongHex(dw);
  MonitorString("\n"); MonitorLongDec(dw);
  MonitorString("\n"); MonitorLongDecimal4(dw);

  return ddw;
}



// значени€ счетчиков на начало суток
void    QueryEngDay38(uchar  ibDayRel)
{
  MonitorString("\n ibDayRel="); MonitorCharDec(ibDayRel);

  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

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

  Query38(250, 33);
}



// значени€ счетчиков на начало мес€цев
void    QueryEngMon38(uchar  ibMonRel)
{
  MonitorString("\n ibMonRel="); MonitorCharDec(ibMonRel);

  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

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

  Query38(250, 33);
}
