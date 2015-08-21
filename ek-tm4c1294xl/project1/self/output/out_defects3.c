/*------------------------------------------------------------------------------
OUT_DEFECTS3.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_energy_spec.h"
#include "../groups.h"
#include "../realtime/realtime.h"
#include "../serial/ports.h"
#include "../special/recalc_def.h"
#include "../energy.h"
#include "../energy2.h"
#include "out_defects2.h"
#include "out_defects3.h"



void    PushFloatDef(void)
{
  PushChar(0xFF);
  PushChar(0xFF);
  PushChar(0xFF);
  PushChar(0xFF);
}


void    PushMaxPowDef(void)
{
uchar  i;

  for (i=0; i<bTARIFFS; i++)
  {
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);

    PushFloatDef();
  }
}


void    PushEngDayGrpDef(uchar  ibGrp)
{
  ulong dw1 = GetDayGrpMaxDef(ibGrp);
  ulong dw2 = GetGrpCurrDef(mpdeDayCan, ibGrp);
  bool f = (dw1 == dw2);

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    if (f)
      PushFloat(GetGrpImp2FloatEng(mpimDayCan[ PrevSoftDay() ], ibGrp, 0x01 << t));
    else
      PushFloatDef();

    wSize += sizeof(float);
  }
}


void    PushEngMonGrpDef(uchar  ibGrp)
{
  ulong dw1 = GetMonGrpMaxDef(ibGrp);
  ulong dw2 = GetGrpCurrDef(mpdeMonCan, ibGrp);
  bool f = (dw1 == dw2);

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    if (f)
      PushFloat(GetGrpImp2FloatEng(mpimMonCan[ PrevSoftMon() ], ibGrp, 0x01 << t));
    else
      PushFloatDef();

    wSize += sizeof(float);
  }
}


void    PushMaxPowDayGrpDef(uchar  ibGrp)
{
  ulong dw1 = GetDayGrpMaxDef(ibGrp);
  ulong dw2 = GetGrpCurrDef(mpdeDayCan, ibGrp);
  bool f = (dw1 == dw2);

  if (f)
    Push(&mppoDayGrp[ PrevSoftDay() ][ ibGrp ], sizeof(power));
  else
    PushMaxPowDef();

  wSize += sizeof(power);
}


void    PushMaxPowMonGrpDef(uchar  ibGrp)
{
  ulong dw1 = GetMonGrpMaxDef(ibGrp);
  ulong dw2 = GetGrpCurrDef(mpdeMonCan, ibGrp);
  bool f = (dw1 == dw2);

  if (f)
    Push(&mppoMonGrp[ PrevSoftMon() ][ ibGrp ], sizeof(power));
  else
    PushMaxPowDef();

  wSize += sizeof(power);
}



void    OutEngDayGrpDef(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      LoadImpDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS );
      LoadDefDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS );

      InitPushPtr();
      uint wSize = 0;

      uchar g;
      for (g=0; g<bGROUPS; g++)
      {
        if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
          PushEngDayGrpDef();
      }

      OutptrOutBuff(wSize);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutEngMonGrpDef(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      LoadImpMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS );
      LoadDefMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS );
      
      InitPushPtr();
      uint wSize = 0;

      uchar g;
      for (g=0; g<bGROUPS; g++)
      {
        if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
          PushEngMonGrpDef();
      }

      OutptrOutBuff(wSize);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutMaxPowDayGrpDef(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      LoadPowDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS );
      LoadDefDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS );

      InitPushPtr();
      uint wSize = 0;

      uchar g;
      for (g=0; g<bGROUPS; g++)
      {
        if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
          PushMaxPowDayGrpDef();
      }

      OutptrOutBuff(wSize);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutMaxPowMonGrpDef(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      LoadPowMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS );
      LoadDefMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS );

      InitPushPtr();
      uint wSize = 0;

      uchar g;
      for (g=0; g<bGROUPS; g++)
      {
        if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
          PushMaxPowMonGrpDef();
      }

      OutptrOutBuff(wSize);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



bool    GetGrpHouDef(uint  *mpwT, uchar  ibGrp)
{
  uchar i;
  for (i=0; i<GetGroupsSize(ibGrp); i++)
  {
    uchar j = GetGroupsNodeCanal(ibGrp,i);

    if (mpwT[j] == 0xFFFF)
      return 1;
  }

  return 0;
}


void    PushPowHouGrpDef(uchar  bMul)
{
  LoadImpHouFree( PrevHardHou() );
  if (GetGrpHouDef(mpwImpHouCan[ PrevSoftHou() ], ibGrp) == 0)
  {
    LoadImpHou( PrevHardHou() );
    reBuffA = GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibGrp, bMul);
    PushFloat();
  }
  else
    PushFloatDef();

  wSize += sizeof(float);
}


void    OutPowHouGrpDef(uchar  bMul)
{
  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();
    uint wSize = 0;

    uchar g;
    for (g=0; g<bGROUPS; g++)
    {
      if ((InBuff(6 + g/8) & (0x80 >> g%8)) != 0)
        PushPowHouGrpDef(bMul);
    }

    OutptrOutBuff(wSize);
  }
  else Result(bRES_NEEDWORK);
}
