/*------------------------------------------------------------------------------
DEVICE19.C

 ох-1.4
------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
//#include "../../memory/mem_factors.h"
//#include "../../memory/mem_realtime.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../digitals/current/current_run.h"
#include "device19.h"



#ifndef SKIP_N

void    QueryEnergyAbsN(void)
{
  InitPush(0);
  PushChar(0);   
  PushChar(diCurr.bAddress);

  PushChar(1);

  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  QueryIO(5+8, 5+8);
}



void    ReadEnergyN(void)
{
  InitPop(3);  

  coEnergy.mpbBuff[3] = PopChar();
  coEnergy.mpbBuff[2] = PopChar();
  coEnergy.mpbBuff[1] = PopChar();
  coEnergy.mpbBuff[0] = PopChar();

  mpdwChannelsA[0] = coEnergy.dwBuff;
  mpboChannelsA[0] = true;
}



void    ReadCurrentN(void)
{
  ReadEnergyN();
  mpdwBaseDig[0] = mpdwChannelsA[0];

  MakeCurrent();
}

#endif


