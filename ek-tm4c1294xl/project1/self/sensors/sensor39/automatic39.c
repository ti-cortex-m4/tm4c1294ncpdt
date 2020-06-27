/*------------------------------------------------------------------------------
automatic39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../sensors/automatic1.h"
#include "device39.h"
#include "error39.h"
#include "crc16x25.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "fragment_open_39.h"
#include "automatic39.h"



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



static void ShowId(uchar  bSize)
{
  bSize = bSize <= 16 ? bSize : 16;

  Clear();

  uchar i;
  for (i=0; i<bSize; i++)
    szLo[i] = PopChar();
}



static bool Fault(uchar  bError)
{
  Error39(20+bError);
  return false;
}



bool    Automatic39(void)
{
  Clear();

  caller39 c = InitCaller39();

  uchar bError = FragmentOpen39(&c);
  if (bError != 0) return Fault(0);

  c.bNS++;
  c.bInvokeId++;
  QueryId39(c.bNS, c.bNR, c.bInvokeId);
  if (Input39() != SER_GOODCHECK) return Fault(1);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return Fault(2);


  InitPop(12 + GetHdlcAddressesSize());

  uchar bResult = PopChar();
  if (bResult != 0) return Fault(3);

  uchar bType = PopChar();
  if (bType != 9) return Fault(4);

  uchar bSize = PopChar();
  ShowId(bSize);


  dbKpulse = 1000;
  dbKtrans = 1;
  SetAllFactors(dbKpulse, dbKtrans);


  Delay(1000);

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return Fault(5);

  return true;
}



bool    ChangeSpeed39(void)
{
  caller39 c = InitCaller39();

  uchar bError = FragmentOpen39(&c);
  if (bError != 0) return Fault(6);

  c.bNS++;
  c.bInvokeId++;
  QueryId39_Simple(c.bNS, c.bNR, c.bInvokeId);
  if (Input39() != SER_GOODCHECK) return Fault(7);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return Fault(8);


  Beep();


  InitPop(12 + GetHdlcAddressesSize_Simple());

  uchar bResult = PopChar();
  if (bResult != 0) return Fault(9);

  uchar bType = PopChar();
  if (bType != 9) return Fault(10);

  uchar bSize = PopChar();
  ShowId(bSize);


  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return Fault(11);


  return true;
}
