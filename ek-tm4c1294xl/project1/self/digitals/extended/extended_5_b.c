/*------------------------------------------------------------------------------
EXTENDED_5_B,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../console.h"
#include "../../sensors/sensor1/automatic1.h"
#include "../../sensors/sensor2/device_b.h"
#include "../../energy.h"
#include "extended_5_b.h"



#ifndef SKIP_B

static void QueryEngTariffB(uchar  bTime, uchar  bTrf)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(5);

  PushChar(bTime);
  PushChar(bTrf);

  QueryIO(1+16+2, 2+2+2);
}


static bool QueryEngTariffB_Full(uchar  bTime, uchar  bTrf)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngTariffB(bTime,bTrf);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (i == MaxRepeats()) return false;

  ReadEnergyB();
  return true;
}


bool    ReadCntDayTariffB(uchar  ibCan, uchar  bTrf)
{
uchar   i;

  Clear();
  if (ReadKoeffDeviceB_Special(ibCan) == 0) return false;

  double dbK = dbKtrans/dbKpulse;


  if (QueryEngTariffB_Full(0x40,bTrf) == 0) return false; // энергия за текущие сутки
  ShowPercent(60+bTrf);

  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i];
  }


  if (QueryEngTariffB_Full(0,bTrf) == 0) return false; // энергия всего
  ShowPercent(80+bTrf);

  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i] - mpdwChannelsB[i]; // энергия всего минус энергия за текущие сутки равно значению счетчика на начало текущих суток
    mpdbChannelsC[i] = (mpdwChannelsB[i] > 0xF0000000 ? 0 : mpdwChannelsB[i]) * dbK * 2;
    mpboChannelsA[i] = true;
  }

  return true;
}

#endif

