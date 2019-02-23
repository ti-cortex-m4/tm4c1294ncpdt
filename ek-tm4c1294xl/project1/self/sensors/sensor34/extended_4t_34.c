/*------------------------------------------------------------------------------
EXTENDED_4T_B,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../console.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../sensors/device_b.h"
#include "../../sensors/automatic1.h"
#include "../../digitals/max_repeats.h"
#include "extended_4t_b.h"



static void QueryCntMonTariffB(uchar  ibMon, uchar  bTrf) // на начало мес€ца
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(6);
  PushChar(2);

  uint w = 0x2BB + 0x55*ibMon + 0x11*bTrf;
  PushChar(w / 0x100);
  PushChar(w % 0x100);
  PushChar(16);

  QueryIO(1+16+2, 3+3+2);
}


static bool QueryCntMonTariffB_Full(uchar  ibMon, uchar  bTrf) // на начало мес€ца
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryCntMonTariffB(ibMon, bTrf);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (i == MaxRepeats()) return false;

  ReadEnergyB();
  return true;
}


status ReadCntMonCanTariffB(uchar  ibCan, uchar  ibMon, uchar  ibTrf) // на начало мес€ца
{
  Clear();
  if (ReadKoeffDeviceB(ibCan) == 0) return ST_BADDIGITAL;

  double dbK = dbKtrans/dbKpulse;


  if (QueryCntMonTariffB_Full(ibMon, ibTrf) == 0) return ST_BADDIGITAL;

  ShowPercent(60+ibTrf);


  uchar i;
  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] = mpdwChannelsA[i] * dbK;
    mpboChannelsA[i] = true;
  }

  return ST_OK;
}
