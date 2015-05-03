/*------------------------------------------------------------------------------
OUT_DEFECTS21.C


------------------------------------------------------------------------------*/
/*
#include "xdata.h"
#include "queries.h"
#include "ports.h"
#include "engine.h"
#include "groups.h"
#include "energy.h"
#include "general.h"
#include "nexttime.h"
#include "keyboard.h"
#include "recalc_def.h"
#include "c_defects20.h"



#ifndef MODBUS

void    PushRealDef(void)
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

    PushRealDef();
  }
}


void    PushEngDayGrpDef(void)
{
uchar  i;

  GetDayGrpMaxDef(ibGrp);
  GetGrpCurrDef(mpdeDayCan, ibGrp);
  boAlt = (dwBuffC == dwTmp);

  for (i=0; i<bTARIFFS; i++)
  {
    if (boAlt)
    {
      reBuffA = *PGetGrpImp2RealEng(mpimDayCan[ PrevSoftDay() ], ibGrp, 0x01 << i);
      PushReal();
    }
    else
      PushRealDef();

    wBuffD += sizeof(real);
  }
}


void    PushEngMonGrpDef(void)
{
uchar  i;

  GetMonGrpMaxDef(ibGrp);
  GetGrpCurrDef(mpdeMonCan, ibGrp);
  boAlt = (dwBuffC == dwTmp);

  for (i=0; i<bTARIFFS; i++)
  {
    if (boAlt)
    {
      reBuffA = *PGetGrpImp2RealEng(mpimMonCan[ PrevSoftMon() ], ibGrp, 0x01 << i);
      PushReal();
    }
    else
      PushRealDef();

    wBuffD += sizeof(real);
  }
}


void    PushMaxPowDayGrpDef(void)
{
  GetDayGrpMaxDef(ibGrp);
  GetGrpCurrDef(mpdeDayCan, ibGrp);
  boAlt = (dwBuffC == dwTmp);

  if (boAlt)
    Push(&mppoDayGrp[ PrevSoftDay() ][ ibGrp ], sizeof(power));
  else
    PushMaxPowDef();

  wBuffD += sizeof(power);
}


void    PushMaxPowMonGrpDef(void)
{
  GetMonGrpMaxDef(ibGrp);
  GetGrpCurrDef(mpdeMonCan, ibGrp);
  boAlt = (dwBuffC == dwTmp);

  if (boAlt)
    Push(&mppoMonGrp[ PrevSoftMon() ][ ibGrp ], sizeof(power));
  else
    PushMaxPowDef();

  wBuffD += sizeof(power);
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
      wBuffD = 0;

      for (ibGrp=0; ibGrp<bGROUPS; ibGrp++)
      {
        if ((InBuff(7 + ibGrp/8) & (0x80 >> ibGrp%8)) != 0) 
          PushEngDayGrpDef();
      }

      OutptrOutBuff(wBuffD);
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
      wBuffD = 0;

      for (ibGrp=0; ibGrp<bGROUPS; ibGrp++)
      {
        if ((InBuff(7 + ibGrp/8) & (0x80 >> ibGrp%8)) != 0) 
          PushEngMonGrpDef();
      }

      OutptrOutBuff(wBuffD);
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
      wBuffD = 0;

      for (ibGrp=0; ibGrp<bGROUPS; ibGrp++)
      {
        if ((InBuff(7 + ibGrp/8) & (0x80 >> ibGrp%8)) != 0) 
          PushMaxPowDayGrpDef();
      }

      OutptrOutBuff(wBuffD);
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
      wBuffD = 0;

      for (ibGrp=0; ibGrp<bGROUPS; ibGrp++)
      {
        if ((InBuff(7 + ibGrp/8) & (0x80 >> ibGrp%8)) != 0) 
          PushMaxPowMonGrpDef();
      }

      OutptrOutBuff(wBuffD);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



bit     GetGrpHouDef(uint  xdata  *mpwT, uchar  ibGroup)
{
uchar   i,j;

  for (i=0; i<GetGroupsSize(ibGroup); i++)
  {
    j = GetGroupsNodeCanal(ibGroup,i);

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
    reBuffA = *PGetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibGrp, bMul);
    PushReal();
  }
  else
    PushRealDef();

  wBuffD += sizeof(real);
}


void    OutPowHouGrpDef(uchar  bMul)
{
  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();
    wBuffD = 0;

    for (ibGrp=0; ibGrp<bGROUPS; ibGrp++)
    {
      if ((InBuff(6 + ibGrp/8) & (0x80 >> ibGrp%8)) != 0) 
        PushPowHouGrpDef(bMul);
    }

    OutptrOutBuff(wBuffD);
  }
  else Result(bRES_NEEDWORK);
}


#endif
*/
