/*------------------------------------------------------------------------------
read_engmon_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "crc16x25.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_read_data.h"
#include "read_engmon_39.h"



/*
<PDU>
<GetResponse>
  <GetResponseNormal>
    <!--Priority: HIGH ServiceClass: UN_CONFIRMED invokeID: 6-->
    <InvokeIdAndPriority Value="86" />
    <Result>
      <Data>
        <Array Qty="01" >
          <Structure Qty="01" >
            <UInt64 Value="00000000000030B3" />
          </Structure>
        </Array>
      </Data>
    </Result>
  </GetResponseNormal>
</GetResponse>
</PDU>
*/
ulong64_ ReadEngMon39(void)
{
  InitPop(12 + 5 + GetHdlcAddressesSize());
  return PopUnsignedValueDLSM();
}



uchar   IsEngMonPresent39(void)
{
  InitPop(12 + GetHdlcAddressesSize());

  if (PopChar() != 0) return 1; // !success
  if (PopChar() != 1) return 2; // !array
  if (PopChar() != 1) return 3; // array size != 1
  if (PopChar() != 2) return 4; // !structure
  if (PopChar() != 1) return 5; // structure size != 1

  return 0;
}


uchar   IsEngMonAbsent39(void)
{
  InitPop(12 + GetHdlcAddressesSize());

  if (PopChar() != 0) return 1; // !success
  if (PopChar() != 1) return 2; // !array
  if (PopChar() != 0) return 3; // array size != 0

  return 0;
}



/*
7e a0 1d 03 03 74 32 9d e6 e7 00 c4 01 81  00 01 01 02 01 15  00 00 00 00 00 00 0f 31  1d 75 7e
00 success
01 array
01 array size
02 structure
01 structure size
15 [21] Unsigned64
value=3889

7e a0 12 03 03 74 cb 2f e6 e7 00 c4 01 81  00 01 00  3d ce 7e
00 success
01 array
00 array size
no value
*/
