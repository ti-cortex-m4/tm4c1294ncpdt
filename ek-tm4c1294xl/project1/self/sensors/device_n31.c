/*------------------------------------------------------------------------------
DEVICE_N31.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
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
#include "../digitals/digitals_messages.h"
//#include "../special/special.h"
#include "automatic_n31.h"
//#include "device_k.h"
#include "device_n31.h"



#ifndef SKIP_N31

uchar                   bVersionN31;



void    QueryCloseN31(void)
{
  InitPush(0);

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

  InitPush(0);

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x03);

  PushLongBig(mpdwAddress1[diCurr.bAddress-1]);
  PushLongBig(mpdwAddress2[diCurr.bAddress-1]);

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

  if (bVersionN31 == 49) return true;

  ShowLo(szNoVersion);
  DelayInf(); Clear();

  return false;
}



void    QueryTimeN31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x07);

  QueryN31(3+8+1, 3+1);
}


time    ReadTimeN31(void)
{
  time ti;

  InitPop(3);
               PopChar();
  ti.bDay    = PopChar();
  ti.bMonth  = PopChar();

  uint y = PopChar()*0x100 + PopChar();
  ti.bYear   = y % 100;

  ti.bHour   = PopChar();
  ti.bMinute = PopChar();
  ti.bSecond = PopChar();

  return ti;
}


#endif
