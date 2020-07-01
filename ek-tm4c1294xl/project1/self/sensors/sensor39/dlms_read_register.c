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
#include "device39.h"
#include "error39.h"
#include "io39.h"
#include "hdlc_address.h"
#include "query_register_39.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"



double2 ReadRegisterScalerDLMS(void)
{
  InitPop(12 + GetHdlcAddressesSize());

  uchar bDataAccessResult = PopChar();
#ifdef MONITOR_39
  MonitorString("\n DataAccessResult="); MonitorCharDec(bDataAccessResult);
#endif
  if (bDataAccessResult != 0) {
    return GetDouble2Error1(Error39_(20+0, bDataAccessResult));
  }

  if (PopChar() != 2) return GetDouble2Error1(Error39(20+1)); // !structure
  if (PopChar() != 2) return GetDouble2Error1(Error39(20+2)); // structure size != 1

  slong64_ scaler = PopSignedValueDLSM();
  if (!scaler.fValid) return GetDouble2Error1(Error39(20+3));

  ulong64_ unit = PopUnsignedValueDLSM();
  if (!unit.fValid) return GetDouble2Error1(Error39(20+4));

  double dbScaler = pow(10, scaler.ddwValue);
#ifdef MONITOR_39
  MonitorString("\n scaler="); MonitorCharHex(scaler.ddwValue % 0x100);
  MonitorString("\n unit="); MonitorCharDec(unit.ddwValue % 0x100);
  MonitorString("\n scaler="); MonitorDouble6(dbScaler);
#endif

  return GetDouble0(dbScaler);
}



double2 ReadRegisterValue39(const obis_t  obis, caller39*  pc)
{
  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryGetRegisterValueDLMS(obis, (*pc));
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(20+5));
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return GetDouble2Error1(Error39(20+6));
  ulong64_ ddw2 = ReadUnsignedValueDLSM();
  if (!ddw2.fValid) return GetDouble2Error1(Error39(20+7));

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(20+8));
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return GetDouble2Error1(Error39(20+9));

  return GetDouble0(ddw2.ddwValue);
}


double2 ReadRegisterScaler39(const obis_t  obis, caller39*  pc)
{
  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryGetRegisterScalerDLMS(obis, (*pc));
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(20+10));
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return GetDouble2Error1(Error39(20+11));
  double2 scaler = ReadRegisterScalerDLMS();
  if (!scaler.fValid) return GetDouble2Error1(Error39(20+12));

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(20+13));
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return GetDouble2Error1(Error39(20+14));

  return GetDouble0(scaler.dbValue);
}



double2 ReadRegisterValueWithScaler39(const obis_t  obis, caller39*  pc)
{
  double2 value = ReadRegisterValue39(obis, pc);
  if (!value.fValid) return GetDouble2Error1(Error39(20+15));

  double2 scaler = ReadRegisterScaler39(obis, pc);
  if (!scaler.fValid) return GetDouble2Error1(Error39(20+16));

  return GetDouble0(value.dbValue * scaler.dbValue);
}
