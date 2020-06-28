/*------------------------------------------------------------------------------
automatic39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../sensors/automatic1.h"
#include "device39.h"
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
  if (bError != 0) return Fault(20+0);

  c.bNS++;
  c.bInvokeId++;
  QueryId39(c.bNS, c.bNR, c.bInvokeId);
  if (Input39() != SER_GOODCHECK) return Fault(20+1);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return Fault(20+2);


  InitPop(12 + GetHdlcAddressesSize());

  uchar bResult = PopChar();
  if (bResult != 0) return Fault(20+3);

  uchar bType = PopChar();
  if (bType != 9) return Fault(20+4);

  uchar bSize = PopChar();
  Show(bSize);


  dbKpulse = 1000;
  dbKtrans = 1;
  SetAllFactors(dbKpulse, dbKtrans);


  Delay(1000);

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return Fault(20+5);

  return true;
}



bool    ChangeSpeed39(void)
{
  caller39 c = InitCaller39();

  uchar bError = FragmentOpen39(&c);
  if (bError != 0) return Fault(20+6);

  c.bNS++;
  c.bInvokeId++;
  QueryId39_Simple(c.bNS, c.bNR, c.bInvokeId);
  if (Input39() != SER_GOODCHECK) return Fault(20+7);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return Fault(20+8);


  Beep();


  InitPop(12 + GetHdlcAddressesSize_Simple());

  uchar bResult = PopChar();
  if (bResult != 0) return Fault(20+9);

  uchar bType = PopChar();
  if (bType != 9) return Fault(20+10);

  uchar bSize = PopChar();
  Show(bSize);


  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return Fault(20+11);


  return true;
}
