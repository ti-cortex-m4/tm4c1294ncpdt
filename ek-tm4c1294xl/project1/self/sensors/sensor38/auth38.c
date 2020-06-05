/*------------------------------------------------------------------------------
auth38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_common.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "io38.h"
#include "dff.h"
#include "device38.h"
#include "crc38.h"
#include "auth38.h"



extern int usprintf(char * restrict s, const char * restrict format, ...);



static ulong            dwRandom;



void    QueryAuthRequest38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(6); // GET_INFO
  PushChar(0x00);

  PushChar(24); // 0x18

  Query38(250, 14);
}


void    ReadAuthRequest38(void)
{
  int64_t ddw = 0;
  DffDecodePositive(InBuffPtr(10+1), &ddw);

  dwRandom = ddw % 0x100000000;
}



void    QueryAuthResponse38(void)
{
static uchar mbPass[10*2];

  memset(&mbPass, 0, sizeof(mbPass));
  uchar bPassSize = usprintf((char *)&mbPass, "%u" ,mpdwAddress2[diCurr.bAddress-1]);

  ulong dw = Crc38(&mbPass[0], bPassSize, dwRandom);


  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(7); // PERFORM_ACTION
  PushChar(0);
  PushChar(1);

  int n = EncodeInt(dw, OutBuffPtr(11));

  *OutBuffPtr(11+n-1) |= 0x80;

  InitPush(11+n);
  PushChar(0xF1);
  PushChar(0x04);

  Query38(250, 11+n+3);
}


uchar   ReadAuthResponse38(void)
{
  return InBuff(11);
}



#ifdef MONITOR_38

void    RunAuth38(void)
{
  QueryAuthRequest38();
  if (Input38() != SER_GOODCHECK) { MonitorString("\n error 1"); return; }

  ReadAuthRequest38();
  MonitorString("\n random="); MonitorLongHex(dwRandom);

  QueryAuthResponse38();
  if (Input38() != SER_GOODCHECK) { MonitorString("\n error 2"); return; }

  uchar bAuth = ReadAuthResponse38();
  MonitorString("\n authorization="); MonitorCharDec(bAuth);
}

#endif
