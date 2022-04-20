/*------------------------------------------------------------------------------
DEVICE19.C

 ох-1.4
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "device19.h"



#ifndef SKIP_N

void    QueryEnergyAbsN(void)
{
  InitPush();
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

  coEnergy.mpbBuff[0] = PopChar();
  coEnergy.mpbBuff[1] = PopChar();
  coEnergy.mpbBuff[2] = PopChar();
  coEnergy.mpbBuff[3] = PopChar();

  dwBuffC = coEnergy.dwBuff;
  SetCanLong(mpdwChannelsA, 0);

  mpboChannelsA[0] = boTrue;
}



void    ReadCurrentN(void)
{
  ReadEnergyN();

  dwBuffC = *PGetCanLong(mpdwChannelsA, 0);
  SetCanLong(mpdwBaseDig, 0);

  MakeCurrent();
}

#endif


