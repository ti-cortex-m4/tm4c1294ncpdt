/*------------------------------------------------------------------------------
OUT_CURRENT.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_current.h"
#include        "../memory/mem_esc.h"
#include        "../memory/mem_ports.h"
#include        "../digitals/sensors.h"
#include        "../serial/ports.h"



void    OutCurrentExt(void)
{
uchar   i;
uint    w;

  InitPushPtr();
  w = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      PushChar(mpboBase[i]);
      PushLong(mpdwBase[i]);
      Push(&mpreBase[i], sizeof(real));
      Push(&mptiBase[i], sizeof(time));
      Push(&mptiOffs[i], sizeof(time));

      w += 21;
    }
  }

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      Push(&mpreEsc_S[i], sizeof(real));
      Push(&mptiEsc_S[i], sizeof(time));
      Push(&mpreLevelDiv[i], sizeof(real));
      Push(&mpreCount[i], sizeof(real));

      w += 18;
    }
  }

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      PushInt(mpwTrue[i]);
      PushInt(mpwFalse[i]);
      PushInt(mpwMore100[i]);
      PushInt(mpwMore1000[i]);
      PushInt(mpwMore10000[i]);
      PushInt(mpwOverflow[i]);
      PushInt(mpwUnderflow[i]);
      PushInt(mpwRepeat[i]);

      w += 16;
    }
  }

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      Push(&mptiBaseOK[i], sizeof(time));
      Push(&mptiBaseError[i], sizeof(time));

      w += 12;
    }
  }

  OutptrOutBuff(w);
}
