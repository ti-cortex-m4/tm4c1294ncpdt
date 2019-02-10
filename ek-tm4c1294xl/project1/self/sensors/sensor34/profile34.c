/*------------------------------------------------------------------------------
PROFILE34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_factors.h"
//#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
//#include "../../serial/monitor.h"
//#include "../../display/display.h"
//#include "../../keyboard/time/key_timedate.h"
//#include "../../time/calendar.h"
//#include "../../time/delay.h"
//#include "../../time/timedate.h"
//#include "../../devices/devices.h"
#include "../../time/calendar.h"
#include "../../time/unix_time.h"
//#include "../sensor31/automatic31.h"
//#include "../sensor31/procedure31.h"
//#include "automatic33.h"
//#include "device33.h"
#include "profile34.h"



#ifndef SKIP_34

time                    tiProfile34;
uchar                   ibDay34;



void    QueryProfileOpen34(uchar  ibProfile)
{
  time ti1 = DayIndexToDate(DateToDayIndex(tiProfile34)/* - ibDay34*/);
//  time ti2 = DayIndexToDate(DateToDayIndex(ti1)         + 1);

  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x6B);
  PushChar(0);
  PushChar(ibProfile);
  PushLongLE(TimeToUnixTime(ti1));
  PushLongLE(TimeToUnixTime(ti2));

  QueryIO(3+18+2, 6+2);
}


/*
void    QueryRead34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x64);
  PushChar(0x00);
  PushChar(0x46);
  PushChar(0x00);
  PushChar(0x09);

  QueryIO(3+18+2, 6+2);
}


void    QueryClose34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x64);
  PushChar(0x00);
  PushChar(0x46);
  PushChar(0x00);
  PushChar(0x09);

  QueryIO(3+18+2, 6+2);
}
*/
#endif
