/*------------------------------------------------------------------------------
query_params_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "crc16x25.h"
#include "io39.h"
#include "hdlc.h"
#include "dlms_push.h"
#include "query_params_39.h"



void    QueryParam39_(uchar  bNS, uchar  bNR, uchar  bInvokeId)
{
#ifdef MONITOR_39  
  MonitorString("\n\n QueryParam39 ");
#endif

  uint wSize = 23 + GetHdlcAddressesSize(); // 0x19 25

  InitPush(0);
  PushChar(0x7E);

  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar((bNR << 5) | 0x10 | (bNS << 1) | 0x00);

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal
  PushChar(0x80 | (bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0x00);
  PushChar(0x03); // class

  PushChar(1); // <!--1.0.72.7.0.255-->
  PushChar(0);
  PushChar(72);
  PushChar(7);
  PushChar(0);
  PushChar(255);

  PushChar(0x02);
  PushChar(0x00);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query39(1000, wSize+2); // 27
}



uint    ReadParam39_(void)
{
  InitPop(14 + GetHdlcAddressesSize());
  return PopIntBig();
}
