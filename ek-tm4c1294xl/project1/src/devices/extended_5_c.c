/*------------------------------------------------------------------------------
EXTENDED_5_C.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../console.h"
#include "../sensors/automatic1.h"
#include "../sensors/device_c.h"
#include "../energy.h"
#include "../engine.h"
#include "extended_5_c.h"



#ifndef SKIP_C

static void QueryEnergyDayTariffC(uchar  bTrf)
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(3);
  PushChar(2);

  PushChar(0);
  PushChar(bTrf);
  PushChar(0);

  RevQueryIO(4+16+2, 3+3+2);
}


static void QueryEnergyAbsTariffC(uchar  bTrf)
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(3);
  PushChar(1);

  PushChar(0);
  PushChar(bTrf);
  PushChar(0);

  RevQueryIO(4+16+2, 3+3+2);
}


static bool QueryEnergyDayTariffC_Full(uchar  bTrf)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyDayTariffC(bTrf);

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadEnergyC();
  return(1);
}


static bool QueryEnergyAbsTariffC_Full(uchar  bTrf)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyAbsTariffC(bTrf);

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadEnergyC();
  return(1);
}


bool    ReadCntDayTariffC(uchar  bTrf)
{ 
uchar   i;
ulong   dw;

  Clear();
  if (ReadKoeffDeviceC() == 0) return(0);


  if (QueryEnergyDayTariffC_Full(bTrf) == 0) return(0);
  ShowPercent(60+bTrf);

  for (i=0; i<4; i++)
  {
    dw = mpdwChannelsA[i];
    mpdwChannelsB[i] = dw;
  }


  if (QueryEnergyAbsTariffC_Full(bTrf) == 0) return(0);
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
    reBuffA = mpdwChannelsB[i] * reKtrans;

    mpreChannelsB[i] = reBuffA;
    mpboChannelsA[i] = TRUE;     
  }

  return(1);
}

#endif
