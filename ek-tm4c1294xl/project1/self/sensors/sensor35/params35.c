/*------------------------------------------------------------------------------
params35.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../digitals/params/params2.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "device35.h"
#include "params35.h"



#ifndef SKIP_35

void    QueryParam35_P(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddress35();

  PushChar(0xD0);
  PushChar(0x01);
  PushChar(0x32);

  Query35(100+14, 15);
}


void    ReadParam35_P(void)
{
  InitPop(9);

  ulong dw = PopChar();
  dw += PopChar()*100;
  dw += PopChar()*10000;

  reValue = dw*10;
}


bool    ReadParam35(void)
{
  Clear();

  QueryParam35_P();
  if (InputS() != SER_GOODCHECK) return(0);

  switch (diCurr.ibLine)
  {
    case PAR_P : ReadParam35_P(); break;

    default: return(0);
  }

  return(1);
}

#endif
