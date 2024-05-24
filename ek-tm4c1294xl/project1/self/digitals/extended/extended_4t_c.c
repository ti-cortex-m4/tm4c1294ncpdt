/*------------------------------------------------------------------------------
EXTENDED_4T_C!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../console.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../sensors/sensor3/device_c.h"
#include "../../time/timedate.h"
#include "../../sensors/automatic1.h"
#include "../../sensors/sensor3/automatic_c.h"
#include "../../digitals/max_repeats.h"
#include "extended_4t_c.h"



#ifndef SKIP_C

static void QueryCntMonTariffC(uchar  ibMon, uchar  bTrf) // на начало мес€ца
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);
  PushChar(43);

  PushChar(ibMon);
  PushChar(bTrf);
  PushChar(0);

  RevQueryIO(4+16+2, 3+3+2);
}


static bool QueryCntMonTariffC_Full(uchar  ibMon, uchar  bTrf) // на начало мес€ца
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();

    if (bTrf == 1) {
        MonitorString("\n # ibMon="); MonitorCharHex(ibMon);
    }

    QueryCntMonTariffC(ibMon, bTrf);

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (i == MaxRepeats()) return false;

  ReadEnergyC();
  return true;
}


status ReadCntMonCanTariffC(uchar  ibCan, uchar  ibMon, uchar  ibTrf) // на начало мес€ца
{
  Clear();
  if (ReadKoeffDeviceC(ibCan) == 0) return ST_BADDIGITAL;

  double dbK = dbKtrans/dbKpulse;


  time2 ti2 = QueryTimeC_Full();
  if (ti2.fValid == false) return ST_BADDIGITAL;

  uchar m = (ibMon + 0)%12;

  if (ibTrf == 0) {
      MonitorString("\n * ibMon="); MonitorCharHex(ibMon);
      MonitorString("\n * m="); MonitorCharHex(m);
      MonitorString("\n * bMonth="); MonitorCharHex(ti2.tiValue.bMonth);
  }

  if (QueryCntMonTariffC_Full(-((12-1+ti2.tiValue.bMonth-m)%12), ibTrf+1) == 0) return ST_BADDIGITAL;

  ShowPercent(60+ibTrf);


  uchar i;
  for (i=0; i<4; i++)
  {
  	mpdbChannelsC[i] = mpdwChannelsA[i] * dbK;
    mpboChannelsA[i] = true;
  }

  return ST_OK;
}

#endif
