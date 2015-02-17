/*------------------------------------------------------------------------------
OUT_MAX_POWER.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../ports.h"
#include        "../realtime/realtime.h"
#include        "../energy2.h"



void    OutMaxPowDayGrpExt(void)
{
uchar   g;
uint    w;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadPowDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == 1)
      {
        InitPushPtr();
        w = 0;

        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
          {
            Push(&mppoDayGrp[ PrevSoftDay() ][ g ], sizeof(power));
            w += sizeof(power);
          }
        }

        OutptrOutBuff(w);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutMaxPowMonGrpExt(void)
{
uchar   g;
uint    w;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadPowMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == 1)
      {
        InitPushPtr();
        w = 0;

        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
          {
            Push(&mppoMonGrp[ PrevSoftMon() ][ g ], sizeof(power));
            w += sizeof(power);
          }
        }

        OutptrOutBuff(w);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}
