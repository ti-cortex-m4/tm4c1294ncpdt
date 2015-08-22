/*------------------------------------------------------------------------------
OUT_CURRENT2,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_current.h"
#include "../memory/mem_extended_1.h"
#include "../memory/mem_ports.h"
#include "../digitals/sensors.h"
#include "../serial/ports.h"
#include "out_current2.h"



void    OutEng3MinDataExt(void)
{
uchar   i;
uint    wSize;

  InitPushPtr();
  for (i=0; i<2+bCANALS/8; i++) PushChar(InBuff(4+i));

  wSize = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      if (GetDigitalDevice(i) == 0)
        reBuffA = *PGetCounterOld(i);
      else if (mpboEnblCan[i] == boFalse)
        reBuffA = 0;
      else
        reBuffA = *PGetCanReal(mpreValueCntHou,i) * mpdwBase[i];

      PushReal();
      wSize += sizeof(real);
    }
  }

  OutptrOutBuff(2+bCANALS/8+wSize);
}


void    OutEng3MinTimeExt(void)
{
uchar   i;
uint    wSize;

  InitPushPtr();
  for (i=0; i<2+bCANALS/8; i++) PushChar(InBuff(4+i));

  wSize = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      if (GetDigitalDevice(i) == 0)
      {
        Push(&tiCurr, sizeof(time));
        Push(&tiCurr, sizeof(time));
      }
      else
      {
        Push(&mptiBase[i], sizeof(time));
        Push(&mptiOffs[i], sizeof(time));
      }

      wSize += 2*sizeof(time);
    }
  }

  OutptrOutBuff(2+bCANALS/8+wSize);
}

