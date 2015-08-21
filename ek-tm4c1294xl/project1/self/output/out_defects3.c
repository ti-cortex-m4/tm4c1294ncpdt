/*------------------------------------------------------------------------------
OUT_DEFECTS3.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_energy.h"
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
  uchar t;
  for (t=0; t<bTARIFFS; t++)
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


uint    PushEngDayGrpDef(uchar  ibGrp)
{
  ulong dw1 = GetDayGrpMaxDef(ibGrp);
  ulong dw2 = GetGrpCurrDef(mpdeDayCan, ibGrp);
  bool f = (dw1 == dw2);

  uint wSize = 0;

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    if (f)
      PushFloat(GetGrpImp2FloatEng(mpimDayCan[ PrevSoftDay() ], ibGrp, 0x01 << t));
    else
      PushFloatDef();

    wSize += sizeof(float);
  }

  return wSize;
}


uint    PushEngMonGrpDef(uchar  ibGrp)
{
  ulong dw1 = GetMonGrpMaxDef(ibGrp);
  ulong dw2 = GetGrpCurrDef(mpdeMonCan, ibGrp);
  bool f = (dw1 == dw2);

  uint wSize = 0;

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    if (f)
      PushFloat(GetGrpImp2FloatEng(mpimMonCan[ PrevSoftMon() ], ibGrp, 0x01 << t));
    else
      PushFloatDef();

    wSize += sizeof(float);
  }

  return wSize;
}


uint    PushMaxPowDayGrpDef(uchar  ibGrp)
{
  ulong dw1 = GetDayGrpMaxDef(ibGrp);
  ulong dw2 = GetGrpCurrDef(mpdeDayCan, ibGrp);
  bool f = (dw1 == dw2);

  if (f)
    Push(&mppoDayGrp[ PrevSoftDay() ][ ibGrp ], sizeof(power));
  else
    PushMaxPowDef();

  return sizeof(power);
}


uint    PushMaxPowMonGrpDef(uchar  ibGrp)
{
  ulong dw1 = GetMonGrpMaxDef(ibGrp);
  ulong dw2 = GetGrpCurrDef(mpdeMonCan, ibGrp);
  bool f = (dw1 == dw2);

  if (f)
    Push(&mppoMonGrp[ PrevSoftMon() ][ ibGrp ], sizeof(power));
  else
    PushMaxPowDef();

  return sizeof(power);
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
        	wSize += PushEngDayGrpDef(g);
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
          wSize += PushEngMonGrpDef(g);
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
          wSize += PushMaxPowDayGrpDef(g);
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
          wSize += PushMaxPowMonGrpDef(g);
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
    uchar c = GetGroupsNodeCanal(ibGrp,i);

    if (mpwT[c] == 0xFFFF)
      return true;
  }

  return false;
}


uint    PushPowHouGrpDef(uchar  bMul, uchar  ibGrp)
{
  LoadImpHouFree( PrevHardHou() );
  if (GetGrpHouDef(mpwImpHouCan[ PrevSoftHou() ], ibGrp) == false)
  {
    LoadImpHou( PrevHardHou() );
    PushFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibGrp, bMul));
  }
  else
    PushFloatDef();

  return sizeof(float);
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
        wSize += PushPowHouGrpDef(bMul, g);
    }

    OutptrOutBuff(wSize);
  }
  else Result(bRES_NEEDWORK);
}
