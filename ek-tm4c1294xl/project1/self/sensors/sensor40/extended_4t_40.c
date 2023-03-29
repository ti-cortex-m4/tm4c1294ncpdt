/*------------------------------------------------------------------------------
extended_4t_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/rtc.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "../../devices/devices.h"
#include "../../digitals/max_repeats.h"
#include "dlms.h"
#include "dlms_obis.h"
#include "error40.h"
#include "io40.h"
#include "fragment_open_time_40.h"
#include "fragment_cntmon_40.h"
#include "extended_4t_40.h"



static status BadDigital(uchar  bError)
{
  Error40(bError);
  return ST_BADDIGITAL;
}



status  CntMonCanTariff40_Internal(uchar  ibMon, uchar  ibTrf)
{
  caller40 c = InitCaller40();
  
  time2 tm2 = FragmentOpenTime40(&c);
  if (!tm2.fValid) return BadDigital(90+0);
  time tm = tm2.tiValue;


  date dt;
  dt.bDay   = 1;
  dt.bMonth = ibMon + 1;
  dt.bYear  = (dt.bMonth > tm.bMonth) ? tm.bYear-1 : tm.bYear;


  double8 db8 = FragmentCntMonCan40(obisBillingPeriodMon, obisScalerForBillingPeriod, &c, dt);

  DISC();
  if (Input40() != SER_GOODCHECK) return BadDigital(90+1);


  if (db8.fValid)
  {
    uchar i;
    for (i=0; i<4; i++) {
      mpdbChannelsC[i] = 0;
    }

    mpdbChannelsC[0] = db8.mdbValue[1 + ibTrf];

    for (i=0; i<4; i++) {
      mpdbChannelsC[i] = mpdbChannelsC[i] * mpdbTransCnt[ibDig];
      mpboChannelsA[i] = true;
    }

    return ST_OK;
  }

  if (db8.bError == ERROR_NOT_PRESENTED) {
    return ST_NOTPRESENTED;
  }

  return BadDigital(90+2);
}



status  ReadCntMonCanTariff40(uchar  ibMonAbs, uchar  ibTrf) // на начало мес€ца
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    status s = CntMonCanTariff40_Internal(ibMonAbs, ibTrf);
    if (fKey == true) break;

    if (s == ST_OK) return s;
    if (s == ST_NOTPRESENTED) return s;
  }

  DISC();
  if (Input40() != SER_GOODCHECK) return BadDigital(90+3);

  return BadDigital(90+4);
}



#ifdef  MONITOR_40

double2 TestCntMonCanTariff40(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  uchar bMonth = (*GetCurrTimeDate()).bMonth;

  uchar m;
  for (m=0; m<10; m++)
  {
    uchar ibMonAbs = (12 + bMonth - 1 - m) % 12;
    
    uchar t;
    for (t=0; t<4; t++)
    {
      MonitorString("\n\n month="); MonitorCharDec(ibMonAbs+1);
      MonitorString(" tariff="); MonitorCharDec(t);
      status s = ReadCntMonCanTariff40(ibMonAbs, t);
      MonitorString("\n status="); MonitorCharDec(s);

      uchar i;
      for (i=0; i<4; i++)
      {
        MonitorString("\n mpdbChannelsC[");
        MonitorCharDec(i);
        MonitorString("]=");
        MonitorDouble6(mpdbChannelsC[i]);
      }
    }
  }

  return GetDouble0(0);
}

#endif
