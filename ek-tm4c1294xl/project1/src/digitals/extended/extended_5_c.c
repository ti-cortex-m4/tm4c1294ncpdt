/*------------------------------------------------------------------------------
EXTENDED_5_C,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../console.h"
#include "../../sensors/automatic1.h"
#include "../../sensors/device_c.h"
#include "../../energy.h"
#include "extended_5_c.h"



#ifndef SKIP_C

static void QueryEngDayTariffC(uchar  bTrf)
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


static void QueryEngAbsTariffC(uchar  bTrf)
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


static bool QueryEngDayTariffC_Full(uchar  bTrf)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEngDayTariffC(bTrf);

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == true) return false;
  }

  if (i == bMINORREPEATS) return false;

  ReadEnergyC();
  return true;
}


static bool QueryEngAbsTariffC_Full(uchar  bTrf)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEngAbsTariffC(bTrf);

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


  if (QueryEngDayTariffC_Full(bTrf) == 0) return false; // энергия за текущие сутки
  ShowPercent(60+bTrf);

  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i];
  }


  if (QueryEngAbsTariffC_Full(bTrf) == 0) return false; // энергия всего
  ShowPercent(80+bTrf);

  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i] - mpdwChannelsB[i]; // энергия всего минус энергия за текущие сутки равно значению счетчика на начало текущих суток
    mpdbChannelsC[i] = mpdwChannelsB[i] * flK;
    mpboChannelsA[i] = TRUE;
  }

  return true;
}

#endif
