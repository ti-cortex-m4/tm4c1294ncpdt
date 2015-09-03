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
uchar   i,j;

  j = bInBuff6;
  if (j > 3) 
    Result(bRES_BADADDRESS);
  else {  
    InitPushPtr();
    wBuffD = 0;

    for (i=0; i<bCANALS; i++) {
      switch (j) {
        case 0: dwBuffC = mpdwEventDevice[i]; break;
        case 1: dwBuffC = mpdwEventPhase1[i]; break;
        case 2: dwBuffC = mpdwEventPhase2[i]; break;
        case 3: dwBuffC = mpdwEventPhase3[i]; break;
      }

      Push(&dwBuffC, sizeof(ulong));
      EveIndexToDate(dwBuffC);
      Push(&tiAlt, sizeof(time));

      wBuffD += 10;
    }

    OutptrOutBuff(wBuffD);
  }
}

