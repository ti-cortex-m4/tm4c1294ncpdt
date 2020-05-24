/*------------------------------------------------------------------------------
device38.c

Энергомера CE318
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "io38.h"
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

  PushChar(0x0A);
  PushChar(0x00);
  PushChar(0x01 + ibLine);

  PushChar(0x02);
  PushChar(0x00);

  Query38(100+17, 16);
}

uint64_t DecodeInt(uchar  *receive_buffer_position) {
  uint64_t result = 0;
  int num = 0;
  uint64_t ch;

  do {
    ch = ( * receive_buffer_position & 0x7F); // читаем очередные 7 бит
    result += ch << (num * 7); //добавляем к результату
    num++; // можно num+=7;, тогда вместо (num*7) везде просто num
  }
  while (( * (receive_buffer_position++) & 0x80)); //условие выхода нулевой флаг lbf

  if (ch >> 6) //если последний принятый бит был 1 заполняем старшие разряды единицами
    result |= 0xffffffffffffffff << (num * 7);

  return result;
}

ulong   ReadEngAbs38(void)
{
  uint w = DFF_Decoder(&mpbInBuff3[11], 0);

  MonitorIn();
  InitPop(11);
  ulong dw = PopChar() + PopChar()*0x100 + PopChar()*0x10000;

  MonitorIntHex(dw / 0x10000); MonitorIntHex(dw % 0x10000);
  MonitorString(" ");
  MonitorLongDec(dw);

  mpbInBuff3[0] = 0xB2;
  mpbInBuff3[1] = 0xAC;
  mpbInBuff3[2] = 0x8D;
  mpbInBuff3[3] = 0x03;

  MonitorString("\n ");
  MonitorCharHex(mpbInBuff3[0]);
  MonitorCharHex(mpbInBuff3[1]);
  MonitorCharHex(mpbInBuff3[2]);
  MonitorCharHex(mpbInBuff3[3]);
  uint w2 = DFF_Decoder(&mpbInBuff3[0], 0);
  MonitorString(" -> ");
  MonitorCharHex(mpbInBuff3[0]);
  MonitorCharHex(mpbInBuff3[1]);
  MonitorCharHex(mpbInBuff3[2]);
  MonitorCharHex(mpbInBuff3[3]);

  MonitorString("\n ");
  uchar buff[4];
  buff[0] = 0xB2;
  buff[1] = 0xAC;
  buff[2] = 0x8D;
  buff[3] = 0x03;
  uint64_t ddw = DecodeInt(buff);

  ulong dw1 = ddw / 0x100000000;
  ulong dw2 = ddw % 0x100000000;
  MonitorIntHex(dw1 / 0x10000); MonitorIntHex(dw1 % 0x10000);
  MonitorIntHex(dw2 / 0x10000); MonitorIntHex(dw2 % 0x10000);

  return dw;
}
