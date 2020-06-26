/*------------------------------------------------------------------------------
extended_4t_39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/timedate.h"
#include "../../time/rtc.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports2.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "device39.h"
#include "device39_obis.h"
#include "error39.h"
#include "time39.h"
#include "query_engmon_39.h"
#include "query_register_39.h"
#include "fragment_open_time_39.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"
#include "extended_4t_39.h"



const obis_t *GetOBIS(uchar  ibTariff)
{
  ASSERT(sizeof(obisEngAbsTariff)/sizeof(obisEngAbsTariff[0]) == 4);
  ASSERT(ibTariff < 4);
  return &obisEngAbsTariff[ibTariff];
}



status  CntMonCanTariff39_Internal(uchar  ibMon, uchar  ibTariff)
{
  caller39 c = InitCaller39();
  
  time2 tm2 = FragmentOpenTime39(&c);
  if (!tm2.fValid) { Error39(130+0); return ST_BADDIGITAL; }
  time tm = tm2.tiValue;


  uchar bMonth = ibMon + 1;
  uchar bYear = (bMonth > tm.bMonth) ? tm.bYear-1 : tm.bYear;


  c.bNS++;
  QueryEngMon39(*GetOBIS(ibTariff), c.bNS, c.bNR, c.bInvokeId++, bMonth, bYear);
  if (Input39() != SER_GOODCHECK) { Error39(130+1); return ST_BADDIGITAL; }
  if (ValidateFrame(c.bNS, c.bNR) != 0) { Error39(130+2); return ST_BADDIGITAL; }


  bool present = (IsEngMonPresent39() == 0);
  bool absent = (IsEngMonAbsent39() == 0);

  ulong64_ ddwValue = GetULong64Error1(130+3);
  if (present) {
    InitPop(17 + GetHdlcAddressesSize());
    ddwValue = PopUnsignedValueDLSM();
  }

#ifdef MONITOR_39
  MonitorString("\n present="); MonitorBool(present);
  MonitorString("\n absent="); MonitorBool(absent);
  MonitorString("\n valid="); MonitorBool(ddwValue.fValid);
  MonitorString("\n value="); MonitorLongDec(ddwValue.ddwValue);
#endif


  c.bNR++;
  Query39_RR(c.bNR);
  if (Input39() != SER_GOODCHECK) { Error39(130+4); return ST_BADDIGITAL; }
  if (!ValidateSframe(c.bNR)) { Error39(130+5); return ST_BADDIGITAL; }


  double2 scaler = ReadRegisterScaler39(*GetOBIS(ibTariff), &c);
  if (!scaler.fValid) { Error39(130+6); return ST_BADDIGITAL; }
  double dbScaler = scaler.dbValue;


  Query39_DISC();
  if (Input39() != SER_GOODCHECK) { Error39(130+7); return ST_BADDIGITAL; }


  if (present) {
    mpdbChannelsC[0] = ((double)ddwValue.ddwValue * dbScaler / 1000) * mpdbTransCnt[ibDig];
    mpboChannelsA[0] = true;
#ifdef MONITOR_39
    MonitorString("\n result="); MonitorDouble6(mpdbChannelsC[0]);
#endif
    return ST_OK;
  }

  if (absent) {
#ifdef MONITOR_39
    MonitorString("\n result absent");
#endif
    return ST_NOTPRESENTED;
  }

  Error39(130+8);
  return ST_BADDIGITAL;
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
  if (Input39() != SER_GOODCHECK) { Error39(130+9); return ST_BADDIGITAL; }

  Error39(130+10);
  return ST_BADDIGITAL;
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
