/*------------------------------------------------------------------------------
extended_5_34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "device34.h"
#include "extended_5_34.h"



#ifndef SKIP_34

static void QueryEngDayTariff34(uchar  bTrf)
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


static void QueryEngAbsTariff34(uchar  bTrf)
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


static bool QueryEngDayTariff34_Full(uchar  bTrf)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngDayTariff34(bTrf);

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (i == MaxRepeats()) return false;

  ReadEnergyC();
  return true;
}


static bool QueryEngAbsTariff34_Full(uchar  bTrf)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngAbsTariff34(bTrf);

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (i == MaxRepeats()) return false;

  ReadEnergyC();
  return true;
}


bool    ReadCntDayTariff34(uchar  ibCan, uchar  bTrf)
{
uchar   i;

  Clear();
  if (ReadKoeffDeviceC(ibCan) == 0) return false;

  double dbK = dbKtrans/dbKpulse;


  if (QueryEngDayTariff34_Full(bTrf) == 0) return false; // энергия за текущие сутки
  ShowPercent(60+bTrf);

  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i];
  }


  if (QueryEngAbsTariff34_Full(bTrf) == 0) return false; // энергия всего
  ShowPercent(80+bTrf);

  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i] - mpdwChannelsB[i]; // энергия всего минус энергия за текущие сутки равно значению счетчика на начало текущих суток
    mpdbChannelsC[i] = mpdwChannelsB[i] * dbK;
    mpboChannelsA[i] = true;
  }

  return true;
}

#endif
