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
  PushChar(4*7);

  QueryIO(3+4*7*4+2, 6+2); // 272
}


static float2 ReadValue34(uchar  i, uint  wMul)
{
  InitPop(3+4*i);
  return GetFloat2(PopFloat34()*wMul, true);
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
    case PAR_U1 : return ReadValue34(0, 1);
    case PAR_U2 : return ReadValue34(1, 1);
    case PAR_U3 : return ReadValue34(2, 1);
    case PAR_U  : return ReadValue34(3, 1);

    case PAR_I1 : return ReadValue34(8, 1000);
    case PAR_I2 : return ReadValue34(9, 1000);
    case PAR_I3 : return ReadValue34(10, 1000);
    case PAR_I  : return ReadValue34(11, 1000);

    case PAR_P1 : return ReadValue34(12, 1);
    case PAR_P2 : return ReadValue34(13, 1);
    case PAR_P3 : return ReadValue34(14, 1);
    case PAR_P  : return ReadValue34(15, 1);

    case PAR_Q1 : return ReadValue34(16, 1);
    case PAR_Q2 : return ReadValue34(17, 1);
    case PAR_Q3 : return ReadValue34(18, 1);
    case PAR_Q  : return ReadValue34(19, 1);

    case PAR_S1 : return ReadValue34(20, 1);
    case PAR_S2 : return ReadValue34(21, 1);
    case PAR_S3 : return ReadValue34(22, 1);
    case PAR_S  : return ReadValue34(23, 1);

    default: return GetFloat2Error();
  }
}


