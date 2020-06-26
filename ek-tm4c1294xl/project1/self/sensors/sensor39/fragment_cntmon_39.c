/*------------------------------------------------------------------------------
fragment_cntmon_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_digitals.h"
//#include "../../memory/mem_factors.h"
//#include "../../display/display.h"
//#include "../../keyboard/keyboard.h"
//#include "../../time/timedate.h"
//#include "../../time/rtc.h"
#include "../../serial/monitor.h"
//#include "../../serial/monitor_settings.h"
#include "../../serial/ports_pop.h"
//#include "../../serial/ports_devices.h"
//#include "../../serial/ports2.h"
//#include "../../devices/devices.h"
//#include "../../digitals/digitals.h"
#include "device39.h"
#include "device39_obis.h"
#include "error39.h"
//#include "time39.h"
#include "query_engmon_39.h"
#include "read_engmon_39.h"
#include "query_register_39.h"
//#include "fragment_open_time_39.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"
#include "fragment_cntmon_39.h"



double2 FragmentCntMonCan(const obis_t  obis, caller39  *pc, uchar  bMonth, uchar  bYear)
{
  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryEngMon39(obis, (*pc).bNS, (*pc).bNR, (*pc).bInvokeId, bMonth, bYear);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(110+0));
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return GetDouble2Error1(Error39(110+0));


  bool present = (IsEngMonPresent39() == 0);
  bool absent = (IsEngMonAbsent39() == 0);

  ulong64_ ddwValue = GetULong64Error1(0);
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


  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(110+0));
  if (!ValidateSframe((*pc).bNR)) return GetDouble2Error1(Error39(110+0));


  double2 scaler = ReadRegisterScaler39(obis, pc);
  if (!scaler.fValid) return GetDouble2Error1(Error39(110+0));
  double dbScaler = scaler.dbValue;


  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(110+0));


  if (present) {
    double db = (double)ddwValue.ddwValue * dbScaler / 1000;
#ifdef MONITOR_39
    MonitorString("\n result="); MonitorDouble6(db);
#endif
    return GetDouble0(db);
  }

  if (absent) {
#ifdef MONITOR_39
    MonitorString("\n result absent");
#endif
    return GetDouble2(-1, false);
  }

  return GetDouble2Error1(Error39(110+0));
}
