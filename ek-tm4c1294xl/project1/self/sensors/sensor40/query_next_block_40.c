/*------------------------------------------------------------------------------
query_next_block_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "crc16x25.h"
#include "io40.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "query_next_block_40.h"



/*
<GetRequest>
  <GetRequestForNextDataBlock>
    <!--Priority: HIGH ServiceClass: UN_CONFIRMED invokeID: 10-->
    <InvokeIdAndPriority Value="8A" />
    <BlockNumber Value="00000001" />
  </GetRequestForNextDataBlock>
</GetRequest>
*/
void    QueryNextBlock39(caller40  c, uchar  bBlockNumber)
{
#ifdef MONITOR_40_NAMES
  MonitorString("\n\n QueryNextBlock39 "); MonitorCharDec(bBlockNumber);
#endif  

  uint wSize = 17 + GetHdlcAddressesSize();

  InitPush(0);
  PushChar(0x7E);
  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar(((c.bNR & 0x07) << 5) | 0x10 | ((c.bNS & 0x07) << 1) | 0x00);

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize()));

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x02); // Get-Request-Next
  PushChar(0xC0 | (c.bInvokeId % 16)); // Invoke-Id-And-Priority

  PushLongBig(bBlockNumber); // <BlockNumber Value="00000001" />

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query40(1000, wSize+2);
}
