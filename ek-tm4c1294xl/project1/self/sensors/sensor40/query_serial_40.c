/*------------------------------------------------------------------------------
query_serial_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "crc16x25.h"
#include "io40.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "query_serial_40.h"



void    QuerySerial40(caller40  c)
{
#ifdef MONITOR_40_NAMES
  MonitorString("\n\n QuerySerial40 ");
#endif

  uint wSize = 23 + GetHdlcAddressesSize();

  InitPush(0);
  PushChar(0x7E);

  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar((((c.bNR & 0x07) << 5) | 0x10 | ((c.bNS & 0x07) << 1) | 0x00));

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize()));

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal
  PushChar(0xC0 | (c.bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0);
  PushChar(1); // class

  PushOBIS_DLMS(obisSerial);

  PushChar(2); // attribute
  PushChar(0);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query40(1000, wSize+2);
}
