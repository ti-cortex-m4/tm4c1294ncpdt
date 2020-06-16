/*------------------------------------------------------------------------------
dlms_read_register.c

Blue Book: 4.3.2 Register (class_id = 3, version = 0)
------------------------------------------------------------------------------*/

#include <math.h>
#include "../../main.h"
#include "../../kernel/wrappers.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "device39.h"
#include "io39.h"
 #include "hdlc_address.h"
 #include "dlms_push.h"
#include "query_params_39.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"



slong64_ ReadRegisterScalerDLMS(void)
{
  InitPop(12 + GetHdlcAddressesSize());

 uchar bDataAccessResult = PopChar();
#ifdef MONITOR_39
 MonitorString("\n DataAccessResult="); MonitorCharDec(bDataAccessResult);
#endif
 if (bDataAccessResult != 0) {
   // TODO error(no_success, bDataAccessResult)
   return GetSLong64Error(1);
 }

  if (PopChar() != 2) return GetSLong64Error(2); // !structure
  if (PopChar() != 2) return GetSLong64Error(3); // structure size != 1

  slong64_ scaler = PopSignedValueDLSM();
  if (!scaler.fValid) return GetSLong64Error(4);

  ulong64_ unit = PopUnsignedValueDLSM();
  if (!unit.fValid) return GetSLong64Error(5);

#ifdef MONITOR_39
  MonitorString("\n scaler="); MonitorCharHex(scaler.ddwValue % 0x100);
  MonitorString("\n unit="); MonitorCharDec(unit.ddwValue % 0x100);
#endif

  return GetSLong64(scaler.ddwValue, true, 0);
}



double2 ReadRegisterValue39(const obis_t  obis, caller39*  pr)
{
  (*pr).bNS++;
  (*pr).bInvokeId++;
  QueryGetRegisterValueDLMS(obis, (*pr));
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe((*pr).bNS, (*pr).bNR)) return GetDouble2Error();
  ulong64_ ddw2 = ReadUnsignedValueDLSM();
  if (!ddw2.fValid) return GetDouble2Error();

  (*pr).bNR++;
  Query39_RR((*pr).bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe((*pr).bNR)) return GetDouble2Error();

  return GetDouble2(ddw2.ddwValue, true);
}


double2 ReadRegisterScaler39(const obis_t  obis, caller39*  pr)
{
  (*pr).bNS++;
  (*pr).bInvokeId++;
  QueryGetRegisterScalerDLMS(obis, (*pr));
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe((*pr).bNS, (*pr).bNR)) return GetDouble2Error();
  slong64_ scaler = ReadRegisterScalerDLMS();
  if (!scaler.fValid) return GetDouble2Error();

  (*pr).bNR++;
  Query39_RR((*pr).bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe((*pr).bNR)) return GetDouble2Error();

  double dbScaler = pow(10, scaler.ddwValue);
#ifdef MONITOR_39  
  MonitorString("\n scaler="); MonitorDouble6(dbScaler);
#endif  
  return GetDouble2(dbScaler, true);
}



double2 ReadRegisterValueWithScaler39(const obis_t  obis, caller39*  pr)
{
  double2 value = ReadRegisterValue39(obis, pr);
  if (!value.fValid) return GetDouble2Error();

  double2 scaler = ReadRegisterScaler39(obis, pr);
  if (!scaler.fValid) return GetDouble2Error();

  return GetDouble2(value.dbValue * scaler.dbValue, true);
}
