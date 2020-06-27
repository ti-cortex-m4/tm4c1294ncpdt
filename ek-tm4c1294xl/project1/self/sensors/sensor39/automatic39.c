/*------------------------------------------------------------------------------
automatic39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
//#include "../../sensors/automatic1.h"
#include "../../digitals/digitals.h"
#include "device39.h"
#include "caller39.h"
#include "crc16x25.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "fragment_open_39.h"
#include "automatic39.h"



void    QueryId39(uchar  bNS, uchar  bNR, uchar  bInvokeId)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n QueryId39 ");
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



bool    ChangeSpeed39(void)
{
  caller39 c = InitCaller39();

  uchar bError = FragmentOpen39(&c);
  if (bError != 0) return false;

  QueryId39(c.bNS, c.bNR, c.bInvokeId);
  if (Input39() != SER_GOODCHECK) return false;


  Beep();


  Clear();

  InitPop(12 + GetHdlcAddressesSize_Simple());
  uchar a = PopChar();
  uchar b = PopChar();
  uchar d = PopChar();

  uchar i;
  for (i=0; i<5; i++)
    szLo[i] = PopChar();

  return true;
}
