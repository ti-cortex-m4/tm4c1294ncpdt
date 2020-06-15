/*------------------------------------------------------------------------------
hdlc_read_register.c

Blue Book: 4.1.5 Common data types
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
  MonitorString("\n Scaler="); MonitorIntHex(scaler % 0x10000);
  MonitorString("\n Unit="); MonitorIntDec(unit % 0x10000);
#endif

  return GetSignedLong64(scaler, true, 0);
}
