/*------------------------------------------------------------------------------
PARAMS32.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "automatic32.h"
#include "device32.h"
#include "params32.h"



#ifndef SKIP_32


static void QueryPower32(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x0F); // "получить текущую мощность"

  Query32(3+4+1, 3+1);
}


float2  ReadParam32(void)
{
  Clear();


  DelayOff();
  QueryOpen32();

  if (Input32() != SER_GOODCHECK) return GetFloat2Error();

  if (ReadOpen32() == 0) return GetFloat2Error();

  DelayOff();
  QueryPower32();

  if (Input32() != SER_GOODCHECK) return GetFloat2Error();


  switch (diCurr.ibLine)
  {
    case PAR_P : {
                   InitPop(3);
                   ulong dw = PopLongBig();
                   return GetFloat2(dw/1000, true);
                 }

    default: return GetFloat2Error();
  }
}


#endif
