/*------------------------------------------------------------------------------
OUT_FACTORS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"



void    OutAllFactors(void)
{
  if (bInBuff5 < bCANALS)
  {
    InitPushCRC();

    PushFloat(mpreTransEng[bInBuff5]);
    PushFloat(mpreTransCnt[bInBuff5]);
    PushFloat(mprePulseHou[bInBuff5]);
    PushFloat(mprePulseMnt[bInBuff5]);

    Output(sizeof(float)*4);
  }
  else Result(bRES_BADADDRESS);
}
