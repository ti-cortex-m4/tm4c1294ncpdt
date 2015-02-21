/*------------------------------------------------------------------------------
OUT_MINUTE30.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../serial/ports.h"
#include        "../realtime/realtime.h"
#include        "../timedate.h"
#include        "../energy2.h"



void    OutImpCanHouExt(void)
{
uchar   c, j;
uint    w, iwHou;
ulong   dw;
time    ti;

  InitPushPtr();
  w = 0;

  iwHou = bInBuff6*0x100 + bInBuff7;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (iwHou >= wHOURS)
    Result(bRES_BADADDRESS);
  else
  {
    for (j=0; j<bInBuff8; j++)
    {
      dw = DateToHouIndex(tiCurr);
      dw -= iwHou;
      ti = HouIndexToDate(dw);

      Push(&ti, sizeof(time));
      w += sizeof(time);

      if (LoadImpHouFree((wHOURS+iwHardHou-iwHou) % wHOURS) == 0) break;
      else
      {
        for (c=0; c<bCANALS; c++)
        {
          if (iwHou >= wHOURS)
            PushInt(0);
          else
            PushInt( mpwImpHouCan[ PrevSoftHou() ][ c ] );

          w += sizeof(uint);
        }
      }

      iwHou++;
    }

    if (j == bInBuff8)
      OutptrOutBuff(w);
    else
      Result(bRES_BADFLASH);
  }
}
