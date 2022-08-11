/*------------------------------------------------------------------------------
EXTENDED_5_A,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../console.h"
#include "../../sensors/automatic1.h"
#include "../../sensors/sensor1/device_a.h"
#include "../../energy.h"
#include "extended_5_a.h"



static void QueryEngTariffA(uchar  bTime, uchar  bTrf)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(5);

  PushChar(bTime);
  PushChar(bTrf);

  QueryIO(1+16+2, 2+2+2);
}


static bool QueryEngTariffA_Full(uchar  bTime, uchar  bTrf)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngTariffA(bTime,bTrf);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == true) return false;
  }

  if (i == MaxRepeats()) return false;

  ReadEnergyA();
  return true;
}


bool    ReadCntDayTariffA(uchar  bTrf)
{ 
uchar   i;

  Clear();
  if (ReadKoeffDeviceA() == 0) return false;

  double dbK = dbKtrans/dbKpulse;


  if (QueryEngTariffA_Full(0x40,bTrf) == 0) return false; // энергия за текущие сутки

  ShowPercent(60+bTrf);
  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i];
  }


  if (QueryEngTariffA_Full(0,bTrf) == 0) return false; // энергия всего

  ShowPercent(80+bTrf);
  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i] - mpdwChannelsB[i]; // энергия всего минус энергия за текущие сутки равно значению счетчика на начало текущих суток
    mpdbChannelsC[i] = (mpdwChannelsB[i] > 0xF0000000 ? 0 : mpdwChannelsB[i]) * dbK;
    mpboChannelsA[i] = true;     
  }

  return true;
}

