/*------------------------------------------------------------------------------
extended_4t_39*c


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
#include "device39.h"
#include "device39_obis.h"
#include "error39.h"
#include "io39.h"
#include "fragment_open_time_39.h"
#include "fragment_cntmon_39.h"
#include "extended_4t_39.h"



const obis_t *GetOBIS(uchar  ibTariff)
{
  ASSERT(sizeof(obisEngAbsTariff)/sizeof(obisEngAbsTariff[0]) == 4);
  ASSERT(ibTariff < 4);
  return &obisEngAbsTariff[ibTariff];
}


static status BadDigital(uchar  bError) {  
  Error39(bError);
  return ST_BADDIGITAL;
}


status  CntMonCanTariff39_Internal(uchar  ibMon, uchar  ibTariff)
{
  caller39 c = InitCaller39();
  
  time2 tm2 = FragmentOpenTime39(&c);
  if (!tm2.fValid) return BadDigital(130+0);
  time tm = tm2.tiValue;


  uchar bMonth = ibMon + 1;
  uchar bYear = (bMonth > tm.bMonth) ? tm.bYear-1 : tm.bYear;


  double2 db2 = FragmentCntMonCan(*GetOBIS(ibTariff), &c, bMonth, bYear);
  uchar bError = db2.bError;

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return BadDigital(130+6);


  if (db2.fValid) {
    mpdbChannelsC[0] = db2.dbValue * mpdbTransCnt[ibDig];
    mpboChannelsA[0] = true;
    return ST_OK;
  }

  if (bError == 1) {
    return ST_NOTPRESENTED;
  }

  return BadDigital(130+7);
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

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return BadDigital(130+8);

  return BadDigital(130+9);
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
    }
  }

  return GetDouble0(0);
}

#endif
