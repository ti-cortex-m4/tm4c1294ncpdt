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
//#include "../serial/ports.h"
//#include "../serial/ports_devices.h"
//#include "../serial/monitor.h"
//#include "../display/display.h"
//#include "../keyboard/time/key_timedate.h"
//#include "../time/timedate.h"
//#include "../time/delay.h"
//#include "../devices/devices.h"
//#include "../devices/devices_time.h"
//#include "../digitals/current/current_run.h"
//#include "../digitals/limits.h"
//#include "../special/special.h"
#include "automatic_n31.h"
//#include "device_k.h"
#include "device_n31.h"



#ifndef SKIP_N31


void    QueryOpenN31(void)
{
//  QueryCloseG();
//  DelayOff();
//
//  memset(&mpbCoder, 0, sizeof(mpbCoder));
  InitPush();

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x03);

  Push(&mpdwAddress1[diCurr.bAddress-1], sizeof(ulong));
  Push(&mpdwAddress2[diCurr.bAddress-1], sizeof(ulong));

//  CodQueryIO(3+8+1, 3+8+1);
}


bool    ReadOpenN31(void)
{
//  InitPop(3);
//
//  bVersionCod = PopChar();
//
//  mpbCoder[0] = PopChar();
//  mpbCoder[1] = PopChar();
//  mpbCoder[2] = PopChar();
//  mpbCoder[3] = PopChar();
//
//  sprintf(szLo,"   версия: %2bu   ",bVersionCod);
//  DelayInf(); Clear();
//
//  if ((bVersionCod == 22) ||
//      (bVersionCod == 33) ||
//      (bVersionCod == 35) ||
//      (bVersionCod == 36) ||
//      (bVersionCod == 37) ||
//      (bVersionCod == 49)) return(1);
//
//  ShowLo(szNoVersion);
//  DelayInf(); Clear();

  return false;
}


#endif
