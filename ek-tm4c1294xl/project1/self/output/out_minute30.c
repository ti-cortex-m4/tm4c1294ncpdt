/*------------------------------------------------------------------------------
OUT_MINUTE30.C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../energy2.h"



void    OutImpCanHouExt(void)
{
uchar   c, j;
uint    wSize, iwHou;
ulong   dw;
time    ti;

  InitPushPtr();
  wSize = 0;

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
      wSize += sizeof(time);

      if (LoadImpHouFree((wHOURS+iwHardHou-iwHou) % wHOURS) == false) { Result(bRES_BADFLASH); return; }
      else
      {
        for (c=0; c<bCANALS; c++)
        {
          if (iwHou >= wHOURS)
            PushInt(0);
          else
            PushInt( mpwImpHouCan[ PrevSoftHou() ][ c ] );

          wSize += sizeof(uint);
        }
      }

      iwHou++;
    }

    OutptrOutBuff(wSize);
  }
}
