/*------------------------------------------------------------------------------
PARAMS33.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "automatic33.h"
#include "device33.h"
#include "params33.h"



#ifndef SKIP_33

static void QueryPower33(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x0F); // "получить текущую мощность"

  Query33(3+4+1, 3+1);
}


float2  ReadParam33(void)
{
  Clear();


  DelayOff();
  QueryOpen33();

  if (Input33() != SER_GOODCHECK) return GetFloat2Error();

  if (ReadOpen33() == 0) return GetFloat2Error();

  DelayOff();
  QueryPower33();

  if (Input33() != SER_GOODCHECK) return GetFloat2Error();


  switch (diCurr.ibLine)
  {
    case PAR_P : {
                   InitPop(3);
                   ulong dw = PopLong33();
                   return GetFloat2(dw/1000, true);
                 }

    default: return GetFloat2Error();
  }
}

#endif
