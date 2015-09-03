/*------------------------------------------------------------------------------
EXTENDED_3_OUT.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_extended_3.h"
#include "../../serial/ports.h"
#include "extended_3.h"
#include "extended_3_out.h"



void    OutExtended30(void)
{
  InitPushCRC();
  PushChar(boExt3Flag);
  Push(&mpboEventFirst, sizeof(mpboEventFirst));
  Push(&mpboEventA, sizeof(mpboEventA));
  Push(&mpboEventB, sizeof(mpboEventB));
  Output(1+64+32+32);
}


void    OutExtended31(void)
{
  uchar j = bInBuff6;
  if (j > 3) 
    Result(bRES_BADADDRESS);
  else
  {
    InitPushPtr();
    uint wSize = 0;

    ulong dw;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      switch (j)
      {
        case 0: dw = mpdwEventDevice[c]; break;
        case 1: dw = mpdwEventPhase1[c]; break;
        case 2: dw = mpdwEventPhase2[c]; break;
        case 3: dw = mpdwEventPhase3[c]; break;
        default: ASSERT(false);
      }

      Push(&dw, sizeof(ulong));
      PushTime(EveIndexToDate(dw));

      wSize += 10;
    }

    OutptrOutBuff(wSize);
  }
}

