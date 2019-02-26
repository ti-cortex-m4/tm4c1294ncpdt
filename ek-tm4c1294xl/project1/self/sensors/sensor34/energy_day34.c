/*------------------------------------------------------------------------------
ENG_DAY34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "unix_time_gmt34.h"
#include "device34.h"
#include "energy_day34.h"



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

  ReadEngWithTrans34();

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}
