/*------------------------------------------------------------------------------
OUT_CURRENT2,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_realtime.h"
#include "../../digitals/sensors.h"
#include "../../digitals/digitals.h"
#include "../../serial/ports.h"
#include "../../energy.h"
#include "out_current2.h"



void    OutEng3MinDataExt(void)
{
  InitPushPtr();
  uint wSize = 0;

  uchar i;
  for (i=0; i<2+bCANALS/8; i++) PushChar(InBuff(4+i));

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      float fl;

      if (GetDigitalDevice(c) == 0)
        fl = GetCntCurrImp(c);
      else if (mpboEnblCan[c] == false)
        fl = 0;
      else
        fl = mpdbValueCntHou[c] * mpdwBase[c];

      wSize += PushFloat(fl);
    }
  }

  OutptrOutBuff(2+bCANALS/8+wSize);
}


void    OutEng3MinTimeExt(void)
{

  InitPushPtr();
  uint wSize = 0;

  uchar i;
  for (i=0; i<2+bCANALS/8; i++) PushChar(InBuff(4+i));

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      if (GetDigitalDevice(c) == 0)
      {
        Push(&tiCurr, sizeof(time));
        Push(&tiCurr, sizeof(time));
      }
      else
      {
        Push(&mptiBase[c], sizeof(time));
        Push(&mptiOffs[c], sizeof(time));
      }

      wSize += 2*sizeof(time);
    }
  }

  OutptrOutBuff(2+bCANALS/8+wSize);
}

