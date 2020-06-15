/*------------------------------------------------------------------------------
hdlc_read_register.c

Blue Book: 4.3.2 Register (class_id = 3, version = 0)
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../kernel/wrappers.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include39.h"
// #include "crc16x25.h"
// #include "io39.h"
// #include "hdlc.h"
// #include "dlms_push.h"
#include "hdlc_read_register.h"



long64_ ReadRegisterScaler(void)
{
  InitPop(12 + GetHdlcAddressesSize());

 uchar bDataAccessResult = PopChar();
#ifdef MONITOR_39
 MonitorString("\n bDataAccessResult="); MonitorCharDec(bDataAccessResult);
#endif
 if (bDataAccessResult != 0) {
   // TODO error(no_success, bDataAccessResult)
   return GetLong64Error(1);
 }

  if (PopChar() != 2) return GetLong64Error(2); // !structure
  if (PopChar() != 2) return GetLong64Error(3); // structure size != 1

  long64_ scaler = PopSignedValueDLSM();
  ulong64_ unit = PopUnsignedValueDLSM();
#ifdef MONITOR_39
  MonitorString("\n Scaler="); MonitorCharHex(scaler % 0x100);
  MonitorString("\n Unit="); MonitorCharDec(unit % 0x100);
#endif

  return GetSignedLong64(scaler, true, 0);
}



double2 ReadValue39(const obis_t  obis, runner39*  pr)
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


double2 ReadScaler39(const obis_t  obis, runner39*  pr)
{
  (*pr).bNS++;
  (*pr).bInvokeId++;
  QueryGetRegisterScalerDLMS(obis, (*pr));
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe((*pr).bNS, (*pr).bNR)) return GetDouble2Error();
  long64_ scaler = ReadRegisterScaler();
  if (!scaler.fValid) return GetDouble2Error();

  (*pr).bNR++;
  Query39_RR((*pr).bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe((*pr).bNR)) return GetDouble2Error();

  double dbScaler = pow(10, scaler.ddwValue);
#ifdef MONITOR_39  
  MonitorString("\n Scaler="); MonitorDouble6(dbScaler);
#endif  
  return GetDouble2(dbScaler, true);
}



float2  ReadRegisterWithScaler39(const obis_t  obis, runner39*  pr)
{
  double2 value = ReadValue39(obis, pr);
  if (!value.fValid) return GetFloat2Error();

  double2 scaler = ReadScaler39(obis, pr);
  if (!scaler.fValid) return GetFloat2Error();

  return GetFloat2(value.dbValue * scaler.dbValue, true);
}
