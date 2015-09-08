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
#include "../energy.h"
#include "../energy2.h"
#include "../energy4.h"
#include "out_minute30.h"



static uchar PushPowHouGrp(uchar  ibGrp, uint  iwHhr, uchar  bMultiplier)
{
  if (iwHhr == iwHardHou)
    return PushFloat(GetPowGrpHouCurr(ibGrp, bMultiplier));
  else
    return PushFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibGrp, bMultiplier));
}


void    OutPowHouGrp(bool  fAllGroups, uint  iwHhr, uchar  bMultiplier)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (iwHhr < wHOURS)
    {
      if (LoadImpHou(iwHhr) == 1)
      {
        if (fAllGroups == 1)
        {
          InitPushPtr();
          uint wSize = 0;

          uchar g;
          for (g=0; g<bGROUPS; g++)
          {
            wSize += PushPowHouGrp(g, iwHhr, bMultiplier);
          }

          OutptrOutBuff(wSize);
        }
        else
        {
          if (bInBuff5 < bGROUPS)
          {
            InitPushPtr();
            OutptrOutBuff(PushPowHouGrp(bInBuff5, iwHhr, bMultiplier));
          }
          else Result(bRES_BADADDRESS);
        }
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



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

      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        if (iwHou >= wHOURS)
          PushInt(0);
        else
          PushInt( mpwImpHouCan[ PrevSoftHou() ][ c ] );

        wSize += sizeof(uint);
      }

      iwHou++;
    }

    OutptrOutBuff(wSize);
  }
}
