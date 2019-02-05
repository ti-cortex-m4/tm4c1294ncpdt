/*------------------------------------------------------------------------------
DEVICE34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../time/unix_time.h"
#include "device34.h"



#ifndef SKIP_34

void    QueryTime34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x64);
  PushChar(0x00);
  PushChar(0x46);
  PushChar(0x00);
  PushChar(0x09);

  QueryIO(3+18+2, 6+2);
}


time    ReadTime34(void)
{
  InitPop(3);
  return UnixTimeToDate(PopLongLtl());
}



void    QueryEngAbs34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x67);
  PushChar(0x00);
  PushChar(0xFF);
  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  QueryIO(3+81+2, 8+2);
}


void    ReadEng34(void)
{
  InitPop(4);

  uchar i;
  for (i=0; i<MAX_LINE_N34; i++)
  {
    mpddwChannels34[i] = PopLongLtl();
    mpddwChannels34[i] += 0x100000000*PopLongLtl();
  }
}

#endif

