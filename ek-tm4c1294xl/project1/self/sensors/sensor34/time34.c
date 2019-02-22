/*------------------------------------------------------------------------------
time34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "time34.h"



void    QueryCorrectTime34(int32_t  dwSecond)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x65);
  PushChar(0x00);
  PushChar(0x4F);
  PushChar(0x00);
  PushChar(0x04);
  PushChar(0x08);

  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);

  PushLongLtl(dwSecond);

  QueryIO(3+3+2, 7+4+4+2);
}


bool    ReadCorrectTime34(void)
{
  return (InBuff(1) & 0x80) == 0;
}
