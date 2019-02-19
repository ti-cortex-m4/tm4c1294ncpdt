/*------------------------------------------------------------------------------
ENG_DATES34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "unix_time_gmt34.h"
#include "eng_dates34.h"



static  time            mptiEngDay[10], mptiEngMon[10];



void    QueryEngDates34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x64);
  PushChar(0x01);
  PushChar(0x86);
  PushChar(0x00);
  PushChar(0x3F);

  QueryIO(3+3*42+2, 6+2);
}


void    ReadEngDates34(void)
{
  memset(&mptiEngDay, 0, sizeof(mptiEngDay));
  memset(&mptiEngMon, 0, sizeof(mptiEngMon));

  InitPop(3);

  PopChar();
  PopChar();

  uchar i;
  for (i=0; i<10; i++) {
    mptiEngDay[i] = UnixTimeToTimeFromGMT34(PopLongLtl());
  }

  PopChar();
  PopChar();

  for (i=0; i<10; i++) {
    mptiEngMon[i] = UnixTimeToTimeFromGMT34(PopLongLtl());
  }
}


bool    QueryEngDates34_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryEngDates34();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return 0;
  }

  if (r == MaxRepeats()) return 0;
  ShowPercent(bPercent);

  ReadEngDates34();

  return 1;
}



bool    HasEngDay34(time  ti)
{
  uchar i;
  for (i=0; i<10; i++) {
    if (mptiEngMon[i] == ti)
      return 1;
  }
  return 0;
}
