/*------------------------------------------------------------------------------
dlms_push.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "dlms_obis.h"
#include "dlms_push.h"



void    PushFormatDLMS(uint  wSize)
{
  PushIntBig(wSize | 0xA000);
}



void    PushOBIS_DLMS(const obis_t  obis)
{
  uchar i;
  for (i=0; i<6; i++)
  {
    PushChar(obis[i]);
  }
}


void    PushTimeMonthYearDLMS(uchar  bMonth, uchar  bYear)
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


void    PushTimeDLMS(time  tm)
{
  uint wYear = 2000 + tm.bYear;
  PushChar(wYear / 0x100);
  PushChar(wYear % 0x100);
  PushChar(tm.bMonth);
  PushChar(tm.bDay);

  PushChar(0xFF);

  PushChar(tm.bHour);
  PushChar(tm.bMinute);
  PushChar(tm.bSecond);

  PushChar(0xFF);
  PushChar(0x80);
  PushChar(0x00);
  PushChar(0xFF);
}


void    PushDateDLMS(date  dt)
{
  uint wYear = 2000 + dt.bYear;
  PushChar(wYear / 0x100);
  PushChar(wYear % 0x100);
  PushChar(dt.bMonth);
  PushChar(dt.bDay);

  PushChar(0xFF);

  PushChar(dt.bHour);
  PushChar(dt.bMinute);
  PushChar(dt.bSecond);

  PushChar(0xFF);
  PushChar(0x80);
  PushChar(0x00);
  PushChar(0xFF);
}
