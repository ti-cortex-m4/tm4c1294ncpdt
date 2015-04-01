/*------------------------------------------------------------------------------
OUT_ENERGY.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../serial/ports.h"
#include        "../realtime/realtime.h"
#include        "../energy.h"
#include        "../energy2.h"



uint    PushEngDayGrp(uchar  ibGrp, bool  fSum)
{
uchar  t;
uint   w;
real   re;

  w = 0;

  if (fSum == 0)
  {
    for (t=0; t<bTARIFFS; t++)
    {
      re = GetGrpImp2FloatEng(mpimDayCan[ PrevSoftDay() ], ibGrp, 0x01 << t);

      w += sizeof(real);
      PushFloat(re);
    }
  }
  else
  {
    re = 0;
    for (t=0; t<bTARIFFS; t++)
      re += GetGrpImp2FloatEng(mpimDayCan[ PrevSoftDay() ], ibGrp, 0x01 << t);

    w += sizeof(real);
    PushFloat(re);
  }

  return w;
}


uint    PushEngMonGrp(uchar  ibGrp, bool  fSum)
{
uchar  t;
uint   w;
real   re;

  w = 0;

  if (fSum == 0)
  {
    for (t=0; t<bTARIFFS; t++)
    {
      re = GetGrpImp2FloatEng(mpimMonCan[ PrevSoftMon() ], ibGrp, 0x01 << t);

      w += sizeof(real);
      PushFloat(re);
    }
  }
  else
  {
    re = 0;
    for (t=0; t<bTARIFFS; t++)
      re += GetGrpImp2FloatEng(mpimMonCan[ PrevSoftMon() ], ibGrp, 0x01 << t);

    w += sizeof(real);
    PushFloat(re);
  }

  return w;
}



void    OutEngDayGrpExt0(void)
{
uchar   g;
uint    w;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadImpDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == TRUE)
      {
        InitPushPtr();
        w = 0;

        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
            w += PushEngDayGrp(g, 0);
        }
        OutptrOutBuff(w);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutEngDayGrpExt1(void)
{
uchar   i, g;
uint    w;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadImpDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == TRUE)
      {
        InitPushPtr();
        for (i=0; i<3+bGROUPS/8; i++) PushChar(InBuff(4+i));

        w = 0;

        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
          	w += PushEngDayGrp(g, 1);
        }
        OutptrOutBuff(3+bGROUPS/8+w);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



void    OutEngMonGrpExt0(void)
{
uchar   g;
uint    w;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadImpMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == TRUE)
      {
        InitPushPtr();
        w = 0;

        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
            w += PushEngMonGrp(g, 0);
        }
        OutptrOutBuff(w);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutEngMonGrpExt1(void)
{
uchar   i, g;
uint    w;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadImpMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == TRUE)
      {
        InitPushPtr();
        for (i=0; i<3+bGROUPS/8; i++) PushChar(InBuff(4+i));

        w = 0;

        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
            w += PushEngMonGrp(g, 1);
        }
        OutptrOutBuff(3+bGROUPS/8+w);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}
