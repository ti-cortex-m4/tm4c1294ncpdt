/*------------------------------------------------------------------------------
DEVICE36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "device36.h"

#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"


void    Query36_Stop(void)
{
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

  Query(1000, 9, true);
}



void    Query36_Open1(void)
{
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



time    ReadTime36(void)
{
  time ti;

  ti.bSecond = 0;

  return ti;
}
