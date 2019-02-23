/*------------------------------------------------------------------------------
params34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../digitals/params/params2.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "device34.h"
#include "params34.h"



static void QueryParam34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x66);
  PushChar(0);
  PushChar(0x80);
  PushChar(0);
  PushChar(4*7); // 1C

  QueryIO(3+4*7*4+2, 6+2); // 272
}


static float2 ReadValue34(uchar  i)
{
  InitPop(3+4*i);
  return GetFloat2(PopFloat34(), true);
}


float2  ReadParam34(void)
{
  Clear();

  if (fBeginParam == false)
  {
    DelayOff();
    QueryParam34();

    if (Input() != SER_GOODCHECK) GetFloat2Error();
    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_U1 : return ReadValue34(0);
    case PAR_U2 : return ReadValue34(1);
    case PAR_U3 : return ReadValue34(2);
    case PAR_U  : return ReadValue34(3);

    default: return GetFloat2Error();
  }
}


