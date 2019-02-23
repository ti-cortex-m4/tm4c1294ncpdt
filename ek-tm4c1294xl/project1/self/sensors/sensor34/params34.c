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



static float        mpeValues[28];



static void QueryParam1(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x66);
  PushChar(0);
  PushChar(0x80);
  PushChar(0);
  PushChar(4*7);

  QueryIO(3+4*7*4+2, 6+2);
}


static void QueryParam2(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x66);
  PushChar(0x01);
  PushChar(0x98);
  PushChar(0);
  PushChar(4*1);

  QueryIO(3+4*1*4+2, 6+2);
}



static void SetValue(uchar  ibValue, uchar  i, uint  wMul)
{
  ASSERT(ibValue < 28);
  InitPop(3+4*i);
  mpeValues[ibValue] = PopFloat34()*wMul;
}


static float2 GetValue(uchar  ibValue)
{
  ASSERT(ibValue < 28);
  return GetFloat2(mpeValues[ibValue], true);
}


float2  ReadParam34(void)
{
  Clear();

  if (fBeginParam == false)
  {
    DelayOff();
    QueryParam1();

    if (Input() != SER_GOODCHECK) GetFloat2Error();

    SetValue(0,  0,  1);
    SetValue(1,  1,  1);
    SetValue(2,  2,  1);
    SetValue(3,  3,  1);

    SetValue(4,  8,  1000);
    SetValue(5,  9,  1000);
    SetValue(6,  10, 1000);
    SetValue(7,  11, 1000);

    SetValue(8,  12, 1);
    SetValue(9,  13, 1);
    SetValue(10, 14, 1);
    SetValue(11, 15, 1);

    SetValue(12, 16, 1);
    SetValue(13, 17, 1);
    SetValue(14, 18, 1);
    SetValue(15, 19, 1);

    SetValue(16, 20, 1);
    SetValue(17, 21, 1);
    SetValue(18, 22, 1);
    SetValue(19, 23, 1);

    SetValue(20, 24, 1);
    SetValue(21, 25, 1);
    SetValue(22, 26, 1);
    SetValue(23, 27, 1);


    DelayOff();
    QueryParam2();

    if (Input() != SER_GOODCHECK) GetFloat2Error();

    SetValue(24,  0,  1);
    SetValue(25,  1,  1);
    SetValue(26,  2,  1);
    SetValue(27,  3,  1);


    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_U1 : return GetValue(0);
    case PAR_U2 : return GetValue(1);
    case PAR_U3 : return GetValue(2);
    case PAR_U  : return GetValue(3);

    case PAR_I1 : return GetValue(4);
    case PAR_I2 : return GetValue(5);
    case PAR_I3 : return GetValue(6);
    case PAR_I  : return GetValue(7);

    case PAR_P1 : return GetValue(8);
    case PAR_P2 : return GetValue(9);
    case PAR_P3 : return GetValue(10);
    case PAR_P  : return GetValue(11);

    case PAR_Q1 : return GetValue(12);
    case PAR_Q2 : return GetValue(13);
    case PAR_Q3 : return GetValue(14);
    case PAR_Q  : return GetValue(15);

    case PAR_S1 : return GetValue(16);
    case PAR_S2 : return GetValue(17);
    case PAR_S3 : return GetValue(18);
    case PAR_S  : return GetValue(19);

    case PAR_F1 : return GetValue(20);
    case PAR_F2 : return GetValue(21);
    case PAR_F3 : return GetValue(22);
    case PAR_F  : return GetValue(23);

    case PAR_C1 : return GetValue(24);
    case PAR_C2 : return GetValue(25);
    case PAR_C3 : return GetValue(26);
    case PAR_C  : return GetValue(27);

    default: return GetFloat2Error();
  }
}


