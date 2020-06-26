/*------------------------------------------------------------------------------
fragment_cntmon_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "../../serial/ports_pop.h"
#include "device39.h"
#include "device39_obis.h"
#include "error39.h"
#include "query_engmon_39.h"
#include "read_engmon_39.h"
#include "query_register_39.h"
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
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(170+0));
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return GetDouble2Error1(Error39(170+1));


  bool present = (EngMonPresent39() == 0);
  bool absent = (EngMonAbsent39() == 0);

  ulong64_ counter = present ? ReadEngMon39() : GetULong64Error1(0);

#ifdef MONITOR_39
  MonitorString("\n present="); MonitorBool(present);
  MonitorString("\n absent="); MonitorBool(absent);
  MonitorString("\n valid="); MonitorBool(counter.fValid);
  MonitorString("\n value="); MonitorLongDec(counter.ddwValue);
#endif


  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(170+2));
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return GetDouble2Error1(Error39(170+3));


  double2 scaler = ReadRegisterScaler39(obis, pc);
  if (!scaler.fValid) return GetDouble2Error1(Error39(170+4));


  if (present) {
    double db = (double)counter.ddwValue * scaler.dbValue;
#ifdef MONITOR_39
    MonitorString("\n result="); MonitorDouble6(db);
#endif
    return GetDouble0(db);
  }

  if (absent) {
#ifdef MONITOR_39
    MonitorString("\n result is absent");
#endif
    return GetDouble2Error1(ERROR_NOT_PRESENTED);
  }

  return GetDouble2Error1(Error39(170+5));
}
