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
    <!--Priority: HIGH ServiceClass: CONFIRMED invokeID: 2-->
    <InvokeIdAndPriority Value="194" />
    <Result>
      <Data>
        <Array Qty="1" >
          <Structure Qty="9" >
            <!--2022-07-01 00:00:00-->
            <OctetString Value="07E60701FF0000000000B480" />
            <UInt32 Value="4609456" />
            <UInt32 Value="3074755" />
            <UInt32 Value="1534701" />
            <UInt32 Value="0" />
            <UInt32 Value="0" />
            <UInt32 Value="0" />
            <UInt32 Value="5617" />
            <UInt32 Value="8481" />
          </Structure>
        </Array>
      </Data>
    </Result>
  </GetResponseNormal>
</GetResponse>
</PDU>
*/
uchar   EngMonPresent39(void)
{
  InitPop(12 + GetHdlcAddressesSize());

  if (PopChar() != 0) return 40+0; // !success
  if (PopChar() != 1) return 40+1; // !array
  if (PopChar() != 1) return 40+2; // array size != 1
  if (PopChar() != 2) return 40+3; // !structure
  if (PopChar() != 9) return 40+4; // structure size != 9
  if (PopChar() != 9) return 40+5; // octet-string
  if (PopChar() != 12) return 40+6; // size != 12

  uchar i;
  for (i=0; i<12; i++) {
    PopChar(); // skip date/time
  }

  return 0;
}
