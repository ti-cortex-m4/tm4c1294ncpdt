/*------------------------------------------------------------------------------
extended_4t_39.c


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
#include "error39.h"
#include "io39.h"
#include "fragment_open_time_39.h"
#include "fragment_cntmon_39.h"
#include "extended_4t_39.h"



static status BadDigital(uchar  bError)
{
  Error39(bError);
  return ST_BADDIGITAL;
}



status  CntMonCanTariff39_Internal(uchar  ibMon, uchar  ibTariff)
{
  caller39 c = InitCaller39();
  
  time2 tm2 = FragmentOpenTime39(&c);
  if (!tm2.fValid) return BadDigital(95+0);
  time tm = tm2.tiValue;


  date dt;
  dt.bDay   = 1;
  dt.bMonth = ibMon + 1;
  dt.bYear  = (dt.bMonth > tm.bMonth) ? tm.bYear-1 : tm.bYear;


  double8 db8 = FragmentCntMonCan(obisBillingPeriodMon, obisScalerForBillingPeriod, &c, dt);

  DISC();
  if (Input39() != SER_GOODCHECK) return BadDigital(95+1);


  if (db8.fValid)
  {
    uchar i;
    for (i=0; i<4; i++) {
      mpdbChannelsC[i] = 0;
    }

    mpdbChannelsC[0] = db8.mdbValue[1 + ibTariff];

    for (i=0; i<4; i++) {
      mpdbChannelsC[i] = (mpdbChannelsC[i] / 1000) * mpdbTransCnt[ibDig];
      mpboChannelsA[i] = true;
    }

    return ST_OK;
  }

  if (db8.bError == ERROR_NOT_PRESENTED) {
    return ST_NOTPRESENTED;
  }

  return BadDigital(95+2);
}



status  ReadCntMonCanTariff39(uchar  ibMonAbs, uchar  ibTariff) // на начало мес€ца
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    status s = CntMonCanTariff39_Internal(ibMonAbs, ibTariff);
    if (fKey == true) break;

    if (s == ST_OK) return s;
    if (s == ST_NOTPRESENTED) return s;
  }

  DISC();
  if (Input39() != SER_GOODCHECK) return BadDigital(95+3);

  return BadDigital(95+4);
}



#ifdef  MONITOR_39

double2 TestCntMonCanTariff39(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  uchar bMonth = (*GetCurrTimeDate()).bMonth;

  uchar m;
  for (m=0; m<10; m++) {
    uchar ibMonthAbs = (12 + bMonth - 1 - m) % 12;
    
    uchar t;
    for (t=0; t<4; t++) {
      MonitorString("\n\n month="); MonitorCharDec(ibMonthAbs+1);
      MonitorString(" tariff="); MonitorCharDec(t);
      status s = ReadCntMonCanTariff39(ibMonthAbs, t);
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
