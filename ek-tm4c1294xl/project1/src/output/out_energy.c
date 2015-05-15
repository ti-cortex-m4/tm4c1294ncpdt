/*------------------------------------------------------------------------------
OUT_ENERGY.C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../energy.h"
#include "../energy2.h"
#include "out_energy.h"



static uint PushEngDayGrp(uchar  ibGrp, bool  fSum)
{
uchar  t;
float  re;

  uint wSize = 0;

  if (fSum == 0)
  {
    for (t=0; t<bTARIFFS; t++)
    {
      re = GetGrpImp2FloatEng(mpimDayCan[ PrevSoftDay() ], ibGrp, 0x01 << t);

      wSize += sizeof(float);
      PushFloat(re);
    }
  }
  else
  {
    re = 0;
    for (t=0; t<bTARIFFS; t++)
      re += GetGrpImp2FloatEng(mpimDayCan[ PrevSoftDay() ], ibGrp, 0x01 << t);

    wSize += sizeof(float);
    PushFloat(re);
  }

  return wSize;
}


static uint PushEngMonGrp(uchar  ibGrp, bool  fSum)
{
uchar  t;
float  re;

  uint wSize = 0;

  if (fSum == 0)
  {
    for (t=0; t<bTARIFFS; t++)
    {
      re = GetGrpImp2FloatEng(mpimMonCan[ PrevSoftMon() ], ibGrp, 0x01 << t);

      wSize += sizeof(float);
      PushFloat(re);
    }
  }
  else
  {
    re = 0;
    for (t=0; t<bTARIFFS; t++)
      re += GetGrpImp2FloatEng(mpimMonCan[ PrevSoftMon() ], ibGrp, 0x01 << t);

    wSize += sizeof(float);
    PushFloat(re);
  }

  return wSize;
}



void    OutEngDayGrpExt(bool  fDouble)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadImpDay((bDAYS+ibHardDay-bInBuff6) % bDAYS) == TRUE)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
            wSize += PushEngDayGrp(g, false);
        }

        OutptrOutBuff(wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutEngDayGrpSum(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadImpDay((bDAYS+ibHardDay-bInBuff6) % bDAYS) == TRUE)
      {
        InitPushPtr();

        uchar i;
        for (i=0; i<3+bGROUPS/8; i++)
          PushChar(InBuff(4+i));

        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
            wSize += PushEngDayGrp(g, true);
        }

        OutptrOutBuff(3+bGROUPS/8+wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



void    OutEngMonGrpExt(bool  fDouble)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadImpMon((bMONTHS+ibHardMon-bInBuff6) % bMONTHS) == TRUE)
      {
        InitPushPtr();

        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
            wSize += PushEngMonGrp(g, false);
        }

        OutptrOutBuff(wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutEngMonGrpSum(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadImpMon((bMONTHS+ibHardMon-bInBuff6) % bMONTHS) == TRUE)
      {
        InitPushPtr();

        uchar i;
        for (i=0; i<3+bGROUPS/8; i++)
          PushChar(InBuff(4+i));

        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
            wSize += PushEngMonGrp(g, true);
        }

        OutptrOutBuff(3+bGROUPS/8+wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}
