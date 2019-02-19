/*------------------------------------------------------------------------------
ENG_DAY34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
//#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "unix_time_gmt34.h"
#include "device34.h"
#include "eng_day34.h"



void    QueryEngDay34(time  ti)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x67);
  PushChar(1);
  PushChar(0xFF);
  PushLongLtl(TimeToUnixTimeToGMT34(ti));

  QueryIO(3+81+2, 8+2);
}


void    ReadEngDay34(void)
{
  InitPop(4);

  uchar i;
  for (i=0; i<MAX_LINE_N34; i++)
  {
    mpddwChannels34[i] = PopLongLtl();
    mpddwChannels34[i] += 0x100000000*PopLongLtl();
  }
}


double2 QueryEngDay34_Full(time  ti, uchar  bPercent)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryEngDay34(ti);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == MaxRepeats()) return GetDouble2Error();
  ShowPercent(bPercent);

  ReadEngDay34();

  return 1;
}
