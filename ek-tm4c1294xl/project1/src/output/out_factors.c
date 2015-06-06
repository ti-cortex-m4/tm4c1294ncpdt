/*------------------------------------------------------------------------------
OUT_FACTORS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "out_factors.h"



void    OutAllFactors(bool  fDouble)
{
  if (bInBuff5 < bCANALS)
  {
    InitPushCRC();
    uint wSize = 0;

    wSize += PushFloatOrDouble(mpdbTransEng[bInBuff5], fDouble);
    wSize += PushFloatOrDouble(mpdbTransCnt[bInBuff5], fDouble);
    wSize += PushFloatOrDouble(mpdbPulseHou[bInBuff5], fDouble);
    wSize += PushFloatOrDouble(mpdbPulseMnt[bInBuff5], fDouble);

    Output(wSize);
  }
  else Result(bRES_BADADDRESS);
}
