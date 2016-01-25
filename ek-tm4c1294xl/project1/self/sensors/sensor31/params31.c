/*------------------------------------------------------------------------------
PARAMS31.C


------------------------------------------------------------------------------*/

#include <math.h>
#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "automatic31.h"
#include "device31.h"
#include "params31.h"



#ifndef SKIP_N31

extern  bool                    fBeginParam;



static void QueryArray31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x0D); // "чтение мощности, напряжения и тока"

  Query31(3+110+1, 3+1);
}


static float2 ReadFloat(uint wMul)
{
  return GetFloat2(PopDouble31()*wMul, true);
}


static float2 ReadInt(void)
{
  return GetFloat2(PopIntLtl()/100, true);
}


static float2 CalcParamS(uchar ibP, uchar ibQ)
{
  InitPop(ibP);
  float flP = PopDouble31();

  InitPop(ibQ);
  float flQ = PopDouble31();

  float flS = sqrtf(flP*flP + flQ*flQ);

  return GetFloat2(flS, true);
}


static float2 CalcParamC(uchar ibP, uchar ibQ)
{
  InitPop(ibP);
  float flP = PopDouble31();

  InitPop(ibQ);
  float flQ = PopDouble31();

  float flS = sqrtf(flP*flP + flQ*flQ);
  float flC = (flS == 0) ? 0 : flP/flS;

  return GetFloat2(flC, true);
}


float2  ReadParam31(void)
{
  Clear();

  if (fBeginParam == false)
  {
    DelayOff();
    QueryOpen31();

    if (Input31() != SER_GOODCHECK) return GetFloat2Error();

    if (ReadOpen31() == 0) return GetFloat2Error();
    if (!ExtVersion31()) return GetFloat2Error();

    DelayOff();
    QueryArray31();

    if (Input31() != SER_GOODCHECK) return GetFloat2Error();

    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P1 : InitPop(3+8*0); return ReadFloat(1);
    case PAR_P2 : InitPop(3+8*1); return ReadFloat(1);
    case PAR_P3 : InitPop(3+8*2); return ReadFloat(1);

    case PAR_Q1 : InitPop(3+8*3); return ReadFloat(1);
    case PAR_Q2 : InitPop(3+8*4); return ReadFloat(1);
    case PAR_Q3 : InitPop(3+8*5); return ReadFloat(1);

    case PAR_S1 : return CalcParamS(3+8*0, 3+8*3);
    case PAR_S2 : return CalcParamS(3+8*1, 3+8*4);
    case PAR_S3 : return CalcParamS(3+8*2, 3+8*5);

    case PAR_U1 : InitPop(3+8*6); return ReadFloat(1);
    case PAR_U2 : InitPop(3+8*7); return ReadFloat(1);
    case PAR_U3 : InitPop(3+8*8); return ReadFloat(1);

    case PAR_I1 : InitPop(3+8*9);  return ReadFloat(1000);
    case PAR_I2 : InitPop(3+8*10); return ReadFloat(1000);
    case PAR_I3 : InitPop(3+8*11); return ReadFloat(1000);

    case PAR_F1 : InitPop(3+8*12+0); return ReadInt();
    case PAR_F2 : InitPop(3+8*12+2); return ReadInt();
    case PAR_F3 : InitPop(3+8*12+4); return ReadInt();

    case PAR_C1 : return CalcParamC(3+8*0, 3+8*3);
    case PAR_C2 : return CalcParamC(3+8*1, 3+8*4);
    case PAR_C3 : return CalcParamC(3+8*2, 3+8*5);

    default: return GetFloat2Error();
  }
}


#endif
