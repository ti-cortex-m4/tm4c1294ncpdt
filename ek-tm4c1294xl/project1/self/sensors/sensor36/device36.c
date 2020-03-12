/*------------------------------------------------------------------------------
DEVICE36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "device36.h"



#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"



void    Query36_Stop(void)
{
  MonitorString("\n\n Stop");

  InitPush(0);

  PushChar(0x7E);
  PushChar(0xA0);
  PushChar(0x07);
  PushChar(0x03);
  PushChar(0x03);
  PushChar(0x53);
  PushChar(0x80);
  PushChar(0xD7);
  PushChar(0x7E);

  uint w = MakeCRC16_X25OutBuff(1, 5); MonitorIntHex(w);

  Query(1000, 9, true);
}


void    Query36_Open1(void)
{
  MonitorString("\n\n Open 1");

  InitPush(0);

  PushChar(0x7E);
  PushChar(0xA0);
  PushChar(0x20);
  PushChar(0x03);
  PushChar(0x03);
  PushChar(0x93);
  PushChar(0xFE);
  PushChar(0xC9);
  PushChar(0x81);
  PushChar(0x80);
  PushChar(0x14);
  PushChar(0x05);
  PushChar(0x02);
  PushChar(0x00);
  PushChar(0x80);
  PushChar(0x06);
  PushChar(0x02);
  PushChar(0x00);
  PushChar(0x80);
  PushChar(0x07);
  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0x08);
  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0xCE);
  PushChar(0x6A);
  PushChar(0x7E);

  Query(1000, 34, true);
}


void    Query36_Open2(void)
{
  MonitorString("\n\n Open 2");

  InitPush(0);

  PushChar(0x7E);
  PushChar(0xA0);
  PushChar(0x44);
  PushChar(0x03);
  PushChar(0x03);
  PushChar(0x10);
  PushChar(0x65);
  PushChar(0x94);
  PushChar(0xE6);
  PushChar(0xE6);
  PushChar(0x00);
  PushChar(0x60);
  PushChar(0x36);
  PushChar(0xA1);
  PushChar(0x09);
  PushChar(0x06);
  PushChar(0x07);
  PushChar(0x60);
  PushChar(0x85);
  PushChar(0x74);
  PushChar(0x05);
  PushChar(0x08);
  PushChar(0x01);
  PushChar(0x01);
  PushChar(0x8A);
  PushChar(0x02);
  PushChar(0x07);
  PushChar(0x80);
  PushChar(0x8B);
  PushChar(0x07);
  PushChar(0x60);
  PushChar(0x85);
  PushChar(0x74);
  PushChar(0x05);
  PushChar(0x08);
  PushChar(0x02);
  PushChar(0x01);
  PushChar(0xAC);
  PushChar(0x0A);
  PushChar(0x80);
  PushChar(0x08);
  PushChar(0x78);
  PushChar(0x52);
  PushChar(0x77);
  PushChar(0x50);
  PushChar(0x62);
  PushChar(0x45);
  PushChar(0x78);
  PushChar(0x46);
  PushChar(0xBE);
  PushChar(0x10);
  PushChar(0x04);
  PushChar(0x0E);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x06);
  PushChar(0x5F);
  PushChar(0x1F);
  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x7E);
  PushChar(0x1F);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0xAF);
  PushChar(0xDF);
  PushChar(0x7E);

  Query(1000, 70, true);
}


void    Query36_Open3(void)
{
  MonitorString("\n\n Open 3");

  InitPush(0);

  PushChar(0x7E);
  PushChar(0xA0);
  PushChar(0x07);
  PushChar(0x03);
  PushChar(0x03);
  PushChar(0x31);
  PushChar(0x94);
  PushChar(0x97);
  PushChar(0x7E);

  Query(1000, 9, true);
}


void    Query36_Open4(void)
{
  MonitorString("\n\n Open 4");

  InitPush(0);

  PushChar(0x7E);
  PushChar(0xA0);
  PushChar(0x19);
  PushChar(0x03);
  PushChar(0x03);
  PushChar(0x32);
  PushChar(0xEC);
  PushChar(0xC8);
  PushChar(0xE6);
  PushChar(0xE6);
  PushChar(0x00);
  PushChar(0xC0);
  PushChar(0x01);
  PushChar(0x83);
  PushChar(0x00);
  PushChar(0x08);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0xFF);
  PushChar(0x02);
  PushChar(0x00);
  PushChar(0x47);
  PushChar(0x7C);
  PushChar(0x7E);

  Query(1000, 27, true);
}


void    Query36_Open5(void)
{
  MonitorString("\n\n Open 5");

  InitPush(0);

  PushChar(0x7E);
  PushChar(0xA0);
  PushChar(0x07);
  PushChar(0x03);
  PushChar(0x03);
  PushChar(0x51);
  PushChar(0x92);
  PushChar(0xF4);
  PushChar(0x7E);

  Query(1000, 9, true);
}


time    ReadTime36(void)
{
  InitPop(8 + 9);

  time ti;

  uint w = PopIntBig();
  ti.bYear   = w - 2000;
  ti.bMonth  = PopChar();
  ti.bDay    = PopChar();

  PopChar();

  ti.bHour   = PopChar();
  ti.bMinute = PopChar();
  ti.bSecond = PopChar();

  return ti;
}
