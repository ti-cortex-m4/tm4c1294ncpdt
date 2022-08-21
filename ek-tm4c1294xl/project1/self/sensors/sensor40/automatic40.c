/*------------------------------------------------------------------------------
automatic40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../sensors/automatic1.h"
#include "dlms.h"
#include "error40.h"
#include "crc16x25.h"
#include "io40.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "query_serial_40.h"
#include "fragment_open_40.h"
#include "automatic40.h"



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
  Error40(bError);
  return false;
}



bool    Automatic40(void)
{
  Clear();

  caller40 c = InitCaller40();

  uchar bError = FragmentOpen40(&c);
  if (bError != 0) return Fault(80+0);

  c.bNS++;
  c.bInvokeId++;
  QuerySerial40(c);
  if (Input40() != SER_GOODCHECK) return Fault(80+1);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return Fault(80+2);


  InitPop(12 + GetHdlcAddressesSize());

  uchar bResult = PopChar();
  if (bResult != 0) return Fault(80+3);

  uchar bType = PopChar();
  if (bType != 10) return Fault(80+4); // visible-string

  uchar bSize = PopChar();
  Show(bSize);


  dbKpulse = 2000;
  dbKtrans = 1;
  SetAllFactors(dbKpulse, dbKtrans);

  Delay(1000);


  DISC();
  if (Input40() != SER_GOODCHECK) return Fault(80+5);

  return true;
}



static void DISC0(uchar  bNumber)
{
  InitPush(0);

  uint wSize = 5+GetHdlcAddressesSize0(bNumber);

  PushChar(0x7E);
  PushFormatDLMS(wSize);
  PushHdlcAddresses0(bNumber);
  PushChar(0x53); // DISC

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize0(bNumber)));
  PushChar(0x7E);

  Query40(1000, wSize+2);
}


bool    ChangeNumber40(uchar  bNumber)
{
  DISC0(bNumber);
  if (Input40() != SER_GOODCHECK) return(0);
  Beep();

  return(1);
}
