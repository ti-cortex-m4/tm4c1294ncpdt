/*------------------------------------------------------------------------------
EXTENDED_3_OUT!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_extended_3.h"
#include "../../serial/ports.h"
#include "extended_3.h"
#include "extended_3_out.h"



void    OutExtended30(void)
{
  InitPushCRC();
  PushBool(fExt3Flag);
  Push(&mpfEventStart, sizeof(mpfEventStart));
  Push(&mpfEventFlagA, sizeof(mpfEventFlagA));
  Push(&mpfEventFlagB, sizeof(mpfEventFlagB));
  Output(1+64+32+32);
}


void    OutExtended31(void)
{
  uchar i = bInBuff6;
  if (i > 3)
    Result(bRES_BADADDRESS);
  else
  {
    InitPushPtr();
    uint wSize = 0;

    ulong dw;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      switch (i)
      {
        case 0: dw = mpdwEventDevice[c]; break;
        case 1: dw = mpdwEventPhase1[c]; break;
        case 2: dw = mpdwEventPhase2[c]; break;
        case 3: dw = mpdwEventPhase3[c]; break;
        default: ASSERT(false);
      }

      wSize += PushLong(dw);
      wSize += PushTime(EventIndexToDate(dw));
    }

    OutptrOutBuff(wSize);
  }
}
