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

    PushFloat(mpdbTransEng[bInBuff5]);
    PushFloat(mpdbTransCnt[bInBuff5]);
    PushFloat(mpdbPulseHou[bInBuff5]);
    PushFloat(mpdbPulseMnt[bInBuff5]);

    Output(sizeof(float)*4);
  }
  else Result(bRES_BADADDRESS);
}
