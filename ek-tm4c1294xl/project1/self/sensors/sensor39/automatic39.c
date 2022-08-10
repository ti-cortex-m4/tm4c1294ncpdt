/*------------------------------------------------------------------------------
automatic39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../sensors/automatic1.h"
#include "dlms.h"
#include "error39.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "query_id_39.h"
#include "fragment_open_39.h"
#include "automatic39.h"



static void Show(uchar  bSize)
{
  bSize = bSize <= 16 ? bSize : 16;

  Clear();

  uchar i;
  for (i=0; i<bSize; i++)
    szLo[i] = PopChar();
}



static bool Fault(uchar  bError)
{
  Error39(bError);
  return false;
}



bool    Automatic39(void)
{
  Clear();

  caller39 c = InitCaller39();

  uchar bError = FragmentOpen39(&c);
  if (bError != 0) return Fault(80+0);

  c.bNS++;
  c.bInvokeId++;
  QueryId39(c.bNS, c.bNR, c.bInvokeId);
  if (Input39() != SER_GOODCHECK) return Fault(80+1);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return Fault(80+2);


  InitPop(12 + GetHdlcAddressesSize());

  uchar bResult = PopChar();
  if (bResult != 0) return Fault(80+3);

  uchar bType = PopChar();
  if (bType != 10) return Fault(80+4); // visible-string

  uchar bSize = PopChar();
  Show(bSize);


  dbKpulse = 1000;
  dbKtrans = 1;
  SetAllFactors(dbKpulse, dbKtrans);

  Delay(1000);


  DISC();
  if (Input39() != SER_GOODCHECK) return Fault(80+5);

  return true;
}



bool    ChangeSpeed39(void)
{
  caller39 c = InitCaller39();

  uchar bError = FragmentOpen39(&c);
  if (bError != 0) return Fault(80+6);

  c.bNS++;
  c.bInvokeId++;
  QueryId39_Single(c.bNS, c.bNR, c.bInvokeId);
  if (Input39() != SER_GOODCHECK) return Fault(80+7);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return Fault(80+8);


  Beep();


  InitPop(12 + GetHdlcAddressesSize_Single());

  uchar bResult = PopChar();
  if (bResult != 0) return Fault(80+9);

  uchar bType = PopChar();
  if (bType != 10) return Fault(80+10); // visible-string

  uchar bSize = PopChar();
  Show(bSize);


  DISC();
  if (Input39() != SER_GOODCHECK) return Fault(80+11);


  return true;
}



uchar   GetHdlcAddressesSize_(uchar  wAddr)
{
  if (wAddr == 0) {
    return 1+1;
  } else if (wAddr <= 0x7F) {
    return 2+1;
  } else {
    return 4+1;
  }
}


void    PushHdlcAddresses_(uchar  wAddr)
{
  if (wAddr == 0) {
    PushChar(0x03);
  } else if (wAddr <= 0x7F) {
    PushChar(0x02);
  } else {
    PushChar(0x00);
    PushChar(0x02);
  }

  uchar bHi = wAddr / 0x100;
  uchar bLo = wAddr % 0x100;

  bHi = (bHi << 2) & 0xFC;
  if (bLo & 0x80) bHi |= 0x02;
  bLo = (bLo << 1) | 0x01;

  if (wAddr == 0) {
  } else if (wAddr <= 0x7F) {
    PushChar(bLo);
  } else {
    PushChar(bHi);
    PushChar(bLo);
  }

  PushChar((bLogical << 1) + 0x01);
}


void    DISC_(uchar  bNumber)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n DISC ");
#endif

  InitPush(0);

  uint wSize = 5+GetHdlcAddressesSize_(bNumber); // 7

  PushChar(0x7E);
  PushFormatDLMS(wSize);
  PushHdlcAddresses_(bNumber);
  PushChar(0x53); // DISC

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize_(bNumber))); // 5
  PushChar(0x7E);

  Query39(1000, wSize+2); // 9
}


bool    ChangeNumber39(uchar  bNumber)
{
  DISC_(bNumber);
  if (Input39() != SER_GOODCHECK) return(0);
  Beep();

  return(1);
}
