/*------------------------------------------------------------------------------
authorization38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "io38.h"
#include "device38.h"
#include "authorization38.h"



void    QueryAuthorizationRequest38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0A); // GET_DATA_SINGLE_EX
  PushChar(0x00);

  PushChar(0x01); // A+
  PushChar(0x02);
  PushChar(0x00);

  Query38(250, 25);
}


uint    ReadAuthorizationRequest38(uchar  ibInBuff)
{
  uint64_t ddw = DffDecodeLong64(&mpbInBuff3[ibInBuff]); // TODO

  ulong dw = ddw % 0x100000000;
  MonitorString("\n"); MonitorLongHex(dw);
  MonitorString("\n"); MonitorLongDec(dw);
  MonitorString("\n"); MonitorLongDecimal4(dw);

  return ddw;
}


#ifdef MONITOR_38

void    RunAuthorization38(void)
{
  QueryAuthorizationRequest38();
  if (Input38() != SER_GOODCHECK) { MonitorString("\n error 1"); return; }

  tiValue38 = ReadAuthorizationRequest38();
}

#endif