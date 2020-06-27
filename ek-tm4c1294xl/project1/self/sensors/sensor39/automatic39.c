/*------------------------------------------------------------------------------
automatic39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
//#include "../../sensors/automatic1.h"
#include "../../digitals/digitals.h"
#include "device39.h"
#include "io39.h"
#include "automatic39.h"



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

  PushChar(0x00);
  PushChar(8); // clock (class_id = 8)

  PushOBIS_DLMS(obisId);

  PushChar(2); // time (attribute = 2)
  PushChar(0x00);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query39(1000, wSize+2); // 27
}



bool    ChangeSpeed38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushLongLtl(0);

  PushChar(0x00);
  PushChar(0x06);

  PushChar(6);
  PushChar(0);
  PushChar(5);

  Query38(250, 14);


  if (Input38() != SER_GOODCHECK) return false;
  Beep();

  ShowLong(ReadNumber38());
  return true;
}
