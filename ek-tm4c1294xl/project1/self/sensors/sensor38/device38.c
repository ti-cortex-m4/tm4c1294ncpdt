/*------------------------------------------------------------------------------
device38.c

Ёнергомера CE318
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "io38.h"
#include "dff.h"
#include "device38.h"



#include "../../time/calendar.h"
#include "../../serial/monitor.h"
#include "../../memory/mem_serial3.h"
uint DFF_Decoder(uchar  *pbData, uchar bS);



void    PushAddress38(void)
{
  PushChar(0xE8);
  PushChar(0xB7);
  PushChar(0xC4);
  PushChar(0x04);

//  PushLongLtl(80001000); // TODO
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


time    ReadTime38(void)
{
  uint w = DFF_Decoder(&mpbInBuff3[11], 0);

  MonitorIn();
  InitPop(11);
  ulong dw = PopLongLtl();

  time ti = SecIndexToDate(dw);
  ti.bYear += 12;

  return ti;
}



void    QueryEngAbs38(uchar  ibLine)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0A); // GET_DATA_SINGLE_EX
  PushChar(0x00);
  PushChar(0x01 + ibLine); // A+, A-, R+, R-

  PushChar(0x02);
  PushChar(0x00);

  Query38(100+17, 16);
}


uint64_t ReadEng38(uchar  ibInBuff)
{
  uint64_t ddw = DffDecodeLong64(&mpbInBuff3[ibInBuff]); // TODO

  ulong dw = ddw % 0x100000000;
  MonitorString("\n"); MonitorLongHex(dw);
  MonitorString("\n"); MonitorLongDec(dw);
  MonitorString("\n"); MonitorLongDecimal(dw, 10000);

  return ddw;
}



// значени€ счетчиков на начало суток
void    QueryEngDay38(uchar  ibDayRel, uchar  ibLine)
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
  PushChar(0x01 + ibLine); // A+, A-, R+, R-

  PushChar(0x02);
  PushChar(0x00);

  PushChar(ibDayRel);
  PushChar(ibDayRel);

  Query38(100+17, 18);
}



// значени€ счетчиков на начало мес€цев
void    QueryEngMon38(uchar  ibMonRel, uchar  ibLine)
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
  PushChar(0x09 + ibLine); // A+, A-, R+, R-

  PushChar(0x02);
  PushChar(0x00);

  PushChar(ibMonRel);
  PushChar(ibMonRel);

  Query38(100+17, 18);
}



uint64_t ReadEngStatus38(uchar  ibInBuff)
{
  uint64_t ddw = DffDecodeLong64(&mpbInBuff3[ibInBuff]);  // TODO

  ulong dw = ddw % 0x100000000;
  MonitorString("\n"); MonitorLongHex(dw);

  uchar bStatus = (ddw % 0x100) & 0x03;
  MonitorString("\n status="); MonitorCharDec(bStatus);

  dw >>= 3;
  MonitorString("\n"); MonitorLongDec(dw);
  MonitorString("\n"); MonitorLongDecimal(dw, 10000);

  return ddw;
}
