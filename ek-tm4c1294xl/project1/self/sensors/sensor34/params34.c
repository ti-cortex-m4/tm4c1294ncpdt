/*------------------------------------------------------------------------------
params34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_digitals.h"
//#include "../../serial/ports.h"
//#include "../../display/display.h"
//#include "../../time/delay.h"
//#include "automatic33.h"
//#include "device33.h"
#include "params34.h"



static void QueryParam34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x66);
  PushIntLtl(128+0);
  PushChar(0);
  PushChar(4*7);

  QueryIO(3+28+2, 6+2);
}


static float2 ReadValue34(uchar  i)
{
  InitPop(3+4*i);
  return GetFloat2(PopFloat(), true);
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


