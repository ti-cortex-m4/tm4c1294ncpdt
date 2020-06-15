/*------------------------------------------------------------------------------
hdlc_read_data.c

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
// #include "hdlc_address.h"
// #include "dlms_push.h"
#include "hdlc_read_data.h"



ulong64_ PopUnsignedValueDLSM(void)
{
  uchar bDataType = PopChar();
#ifdef MONITOR_39  
  MonitorString("\n bDataType="); MonitorCharDec(bDataType);
#endif  

  if (bDataType == 17) // unsigned [17] Unsigned8 0…255
  {
    uchar value = PopChar();
    return GetLong64(value, true, 0);
  }
  if (bDataType == 22) // enum [22] 0…255
  {
    uchar value = PopChar();
    return GetLong64(value, true, 0);
  }
  if (bDataType == 18) // long-unsigned [18] Unsigned16 0…65_535
  {
    uint value = PopIntBig();
    return GetLong64(value, true, 0);
  }
  if (bDataType == 6) // double-long-unsigned [6] Unsigned32 0…4_294_967_295
  {
    ulong value = PopLongBig();
    return GetLong64(value, true, 0);
  }
  if (bDataType == 21) // long64-unsigned [21] Unsigned64 0…2^64-1
  {
    uint64_t value = PopLongBig()*0x100000000 + PopLongBig();
    return GetLong64(value, true, 0);
  }

  // error(unknown_data_type, bDataType)
  return GetLong64Error(1);
}


long64_  PopSignedValueDLSM(void)
{
  uchar bDataType = PopChar();
#ifdef MONITOR_39  
  MonitorString("\n bDataType="); MonitorCharDec(bDataType);
#endif  

  if (bDataType == 15) // integer [15] Integer8 -128…127
  {
    schar value = PopChar();
    return GetSignedLong64(value, true, 0);
  }
  if (bDataType == 16) // long [16] Integer16 -32_768…32_767
  {
    sint value = PopIntBig();
    return GetSignedLong64(value, true, 0);
  }
  if (bDataType == 5) // double-long [5] Integer32 -2_147_483_648…2_147_483_647
  {
    slong value = PopLongBig();
    return GetSignedLong64(value, true, 0);
  }
  if (bDataType == 20) // long64 [20] Integer64 - 2^63…2^63-1
  {
    int64_t value = PopLongBig()*0x100000000 + PopLongBig();
    return GetSignedLong64(value, true, 0);
  }

  // error(unknown_data_type, bDataType)
  return GetLong64Error(1);
}



ulong64_ ReadUnsignedValueDLSM(void)
{
  InitPop(12 + GetHdlcAddressesSize());

  uchar bDataAccessResult = PopChar();
#ifdef MONITOR_39
  MonitorString("\n bDataAccessResult="); MonitorCharDec(bDataAccessResult);
#endif
  if (bDataAccessResult != 0) {
    // error(no_success, bDataAccessResult)
    return GetLong64Error(0);
  }

  return PopUnsignedValueDLSM();
}
