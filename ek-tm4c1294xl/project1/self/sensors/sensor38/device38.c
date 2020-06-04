/*------------------------------------------------------------------------------
device38.c

Энергомера CE318
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
  uint64_t ddw = DffDecodePositive(InBuffPtr(11)); // TODO

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
  uint64_t ddw = DffDecodePositive(InBuffPtr(ibInBuff)); // TODO

  ulong dw = ddw % 0x100000000;
  MonitorString("\n"); MonitorLongHex(dw);
  MonitorString("\n"); MonitorLongDec(dw);
  MonitorString("\n"); MonitorLongDecimal4(dw);

  return ddw;
}



// значения счетчиков на начало суток
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



// значения счетчиков на начало месяцев
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
  PushChar(0x00); // общая энергия
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


/*
счетчики на начало месяцев по тарифам
 Запрос
03.06.2020 22:29:44.414
06 E8 B7 C4 04 00 06
0B GET_DATA_MULTIPLE_EX
00
09 // A+
02
1E по 4 тарифам
01 месяц
02 месяц
BE A6

Ответ
03.06.2020 22:29:45.092
06 E8 B7 C4 04 80 06 0B 00 09
B8 D3 E5 02
98 CE 9F 01
A8 BE 48
00
A0 C7 8C 02
C8 D9 72 E0
9F 35
00
0A 92                                                                                                  ..?

 */
