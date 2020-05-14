/*------------------------------------------------------------------------------
query_next_block_36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include38.h"
#include "crc16x25.h"
#include "io36.h"
#include "hdlc.h"
#include "push_dlms.h"
#include "device36.h" //
#include "query_next_block_38.h"



/*
<GetRequest>
  <GetRequestForNextDataBlock>
    <!--Priority: HIGH ServiceClass: UN_CONFIRMED invokeID: 10-->
    <InvokeIdAndPriority Value="8A" />
    <BlockNumber Value="00000001" />
  </GetRequestForNextDataBlock>
</GetRequest>
*/
void    QueryNextBlock36(uchar  bNS, uchar  bNR, uchar  bInvokeId, uchar  bBlockNumber)
{
  MonitorString("\n\n NextBlock"); // TODO ???

  uint wSize = 17 + GetHdlcAddressesSize();

  InitPush(0);
  PushChar(0x7E);
  PushFormatDLMS(wSize);
  PushHdlcAddresses();

//MonitorString("Control{R(R)=1} 31 ? "); MonitorCharHex((bNR << 5) | 0x10 | 0x01);
  PushChar((bNR << 5) | 0x10 | (bNS << 1) | 0x00);

  PushIntLtl(MakeCRC16_X25OutBuff(1, 3+GetHdlcAddressesSize()));

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x02); // Get-Request-Normal /// TODO ???
  PushChar(0x80 | (bInvokeId % 16)); // Invoke-Id-And-Priority

  PushLongBig(bBlockNumber); // <BlockNumber Value="00000001" /> TODO ???

  // DLMS finish

  PushIntLtl(MakeCRC16_X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query36(1000, wSize+2); // 0x13
}
