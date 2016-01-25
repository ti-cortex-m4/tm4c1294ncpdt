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

extern  float                   reValue;



static void QueryArray31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x0D);

  Query31(3+110+1, 3+1);
}


static void ReadFloat(void)
{
  reValue = PopDouble31();
}


static void ReadInt(void)
{
  reValue = PopIntLtl()/100;
}


static void CalcParamS(uchar ibP, uchar ibQ)
{
  InitPop(ibP);
  ReadFloat();
  float flP = reValue;

  InitPop(ibQ);
  ReadFloat();
  float flQ = reValue;

  reValue = sqrtf(flP*flP + flQ*flQ);
}


static void CalcParamC(uchar ibP, uchar ibQ)
{
  InitPop(ibP);
  ReadFloat();
  float flP = reValue;

  InitPop(ibQ);
  ReadFloat();
  float flQ = reValue;

  reValue = (flQ == 0) ? 0 : flP/flQ;
}


bool    ReadParam31(void)
{
  Clear();

  if (fBeginParam == false)
  {
    DelayOff();
    QueryOpen31();

    if (Input31() != SER_GOODCHECK) return(0);

    if (ReadOpen31() == 0) return(0);
    if (!ExtVersion31()) return(0);

    DelayOff();
    QueryArray31();

    if (Input31() != SER_GOODCHECK) return(0);

    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P1 : InitPop(3+8*0);   ReadFloat(); break;
    case PAR_P2 : InitPop(3+8*1);   ReadFloat(); break;
    case PAR_P3 : InitPop(3+8*2);   ReadFloat(); break;

    case PAR_Q1 : InitPop(3+8*3);   ReadFloat(); break;
    case PAR_Q2 : InitPop(3+8*4);   ReadFloat(); break;
    case PAR_Q3 : InitPop(3+8*5);   ReadFloat(); break;

    case PAR_S1 : CalcParamS(3+8*0, 3+8*3); break;
    case PAR_S2 : CalcParamS(3+8*1, 3+8*4); break;
    case PAR_S3 : CalcParamS(3+8*2, 3+8*5); break;

    case PAR_U1 : InitPop(3+8*6);   ReadFloat(); break;
    case PAR_U2 : InitPop(3+8*7);   ReadFloat(); break;
    case PAR_U3 : InitPop(3+8*8);   ReadFloat(); break;

    case PAR_I1 : InitPop(3+8*9);   ReadFloat(); reValue *= 1000; break;
    case PAR_I2 : InitPop(3+8*10);  ReadFloat(); reValue *= 1000; break;
    case PAR_I3 : InitPop(3+8*11);  ReadFloat(); reValue *= 1000; break;

    case PAR_F1 : InitPop(3+8*12+0);  ReadInt(); break;
    case PAR_F2 : InitPop(3+8*12+2);  ReadInt(); break;
    case PAR_F3 : InitPop(3+8*12+4);  ReadInt(); break;

    case PAR_C1 : CalcParamC(3+8*0, 3+8*3); break;
    case PAR_C2 : CalcParamC(3+8*1, 3+8*4); break;
    case PAR_C3 : CalcParamC(3+8*2, 3+8*5); break;

    default: return(0);
  }

  return(1);
}


#endif
