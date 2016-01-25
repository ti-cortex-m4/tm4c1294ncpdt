/*------------------------------------------------------------------------------
PARAMS31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_factors.h"
//#include "../../memory/mem_energy_spec.h"
//#include "../../memory/mem_profile.h"
#include "../../serial/ports.h"
//#include "../../serial/ports_devices.h"
//#include "../../serial/monitor.h"
//#include "../../display/display.h"
//#include "../../keyboard/time/key_timedate.h"
//#include "../../time/calendar.h"
#include "../../time/delay.h"
//#include "../../devices/devices.h"
//#include "../../devices/devices_time.h"
//#include "../../special/special.h"
#include "automatic31.h"
#include "device31.h"
#include "params31.h"



#ifndef SKIP_N31

static void QueryArray31(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x0D);

  CodQueryIO(3+110+1, 3+1);
}


static void ReadReal31(void)
{
  PopRealExt_31();
  if (reValue == 2) reValue = 0;
}


static void ReadInt31(void)
{
  reValue = PopIntExt31()/100;
}


static void CalsParS_31(uchar ibP, uchar ibQ)
{
  InitPop(ibP); ReadReal31(); reP = reValue;
  InitPop(ibQ); ReadReal31(); reQ = reValue;
  reQ = sqrt(reP*reP + reQ*reQ);
  reValue = reQ;
}


static void CalsParC_31(uchar ibP, uchar ibQ)
{
  CalsParS_31(ibP, ibQ);
  reValue = (reQ == 0) ? 0 : reP/reQ;
}


bool    ReadParam31(void)
{
  Clear();

  if (fBeginParam == false)
  {
    DelayOff();
    QueryOpen31();

    if (CodInput() != SER_GOODCHECK) return(0);

    if (ReadOpen31() == 0) return(0);
    if (!ExtVersionCod()) return(0);

    DelayOff();
    QueryArray31();

    if (CodInput() != SER_GOODCHECK) return(0);

    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P1 : InitPop(3+8*0);   ReadReal31(); break;
    case PAR_P2 : InitPop(3+8*1);   ReadReal31(); break;
    case PAR_P3 : InitPop(3+8*2);   ReadReal31(); break;

    case PAR_Q1 : InitPop(3+8*3);   ReadReal31(); break;
    case PAR_Q2 : InitPop(3+8*4);   ReadReal31(); break;
    case PAR_Q3 : InitPop(3+8*5);   ReadReal31(); break;

    case PAR_S1 : CalsParS_31(3+8*0, 3+8*3); break;
    case PAR_S2 : CalsParS_31(3+8*1, 3+8*4); break;
    case PAR_S3 : CalsParS_31(3+8*2, 3+8*5); break;

    case PAR_U1 : InitPop(3+8*6);   ReadReal31(); break;
    case PAR_U2 : InitPop(3+8*7);   ReadReal31(); break;
    case PAR_U3 : InitPop(3+8*8);   ReadReal31(); break;

    case PAR_I1 : InitPop(3+8*9);   ReadReal31(); reValue *= 1000; break;
    case PAR_I2 : InitPop(3+8*10);  ReadReal31(); reValue *= 1000; break;
    case PAR_I3 : InitPop(3+8*11);  ReadReal31(); reValue *= 1000; break;

    case PAR_F1 : InitPop(3+8*12+0);  ReadInt31(); break;
    case PAR_F2 : InitPop(3+8*12+2);  ReadInt31(); break;
    case PAR_F3 : InitPop(3+8*12+4);  ReadInt31(); break;

    case PAR_C1 : CalsParC_31(3+8*0, 3+8*3); break;
    case PAR_C2 : CalsParC_31(3+8*1, 3+8*4); break;
    case PAR_C3 : CalsParC_31(3+8*2, 3+8*5); break;

    default: return(0); break;
  }

  return(1);
}


#endif
