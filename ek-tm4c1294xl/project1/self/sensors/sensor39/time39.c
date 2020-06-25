/*------------------------------------------------------------------------------
time39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "crc16x25.h"
#include "device39_obis.h"
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
  PushChar(0x08); // class
  
  PushChar(0x00); // 0-0:1.0.0*255
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0xFF);
  
  PushChar(0x02); // index  
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

  PushChar(6); // shift_time (method 6)
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

// Output: out=30 in=1000
// 7e a0 1c 03 03 54 8b a0    e6 e6 00 c3 01 c2 00 08  00 00 01 00 00 ff  06 01 10 00 00 41 06 7e
// 7E A01C 0221 61 34 2DC7    E6 E6 00 C3 01 C1 00 46  00 00 60 03 01 FF  01 01 0F 00    EF B4 7E
// 7E A0 28 02 21 61 54 41 45 E6 E6 00 C1 01 81 00 08  00 00 01 00 00 FF  02 00 09 0C 07 E0 0A 1F FF 08 2E 26 01 00 00 00 F6 6D 7E

//service-class
