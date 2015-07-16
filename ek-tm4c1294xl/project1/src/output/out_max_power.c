/*------------------------------------------------------------------------------
OUT_MAX_POWER.C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../energy2.h"



void    PushMaxPow(power  *ppo)
{
uchar   t;

	for (t=0; t<bTARIFFS; t++)
	{
    PushTime((ppo->mpmaMax[t]).tiSelf);
    PushFloat(ppo->mpmaMax[t].reSelf);
	}
}



void    OutMaxPowDayGrpExt(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadPowDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == true)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
          {
          	PushMaxPow(&mppoDayGrp[ PrevSoftDay() ][ g ]);
            wSize += (sizeof(time) + sizeof(real))*bTARIFFS;
          }
        }

        OutptrOutBuff(wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutMaxPowMonGrpExt(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadPowMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == true)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
          {
          	PushMaxPow(&mppoMonGrp[ PrevSoftMon() ][ g ]);
            wSize += (sizeof(time) + sizeof(real))*bTARIFFS;
          }
        }

        OutptrOutBuff(wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}
