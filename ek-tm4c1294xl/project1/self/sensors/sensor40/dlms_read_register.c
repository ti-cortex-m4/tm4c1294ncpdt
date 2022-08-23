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
#include "dlms.h"
#include "error40.h"
#include "io40.h"
#include "hdlc_address.h"
#include "query_register_40.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"



static double2 Fault(uchar  bError)
{
  return GetDouble2Error1(Error40(bError));
}



double2 ReadRegisterScalerDLMS(void)
{
  InitPop(12 + GetHdlcAddressesSize());

  uchar bDataAccessResult = PopChar();
#ifdef MONITOR_40
  MonitorString("\n DataAccessResult="); MonitorCharDec(bDataAccessResult);
#endif

  if (bDataAccessResult != 0) {
    return GetDouble2Error1(ErrorData40(15+0, bDataAccessResult));
  }

  if (PopChar() != 2) return Fault(15+1); // !structure
  if (PopChar() != 2) return Fault(15+2); // structure size != 1

  slong64_ scaler = PopSignedValueDLSM();
  if (!scaler.fValid) return Fault(15+3);

  ulong64_ unit = PopUnsignedValueDLSM();
  if (!unit.fValid) return Fault(15+4);

  double dbScaler = pow(10, scaler.ddwValue);

#ifdef MONITOR_40
  MonitorString("\n Scaler="); MonitorCharHex(scaler.ddwValue % 0x100);
  MonitorString("\n Unit="); MonitorCharDec(unit.ddwValue % 0x100);
  MonitorString("\n ScalerValue="); MonitorDouble6(dbScaler);
#endif

  return GetDouble0(dbScaler);
}



double2 ReadRegisterUnsignedValue39(const obis_t  obis, caller40*  pc)
{
  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryGetRegisterValueDLMS(obis, (*pc));
  if (Input40() != SER_GOODCHECK) return Fault(15+5);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(15+6);

  ulong64_ value = ReadUnsignedValueDLSM();
  if (!value.fValid) return Fault(15+7);

  (*pc).bNR++;
  RR((*pc).bNR);
  if (Input40() != SER_GOODCHECK) return Fault(15+8);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(15+9);

  return GetDouble0(value.ddwValue);
}


double2 ReadRegisterSignedValue39(const obis_t  obis, caller40*  pc)
{
  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryGetRegisterValueDLMS(obis, (*pc));
  if (Input40() != SER_GOODCHECK) return Fault(15+10);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(15+11);

  slong64_ value = ReadSignedValueDLSM();
  if (!value.fValid) return Fault(15+12);

  (*pc).bNR++;
  RR((*pc).bNR);
  if (Input40() != SER_GOODCHECK) return Fault(15+13);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(15+14);

  return GetDouble0(value.ddwValue);
}


double2 ReadRegisterScaler39(const obis_t  obis, caller40*  pc)
{
  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryGetRegisterScalerDLMS(obis, (*pc));
  if (Input40() != SER_GOODCHECK) return Fault(15+15);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(15+16);

  double2 scaler = ReadRegisterScalerDLMS();
  if (!scaler.fValid) return Fault(15+17);

  (*pc).bNR++;
  RR((*pc).bNR);
  if (Input40() != SER_GOODCHECK) return Fault(15+18);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(15+19);

  return GetDouble0(scaler.dbValue);
}



double2 ReadRegisterUnsignedValueWithScaler39(const obis_t  obis, caller40*  pc)
{
  double2 value = ReadRegisterUnsignedValue39(obis, pc);
  if (!value.fValid) return Fault(15+20);

  double2 scaler = ReadRegisterScaler39(obis, pc);
  if (!scaler.fValid) return Fault(15+21);

  return GetDouble0(value.dbValue * scaler.dbValue);
}


double2 ReadRegisterSignedValueWithScaler39(const obis_t  obis, caller40*  pc)
{
  double2 value = ReadRegisterSignedValue39(obis, pc);
  if (!value.fValid) return Fault(15+22);

  double2 scaler = ReadRegisterScaler39(obis, pc);
  if (!scaler.fValid) return Fault(15+23);

  return GetDouble0(value.dbValue * scaler.dbValue);
}
