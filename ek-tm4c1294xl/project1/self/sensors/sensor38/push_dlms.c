/*------------------------------------------------------------------------------
push_dlms.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
//#include "../../serial/ports2.h"
//#include "../../serial/ports_devices.h"
//#include "../../serial/monitor.h"
//#include "include36.h"
//#include "crc16_x25.h"
//#include "io36.h"
//#include "hdlc.h"
#include "push_dlms.h"



void    PushFormat(uint  wSize)
{
  PushIntBig(wSize | 0xA000);
}


void    PushMon36(uchar  bMonth, uchar  bYear)
{
  uint wYear = 2000 + bYear;
  PushChar(wYear / 0x100);
  PushChar(wYear % 0x100);
  PushChar(bMonth);
  PushChar(1);
  PushChar(0xFF);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0xFF);
  PushChar(0x80);
  PushChar(0x00);
  PushChar(0xFF);
}


void    PushTime36(time  ti)
{
  PushChar(0x07); // <!--2020-04-14 23:59:59-->
  PushChar(0xE4);
  PushChar(0x04);
  PushChar(0x0E);
  PushChar(0xFF);
  PushChar(0x17);
  PushChar(0x3B);
  PushChar(0x3B);
  PushChar(0xFF);
  PushChar(0x80);
  PushChar(0x00);
  PushChar(0xFF);
}
