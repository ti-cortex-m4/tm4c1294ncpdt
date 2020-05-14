/*------------------------------------------------------------------------------
push_dlms.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "push_dlms.h"



void    PushFormatDLMS(uint  wSize)
{
  PushIntBig(wSize | 0xA000);
}



void    PushTimeMonthDLMS(uchar  bMonth, uchar  bYear)
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



void    PushTimeDLMS(time  ti)
{
  uint wYear = 2000 + ti.bYear;
  PushChar(wYear / 0x100);
  PushChar(wYear % 0x100);
  PushChar(ti.bMonth);
  PushChar(ti.bDay);

  PushChar(0xFF);

  PushChar(ti.bHour);
  PushChar(ti.bMinute);
  PushChar(ti.bSecond);

  PushChar(0xFF);
  PushChar(0x80);
  PushChar(0x00);
  PushChar(0xFF);
}
