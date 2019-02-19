/*------------------------------------------------------------------------------
ENG_DATES34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
//#include "../../memory/mem_current.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
//#include "../../hardware/beep.h"
#include "../../devices/devices.h"
//#include "../../display/display.h"
//#include "../../time/delay.h"
#include "unix_time_gmt34.h"
#include "eng_dates34.h"



static  time            mptiEngDay[10], mptiEngMon[10];
static  uchar             cbEngDay,   cbEngMon;



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
  cbEngDay = 0;

  uchar i;
  for (i=0; i<10; i++) {
    time ti = UnixTimeToTimeFromGMT34(PopLongLtl());
    if (ti.bYear > 0) {
      mptiEngDay[cbEngDay++] = ti;
    }
  }

  PopChar();
  PopChar();
  cbEngMon = 0;

  for (i=0; i<10; i++) {
    time ti = UnixTimeToTimeFromGMT34(PopLongLtl());
    if (ti.bYear > 0) {
      mptiEngMon[cbEngMon++] = ti;
    }
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
