/*------------------------------------------------------------------------------
EXTENDED_5_A.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../console.h"
#include "../sensors/automatic1.h"
#include "../sensors/device_a.h"
#include "../energy.h"
#include "../engine.h"
#include "extended_5_a.h"



void    QueryEnergyTariffA(uchar  bTime, uchar  bTrf)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(5);

  PushChar(bTime);
  PushChar(bTrf);

  QueryIO(1+16+2, 2+2+2);
}


bool    QueryEnergyTariffA_Full(uchar  bTime, uchar  bTrf)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyTariffA(bTime,bTrf);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == true) return false;
  }

  if (i == bMINORREPEATS) return false;

  ReadEnergyA();
  return true;
}


bool    ReadCntDayTariffA(uchar  bTrf)
{ 
uchar   i;
ulong   dw;

  Clear();
  if (ReadKoeffDeviceA() == 0) return false;


  if (QueryEnergyTariffA_Full(0x40,bTrf) == 0) return false;

  ShowPercent(60+bTrf);
  for (i=0; i<4; i++)
  {
    dw = mpdwChannelsA[i];
    mpdwChannelsB[i] = dw;
  }


  if (QueryEnergyTariffA_Full(0,bTrf) == 0) return false;

  ShowPercent(80+bTrf);
  for (i=0; i<4; i++)
  {
    dw  = mpdwChannelsA[i];
    dw -= mpdwChannelsB[i];

    mpdwChannelsB[i] = dw;
  }


  reKtrans = reKtrans/reBuffA;

  for (i=0; i<4; i++) 
  {
    if (mpdwChannelsB[i] > 0xF0000000)
      reBuffA = 0;
    else
      reBuffA = mpdwChannelsB[i] * reKtrans;

    mpreChannelsB[i] = reBuffA;
    mpboChannelsA[i] = TRUE;     
  }

  return true;
}

