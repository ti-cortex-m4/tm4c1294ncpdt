/*------------------------------------------------------------------------------
query_id_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "crc16x25.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "query_id_39.h"



void    QueryId39_Simple(uchar  bNS, uchar  bNR, uchar  bInvokeId)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n QueryId39_Simple ");
#endif

  uint wSize = 23 + GetHdlcAddressesSize_Simple(); // 0x19 25

  InitPush(0);
  PushChar(0x7E);

  PushFormatDLMS(wSize);
  PushHdlcAddresses_Simple();

  PushChar(((bNR << 5) | 0x10 | (bNS << 1) | 0x00));

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize_Simple())); // 5

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal
  PushChar(0xC0 | (bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0);
  PushChar(1);

  PushOBIS_DLMS(obisId);

  PushChar(2);
  PushChar(0);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query39(1000, wSize+2); // 27
}



void    QueryId39(uchar  bNS, uchar  bNR, uchar  bInvokeId)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n QueryId39 ");
#endif

  uint wSize = 23 + GetHdlcAddressesSize(); // 0x19 25

  InitPush(0);
  PushChar(0x7E);

  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar(((bNR << 5) | 0x10 | (bNS << 1) | 0x00));

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal
  PushChar(0xC0 | (bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0);
  PushChar(1);

  PushOBIS_DLMS(obisId);

  PushChar(2);
  PushChar(0);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query39(1000, wSize+2); // 27
}