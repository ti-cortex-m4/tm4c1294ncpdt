/*------------------------------------------------------------------------------
time39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "crc16x25.h"
#include "dlms_obis.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "time39.h"



void    QueryTime39(uchar  bNS, uchar  bNR, uchar  bInvokeId)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n QueryTime39 ");
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
  
  PushChar(0x00);
  PushChar(8); // clock (class_id = 8)
  
  PushOBIS_DLMS(obisTime);
  
  PushChar(2); // time (attribute = 2)
  PushChar(0x00);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));
  
  PushChar(0x7E);

  Query39(1000, wSize+2); // 27
}


time    ReadTime39(void)
{
  InitPop(15 + GetHdlcAddressesSize());

  time ti;
  ti.bYear   = PopIntBig() - 2000;
  ti.bMonth  = PopChar();
  ti.bDay    = PopChar();

  PopChar();

  ti.bHour   = PopChar();
  ti.bMinute = PopChar();
  ti.bSecond = PopChar();

  return ti;
}



void    QueryCorrectTime39(uchar  bNS, uchar  bNR, uchar  bInvokeId, sint  wSeconds)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n QueryCorrectTime39 "); MonitorSignedLongDec(wSeconds);
#endif

  uint wSize = 26 + GetHdlcAddressesSize();

  InitPush(0);
  PushChar(0x7E);
  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar((bNR << 5) | 0x10 | (bNS << 1) | 0x00);

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize()));

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC3); // Action-Request
  PushChar(0x01); // Action-Request-Normal
  PushChar(0xC0 | (bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0x00);
  PushChar(8); // clock (class_id = 8)

  PushOBIS_DLMS(obisTime);

  PushChar(6); // shift_time (method = 6)
  PushChar(0x01);

  PushChar(0x10);

  if (wSeconds < -900) wSeconds = -900;
  else if (wSeconds > 900) wSeconds = 900;

  PushIntBig(wSeconds);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query39(1000, wSize+2);
}
