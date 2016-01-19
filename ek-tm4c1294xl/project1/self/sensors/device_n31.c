/*------------------------------------------------------------------------------
DEVICE_N31.C


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "../memory/mem_digitals.h"
//#include "../memory/mem_current.h"
//#include "../memory/mem_factors.h"
//#include "../memory/mem_realtime.h"
//#include "../memory/mem_energy_spec.h"
//#include "../memory/mem_profile.h"
//#include "../memory/mem_limits.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
//#include "../serial/monitor.h"
#include "../display/display.h"
//#include "../keyboard/time/key_timedate.h"
//#include "../time/timedate.h"
#include "../time/delay.h"
//#include "../devices/devices.h"
//#include "../devices/devices_time.h"
//#include "../digitals/current/current_run.h"
//#include "../digitals/limits.h"
//#include "../special/special.h"
#include "automatic_n31.h"
//#include "device_k.h"
#include "device_n31.h"



#ifndef SKIP_N31

uchar                   bVersionN31;



void    QueryCloseN31(void)
{
  InitPush();

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x02);

  QueryN31(0, 3+1);
}


void    QueryOpenN31(void)
{
  QueryCloseN31();
  DelayOff();

  memset(&mpbCoder, 0, sizeof(mpbCoder));

  InitPush();

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x03);

  PushLongLtl(mpdwAddress1[diCurr.bAddress-1]);
  PushLongLtl(mpdwAddress2[diCurr.bAddress-1]);

  QueryN31(3+8+1, 3+8+1);
}


bool    ReadOpenN31(void)
{
  InitPop(3);

  bVersionN31 = PopChar();

  mpbCoder[0] = PopChar();
  mpbCoder[1] = PopChar();
  mpbCoder[2] = PopChar();
  mpbCoder[3] = PopChar();

  Clear(); sprintf(szLo+3,"версия: %2u",bVersionN31);
  DelayInf(); Clear();

  if ((bVersionN31 == 22) ||
      (bVersionN31 == 33) ||
      (bVersionN31 == 35) ||
      (bVersionN31 == 36) ||
      (bVersionN31 == 37) ||
      (bVersionN31 == 49)) return true;

  ShowLo(szNoVersion);
  DelayInf(); Clear();

  return false;
}


#endif
