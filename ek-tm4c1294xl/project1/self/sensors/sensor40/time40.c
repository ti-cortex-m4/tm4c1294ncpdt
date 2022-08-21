/*------------------------------------------------------------------------------
time40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include40.h"
#include "crc16x25.h"
#include "dlms_obis.h"
#include "io40.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "correct40.h"
#include "time40.h"



void    QueryTime40(caller40  c)
{
#ifdef MONITOR_40_NAMES
  MonitorString("\n\n QueryTime39 ");
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
  
  PushChar(0x00);
  PushChar(8); // clock (class_id = 8)
  
  PushOBIS_DLMS(obisTime);
  
  PushChar(2); // time (attribute = 2)
  PushChar(0x00);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));
  
  PushChar(0x7E);

  Query40(1000, wSize+2);
}


time    ReadTime40(void)
{
  InitPop(15 + GetHdlcAddressesSize());

  time tm;
  tm.bYear   = PopIntBig() - 2000;
  tm.bMonth  = PopChar();
  tm.bDay    = PopChar();

  PopChar();

  tm.bHour   = PopChar();
  tm.bMinute = PopChar();
  tm.bSecond = PopChar();

  return tm;
}



void    QueryCorrectTime40(caller40  c, sint  wSeconds)
{
#ifdef MONITOR_40_NAMES
  MonitorString("\n\n QueryCorrectTime39 "); MonitorSignedLongDec(wSeconds);
#endif

  uint wSize = 26 + GetHdlcAddressesSize();

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

  PushChar(0xC3); // Action-Request
  PushChar(0x01); // Action-Request-Normal
  PushChar(0xC0 | (c.bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0x00);
  PushChar(8); // clock (class_id = 8)

  PushOBIS_DLMS(obisTime);

  PushChar(6); // shift_time (method = 6)
  PushChar(0x01);

  PushChar(0x10);

  if (wSeconds < -wLIMITCORRECT_40)
    wSeconds = -wLIMITCORRECT_40;
  else if (wSeconds > wLIMITCORRECT_40)
    wSeconds = wLIMITCORRECT_40;

  PushIntBig(wSeconds);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query40(1000, wSize+2);
}
