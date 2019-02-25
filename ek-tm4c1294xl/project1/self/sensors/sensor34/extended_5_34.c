/*------------------------------------------------------------------------------
extended_5_34.c


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
#include "monitor34.h"
#include "device34.h"
#include "extended_5_34.h"



void    QueryCntDayTariff34(time  tmDay, uchar  ibTrf) // на начало суток, индекс тарифа
{
  ASSERT(ibTrf < 4);

  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x67);
  PushChar(1);
  PushChar(ibTrf);
  PushLongLtl(TimeToUnixTimeToGMT34(tmDay));

  QueryIO(3+81+2, 8+2);
}


static status QueryCntDayTariff34_Full(time  tmDay, uchar  ibTrf) // на начало суток, индекс тарифа
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryCntDayTariff34(tmDay, ibTrf);

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


bool    ReadCntDayTariff34(uchar  ibCan, uchar  ibTrf) // на начало суток, индекс тарифа
{
  if (QueryEngDates34_Full(60+ibTrf*2) == 0) return false;

  time tm = tiCurr;
  tm.bSecond = 0;
  tm.bMinute = 0;
  tm.bHour   = 0;

#if MONITOR_34
  MonitorString("\n day begin date "); MonitorTime(tm);
#endif

  if (HasEngDay34(tm) == 0) {
    Clear();
    sprintf(szLo+1,"сутки %02u.%02u.%02u ?", tm.bDay,tm.bMonth,tm.bYear);
    Delay(1000);
    return ST_NOTPRESENTED;
  } else {
    return QueryCntDayTariff34_Full(tm, ibTrf);
  }
}
