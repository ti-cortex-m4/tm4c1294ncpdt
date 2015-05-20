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
    if (fKey == true) return false;
  }

  if (i == bMINORREPEATS) return false;

  ReadEnergyC();
  return true;
}


static bool QueryEnergyAbsTariffC_Full(uchar  bTrf)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyAbsTariffC(bTrf);

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == true) return false;
  }

  if (i == bMINORREPEATS) return false;

  ReadEnergyC();
  return true;
}


bool    ReadCntDayTariffC(uchar  bTrf)
{ 
uchar   i;

  Clear();
  if (ReadKoeffDeviceC() == 0) return false;

  float flK = reKtrans/reKpulse;


  if (QueryEnergyDayTariffC_Full(bTrf) == 0) return false; // энергия за текущие сутки
  ShowPercent(60+bTrf);

  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i];
  }


  if (QueryEnergyAbsTariffC_Full(bTrf) == 0) return false; // энергия всего
  ShowPercent(80+bTrf);

  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i] - mpdwChannelsB[i]; // энергия всего минус энергия за текущие сутки равно значение счетчика на начало текущих суток
  }


  for (i=0; i<4; i++) 
  {
  	mpdbChannelsC[i] = mpdwChannelsB[i] * flK;
    mpboChannelsA[i] = TRUE;
  }

  return true;
}

#endif
