/*------------------------------------------------------------------------------
OUT_CURRENT,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_extended_1.h"
#include "../../digitals/sensors.h"
#include "../../serial/ports.h"
#include "out_current.h"



void    OutCurrentExt(void)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      PushBool(mpboBase[c]);
      PushLong(mpdwBase[c]);
      PushFloat(mpreBase[c]);
      PushTime(mptiBase[c]);
      PushTime(mptiOffs[c]);

      wSize += 21;
    }
  }

  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      PushFloat(mpdbEsc_S[c]);
      PushTime(mptiEsc_S[c]);
      PushFloat(mpdbLevel[c]);
      PushFloat(mpdbCount[c]);

      wSize += 18;
    }
  }

  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      PushInt(mpwTrue[c]);
      PushInt(mpwFalse[c]);
      PushInt(mpwMore100[c]);
      PushInt(mpwMore1000[c]);
      PushInt(mpwMore10000[c]);
      PushInt(mpwOverflow[c]);
      PushInt(mpwUnderflow[c]);
      PushInt(mpwRepeat[c]);

      wSize += 16;
    }
  }

  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      Push(&mptiBaseOK[c], sizeof(time));
      Push(&mptiBaseError[c], sizeof(time));

      wSize += 12;
    }
  }

  OutptrOutBuff(wSize);
}
