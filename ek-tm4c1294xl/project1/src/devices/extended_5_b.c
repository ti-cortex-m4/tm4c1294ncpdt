/*------------------------------------------------------------------------------
EXTENDED_5_B.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../console.h"
#include "../sensors/automatic1.h"
#include "../sensors/device_b.h"
#include "../energy.h"
#include "../engine.h"
#include "extended_5_b.h"



#ifndef SKIP_B

void    QueryEnergyTariffB(uchar  bTime, uchar  bTrf)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(5);

  PushChar(bTime);
  PushChar(bTrf);

  QueryIO(1+16+2, 2+2+2);
}


bool    QueryEnergyTariffB_Full(uchar  bTime, uchar  bTrf)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyTariffB(bTime,bTrf);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadEnergyB();
  return(1);
}


bool    ReadCntAbsTariffB(uchar  bTrf)
{ 
uchar   i;
ulong   dw;

  Clear();
  if (ReadKoeffDeviceB_Special() == 0) return(0);

  float flK = reKtrans/reKpulse;


  if (QueryEnergyTariffB_Full(0x40,bTrf) == 0) return(0); // энергия за текущие сутки
  ShowPercent(60+bTrf);

  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i];
  }

  if (QueryEnergyTariffB_Full(0,bTrf) == 0) return(0); // энергия всего
  ShowPercent(80+bTrf);

  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i] - mpdwChannelsB[i]; // энергия всего минус энергия за текущие сутки равно значению счетчика на начало текущих суток
  }


  for (i=0; i<4; i++) 
  {
    if (mpdwChannelsB[i] > 0xF0000000)
      reBuffA = 0;
    else
      reBuffA = mpdwChannelsB[i] * flK * 2;

    mpreChannelsB[i] = reBuffA;
    mpboChannelsA[i] = TRUE;     
  }

  return(1);
}

#endif

