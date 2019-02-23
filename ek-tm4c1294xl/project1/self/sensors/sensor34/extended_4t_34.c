/*------------------------------------------------------------------------------
extended_4t_34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "unix_time_gmt34.h"
#include "eng_dates34.h"
#include "device34.h"
#include "extended_4t_34.h"



void    QueryCntMonTariff34(time  tmMon, uchar  ibTrf) // на начало мес€ца
{
  ASSERT(ibTrf < 4);

  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x67);
  PushChar(2);
  PushChar(ibTrf);
  PushLongLtl(TimeToUnixTimeToGMT34(tmMon));

  QueryIO(3+81+2, 8+2);
}


static status QueryCntMonTariff34_Full(time  tmMon, uchar  ibTrf) // на начало мес€ца
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryCntMonTariff34(tmMon, ibTrf);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return ST_BADDIGITAL;
  }

  if (r == MaxRepeats()) return ST_BADDIGITAL;

  ReadEng34();

  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_N34; i++)
  {
    mpdbChannelsC[i] = (double)mpddwChannels34[i] / 1000000;
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return ST_OK;
}


status ReadCntMonCanTariff34(uchar  ibMon, uchar  ibTrf) // на начало мес€ца
{
  if (QueryEngDates34_Full(60+ibTrf) == 0) return ST_BADDIGITAL;

  time ti = ti2.tiValue;
  ti.bSecond = 0;
  ti.bMinute = 0;
  ti.bHour   = 0;
  ti.bDay    = 1;

  uchar m = (ibMon+1) % 12 + 1;
  ti.bYear   = (m > ti.bMonth) ? ti.bYear-1 : ti.bYear;
  ti.bMonth  = m;

  if (HasEngMon34(ti) == 0) {
    Clear();
    sprintf(szLo+1,"мес€ц %02u.%02u ?", ti.bMonth,ti.bYear);
    Delay(1000);
    return ST_NOTPRESENTED;
  } else {
    return QueryCntMonTariff34_Full(ti, ibTrf);
  }
}


/*
static void QueryCntMonTariff34(uchar  ibMon, uchar  bTrf) // на начало мес€ца
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x67);
  PushChar(2);
  PushChar(0xFF);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  QueryIO(3+81+2, 8+2);
}


static bool QueryCntMonTariff34_Full(uchar  ibMon, uchar  bTrf) // на начало мес€ца
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


status ReadCntMonCanTariff34(uchar  ibCan, uchar  ibMon, uchar  ibTrf) // на начало мес€ца
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
*/
