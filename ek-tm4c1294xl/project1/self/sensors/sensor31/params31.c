/*------------------------------------------------------------------------------
PARAMS31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_factors.h"
//#include "../../memory/mem_energy_spec.h"
//#include "../../memory/mem_profile.h"
//#include "../../serial/ports.h"
//#include "../../serial/ports_devices.h"
//#include "../../serial/monitor.h"
//#include "../../display/display.h"
//#include "../../keyboard/time/key_timedate.h"
//#include "../../time/calendar.h"
//#include "../../time/delay.h"
//#include "../../devices/devices.h"
//#include "../../devices/devices_time.h"
//#include "../../special/special.h"
//#include "automatic31.h"
//#include "device31.h"
//#include "profile31.h"
#include "params31.h"



#ifndef SKIP_N31

static void QueryArrayG(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x0D);

  CodQueryIO(3+110+1, 3+1);
}


static void ReadRealG(void)
{
  PopRealExt_G();
  if (reValue == 2) reValue = 0;
}


static void ReadIntG(void)
{
  reValue = PopIntExtG()/100;
}


static void CalsParS_G(uchar ibP, uchar ibQ)
{
  InitPop(ibP); ReadRealG(); reP = reValue;
  InitPop(ibQ); ReadRealG(); reQ = reValue;
  reQ = sqrt(reP*reP + reQ*reQ);
  reValue = reQ;
}


static void CalsParC_G(uchar ibP, uchar ibQ)
{
  CalsParS_G(ibP, ibQ);
  reValue = (reQ == 0) ? 0 : reP/reQ;
}


bool    ReadParam31(void)
{
  Clear();

  if (fBeginParam == false)
  {
    DelayOff();
    QueryOpenG();

    if (CodInput() != SER_GOODCHECK) return(0);

    if (ReadOpenG() == 0) return(0);
    if (!ExtVersionCod()) return(0);

    DelayOff();
    QueryArrayG();

    if (CodInput() != SER_GOODCHECK) return(0);

    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P1 : InitPop(3+8*0);   ReadRealG(); break;
    case PAR_P2 : InitPop(3+8*1);   ReadRealG(); break;
    case PAR_P3 : InitPop(3+8*2);   ReadRealG(); break;

    case PAR_Q1 : InitPop(3+8*3);   ReadRealG(); break;
    case PAR_Q2 : InitPop(3+8*4);   ReadRealG(); break;
    case PAR_Q3 : InitPop(3+8*5);   ReadRealG(); break;

    case PAR_S1 : CalsParS_G(3+8*0, 3+8*3); break;
    case PAR_S2 : CalsParS_G(3+8*1, 3+8*4); break;
    case PAR_S3 : CalsParS_G(3+8*2, 3+8*5); break;

    case PAR_U1 : InitPop(3+8*6);   ReadRealG(); break;
    case PAR_U2 : InitPop(3+8*7);   ReadRealG(); break;
    case PAR_U3 : InitPop(3+8*8);   ReadRealG(); break;

    case PAR_I1 : InitPop(3+8*9);   ReadRealG(); reValue *= 1000; break;
    case PAR_I2 : InitPop(3+8*10);  ReadRealG(); reValue *= 1000; break;
    case PAR_I3 : InitPop(3+8*11);  ReadRealG(); reValue *= 1000; break;

    case PAR_F1 : InitPop(3+8*12+0);  ReadIntG(); break;
    case PAR_F2 : InitPop(3+8*12+2);  ReadIntG(); break;
    case PAR_F3 : InitPop(3+8*12+4);  ReadIntG(); break;

    case PAR_C1 : CalsParC_G(3+8*0, 3+8*3); break;
    case PAR_C2 : CalsParC_G(3+8*1, 3+8*4); break;
    case PAR_C3 : CalsParC_G(3+8*2, 3+8*5); break;

    default: return(0); break;
   }

  return(1);
}


#endif
