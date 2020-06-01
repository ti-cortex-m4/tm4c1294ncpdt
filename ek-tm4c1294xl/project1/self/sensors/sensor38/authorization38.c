/*------------------------------------------------------------------------------
authorization38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_common.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "io38.h"
#include "bits2.h"
#include "device38.h"
#include "hash38.h"
#include "authorization38.h"



void    QueryAuthorizationRequest38(void)
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


ulong   ReadAuthorizationRequest38(void)
{
  uint64_t ddw = 0;
  pucDecodeBitArr((uchar *) &ddw, InBuffPtr(10+1));

  return ddw % 0x100000000;
}



void    QueryAuthorizationResponse38(ulong  random)
{
  uchar password[16+1];
  password[0] = 'y';
  password[1] = 'y';
  password[2] = 'y';
  password[3] = 0;

  uchar password_size = 3;

  ulong dw = Hash38(&password[0], password_size, random);


  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(7); // ?
  PushChar(0);
  PushChar(1);

  Query38(250, 21);
}


uchar   ReadAuthorizationResponse38(void)
{
  return InBuff(11);
}



#ifdef MONITOR_38

void    RunAuthorization38(void)
{
  QueryAuthorizationRequest38();
  if (Input38() != SER_GOODCHECK) { MonitorString("\n error 1"); return; }

  ulong random = ReadAuthorizationRequest38();

  QueryAuthorizationResponse38(random);
  if (Input38() != SER_GOODCHECK) { MonitorString("\n error 2"); return; }

  uchar b = ReadAuthorizationResponse38();
  MonitorString("authorization="); MonitorCharDec(b);
}

#endif
