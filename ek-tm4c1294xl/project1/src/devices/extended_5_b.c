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

void    QueryEnergyTariffB(uchar  bTime, uchar  bTariff)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(5);

  PushChar(bTime);
  PushChar(bTariff);

  QueryIO(1+16+2, 2+2+2);
}


bool    QueryEnergyTariffB_Full(uchar  bTime, uchar  bTariff)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyTariffB(bTime,bTariff);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadEnergyB();
  return(1);
}


bool    ReadCntAbsTariffB(uchar  bTariff)
{ 
uchar   i;
ulong   dw;

  Clear();
  if (ReadKoeffDeviceB_Special() == 0) return(0);


  if (QueryEnergyTariffB_Full(0x40,bTariff) == 0) return(0);  
  ShowPercent(60+bTariff);
  for (i=0; i<4; i++)
  {
    dw = mpdwChannelsA[i];
    mpdwChannelsB[i] = dw;
  }

  if (QueryEnergyTariffB_Full(0,bTariff) == 0) return(0);             
  ShowPercent(80+bTariff);
  for (i=0; i<4; i++)
  {
    dw  = mpdwChannelsA[i];
    dw -= mpdwChannelsB[i];

    mpdwChannelsB[i] = dw;
  }


  reBuffB = reBuffB/reBuffA;

  for (i=0; i<4; i++) 
  {
    if (mpdwChannelsB[i] > 0xF0000000)
      reBuffA = 0;
    else
      reBuffA = mpdwChannelsB[i] * reBuffB * 2;

    mpreChannelsB[i] = reBuffA;
    mpboChannelsA[i] = TRUE;     
  }

  return(1);
}

#endif

