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
#include "out_max_power.h"



static uchar PushMaxPow(power  *ppo)
{
  uchar wSize = 0;

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    wSize += PushTime((ppo->mpmaMax[t]).tiSelf);
    wSize += PushFloat(ppo->mpmaMax[t].reSelf);
  }

  return wSize;
}



void    OutMaxPowDayGrp(bool  fAllGroups, uchar  ibDay)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (ibDay < bDAYS)
    {
      if (LoadPowDay(ibDay) == true)
      {
        if (fAllGroups == true)
        {
          InitPushPtr();
          uint wSize = 0;

          uchar g;
          for (g=0; g<bGROUPS; g++)
          {
            wSize += PushMaxPow(&mppoDayGrp[ PrevSoftDay() ][ g ]);
          }

          OutptrOutBuff(wSize);
        }
        else
        {
          if (bInBuff5 < bGROUPS)
          {
            InitPushPtr();
            OutptrOutBuff(PushMaxPow(&mppoDayGrp[ PrevSoftDay() ][ bInBuff5 ]));
          }
          else
            Result(bRES_BADADDRESS);
        }
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutMaxPowMonGrp(bool  fAllGroups, uchar  ibMon)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (ibMon < bMONTHS)
    {
      if (LoadPowMon( ibMon ) == true)
      {
        if (fAllGroups == true)
        {
          InitPushPtr();
          uint wSize = 0;

          uchar g;
          for (g=0; g<bGROUPS; g++)
          {
            wSize += PushMaxPow(&mppoMonGrp[ PrevSoftMon() ][ g ]);
          }

          OutptrOutBuff(wSize);
        }
        else
        {
          if (bInBuff5 < bGROUPS)
          {
            InitPushPtr();
            OutptrOutBuff(PushMaxPow(&mppoMonGrp[ PrevSoftMon() ][ bInBuff5 ]));
          }
          else
            Result(bRES_BADADDRESS);
        }
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
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
            wSize += PushMaxPow(&mppoDayGrp[ PrevSoftDay() ][ g ]);
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
            wSize += PushMaxPow(&mppoMonGrp[ PrevSoftMon() ][ g ]);
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
