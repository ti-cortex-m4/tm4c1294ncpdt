/*------------------------------------------------------------------------------
dlms_read_data.c

Blue Book: 4.1.5 Common data types
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../kernel/wrappers.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "error39.h"
#include "hdlc_address.h"
#include "dlms_read_data.h"



ulong64_ PopUnsignedValueDLSM(void)
{
  uchar bDataType = PopChar();
#ifdef MONITOR_39  
  MonitorString("\n DataType="); MonitorCharDec(bDataType);
#endif  

  if (bDataType == 17) // unsigned [17] Unsigned8 0…255
  {
    uchar value = PopChar();
    return GetULong64Ok(value);
  }
  if (bDataType == 22) // enum [22] 0…255
  {
    uchar value = PopChar();
    return GetULong64Ok(value);
  }
  if (bDataType == 18) // long-unsigned [18] Unsigned16 0…65_535
  {
    uint value = PopIntBig();
    return GetULong64Ok(value);
  }
  if (bDataType == 6) // double-long-unsigned [6] Unsigned32 0…4_294_967_295
  {
    ulong value = PopLongBig();
    return GetULong64Ok(value);
  }
  if (bDataType == 21) // long64-unsigned [21] Unsigned64 0…2^64-1
  {
    uint64_t value = PopLongBig()*0x100000000 + PopLongBig();
    return GetULong64Ok(value);
  }

  return GetULong64Error(ErrorData39(10+0, bDataType));
}


slong64_ PopSignedValueDLSM(void)
{
  uchar bDataType = PopChar();
#ifdef MONITOR_39  
  MonitorString("\n DataType="); MonitorCharDec(bDataType);
#endif  

  if (bDataType == 15) // integer [15] Integer8 -128…127
  {
    schar value = PopChar();
    return GetSLong64Ok(value);
  }
  if (bDataType == 17) // unsigned [17] Unsigned8 0…255
  {
    uchar value = PopChar();
    return GetSLong64Ok(value);
  }
  if (bDataType == 22) // enum [22] 0…255
  {
    uchar value = PopChar();
    return GetSLong64Ok(value);
  }
  if (bDataType == 16) // long [16] Integer16 -32_768…32_767
  {
    sint value = PopIntBig();
    return GetSLong64Ok(value);
  }
  if (bDataType == 18) // long-unsigned [18] Unsigned16 0…65_535
  {
    uint value = PopIntBig();
    return GetSLong64Ok(value);
  }
  if (bDataType == 5) // double-long [5] Integer32 -2_147_483_648…2_147_483_647
  {
    slong value = PopLongBig();
    return GetSLong64Ok(value);
  }
  if (bDataType == 6) // double-long-unsigned [6] Unsigned32 0…4_294_967_295
  {
    ulong value = PopLongBig();
    return GetSLong64Ok(value);
  }
  if (bDataType == 20) // long64 [20] Integer64 - 2^63…2^63-1
  {
    int64_t value = PopLongBig()*0x100000000 + PopLongBig();
    return GetSLong64Ok(value);
  }
  if (bDataType == 21) // long64-unsigned [21] Unsigned64 0…2^64-1
  {
    uint64_t value = PopLongBig()*0x100000000 + PopLongBig();
    return GetSLong64Ok(value);
  }

  return GetSLong64Error(ErrorData39(10+1, bDataType));
}



ulong64_ ReadUnsignedValueDLSM(void)
{
  InitPop(12 + GetHdlcAddressesSize());

  uchar bDataAccessResult = PopChar();
#ifdef MONITOR_39
  MonitorString("\n DataAccessResult="); MonitorCharDec(bDataAccessResult);
#endif

  if (bDataAccessResult != 0) {
    return GetULong64Error(ErrorData39(10+2, bDataAccessResult));
  }

  ulong64_ value = PopUnsignedValueDLSM();
#ifdef MONITOR_39
  MonitorString("\n Value="); MonitorLong64Hex(value.ddwValue);
#endif

  return value;
}


slong64_ ReadSignedValueDLSM(void)
{
  InitPop(12 + GetHdlcAddressesSize());

  uchar bDataAccessResult = PopChar();
#ifdef MONITOR_39
  MonitorString("\n DataAccessResult="); MonitorCharDec(bDataAccessResult);
#endif

  if (bDataAccessResult != 0) {
    return GetSLong64Error(ErrorData39(10+3, bDataAccessResult));
  }

  return PopSignedValueDLSM();
}
