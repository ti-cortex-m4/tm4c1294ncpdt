/*------------------------------------------------------------------------------
extended_4t_34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_digitals.h"
//#include "../../console.h"
//#include "../../serial/ports_stack.h"
//#include "../../serial/ports_devices.h"
//#include "../../sensors/device_b.h"
//#include "../../sensors/automatic1.h"
//#include "../../digitals/max_repeats.h"
#include "extended_4t_34.h"



void    QueryEngMon34_(time  ti)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x67);
  PushChar(2);
  PushChar(0xFF);
  PushLongLtl(TimeToUnixTimeToGMT34(ti));

  QueryIO(3+81+2, 8+2);
}


double2 QueryEngMon34_Full_(time  ti, uchar  bPercent)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryEngMon34(ti);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == MaxRepeats()) return GetDouble2Error();
  ShowPercent(bPercent);

  ReadEng34();

  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_N34; i++)
  {
    mpdbChannelsC[i] = (double)mpddwChannels34[i] / 1000000;
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}


status ReadCntMonCanTariff34(uchar  ibCan, uchar  ibMon, uchar  ibTrf) // на начало мес€ца
{
  time2 ti2 = QueryTime34_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();

  if (QueryEngDates34_Full(60) == 0) return GetDouble2Error();

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
    return GetDouble2Error();
  } else {
    return QueryEngMon34_Full(ti, 80);
  }
}



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

/*
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
