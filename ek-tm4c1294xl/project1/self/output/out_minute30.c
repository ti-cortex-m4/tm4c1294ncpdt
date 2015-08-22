/*------------------------------------------------------------------------------
OUT_MINUTE30,C


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
  InitPushPtr();
  uint wSize = 0;

  uint iwHou = bInBuff6*0x100 + bInBuff7;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (iwHou >= wHOURS)
    Result(bRES_BADADDRESS);
  else
  {
    uchar i;
    for (i=0; i<bInBuff8; i++)
    {
      ulong dw = DateToHouIndex(tiCurr);
      dw -= iwHou;
      time ti = HouIndexToDate(dw);

      wSize += PushTime(ti);

      if (LoadImpHouFree((wHOURS+iwHardHou-iwHou) % wHOURS) == false) { Result(bRES_BADFLASH); return; }
      else
      {
        uchar c;
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
