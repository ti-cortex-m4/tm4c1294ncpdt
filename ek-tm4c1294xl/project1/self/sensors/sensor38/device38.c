/*------------------------------------------------------------------------------
device38.c

���������� CE318
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


// �������� ��������� �� ������ �����
void    QueryEngDay38(uchar  ibDayRel, uchar  ibLine)
{
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



// �������� ��������� �� ������ �������
void    QueryEngMon38(uchar  ibMonRel, uchar  ibLine)
{
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



uint64_t ReadEngAbs38(uchar  ibInBuff)
{
//  uint w = DFF_Decoder(&mpbInBuff3[11], 0);
//
//  MonitorIn();
//  InitPop(11);
//  ulong dw = PopChar() + PopChar()*0x100 + PopChar()*0x10000;
//
//  MonitorIntHex(dw / 0x10000); MonitorIntHex(dw % 0x10000);
//  MonitorString(" ");
//  MonitorLongDec(dw);
//
//  mpbInBuff3[0] = 0xB2;
//  mpbInBuff3[1] = 0xAC;
//  mpbInBuff3[2] = 0x8D;
//  mpbInBuff3[3] = 0x03;
//
//  MonitorString("\n ");
//  MonitorCharHex(mpbInBuff3[0]);
//  MonitorCharHex(mpbInBuff3[1]);
//  MonitorCharHex(mpbInBuff3[2]);
//  MonitorCharHex(mpbInBuff3[3]);
//  uint w2 = DFF_Decoder(&mpbInBuff3[0], 0);
//  MonitorString(" -> ");
//  MonitorCharHex(mpbInBuff3[0]);
//  MonitorCharHex(mpbInBuff3[1]);
//  MonitorCharHex(mpbInBuff3[2]);
//  MonitorCharHex(mpbInBuff3[3]);
//
//  MonitorString("\n ");
////  uchar buff[4];
////  buff[0] = 0xB2;
////  buff[1] = 0xAC;
////  buff[2] = 0x8D;
////  buff[3] = 0x03;
  uint64_t ddw = DffDecodeLong64(&mpbInBuff3[ibInBuff]);

  ulong dw = ddw % 0x100000000;
  MonitorString("\n"); MonitorIntHex(dw / 0x10000); MonitorIntHex(dw % 0x10000);
  MonitorString("\n"); MonitorIntDec(dw1);

  return ddw;
}
