/*------------------------------------------------------------------------------
extended_4t_34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
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
  ShowPercent(61+ibTrf*2);

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
  if (QueryEngDates34_Full(60+ibTrf*2) == 0) return ST_BADDIGITAL;

  time tm = tiCurr;
  tm.bSecond = 0;
  tm.bMinute = 0;
  tm.bHour   = 0;
  tm.bDay    = 1;

  uchar m = ibMon + 1;
  tm.bYear   = (m > tm.bMonth) ? tm.bYear-1 : tm.bYear;
  tm.bMonth  = m;

#if MONITOR_34
  MonitorString("\n month index "); MonitorCharDec(ibMon);
  MonitorString("\n month begin date "); MonitorTime(tm);
#endif

  if (HasEngMon34(tm) == 0) {
    Clear();
    sprintf(szLo+1,"мес€ц %02u.%02u ?", tm.bMonth,tm.bYear);
    Delay(1000);
    return ST_NOTPRESENTED;
  } else {
    return QueryCntMonTariff34_Full(tm, ibTrf);
  }
}
