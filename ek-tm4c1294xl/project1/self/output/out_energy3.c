/*------------------------------------------------------------------------------
OUT_ENERGY3.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_energy.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../groups.h"
#include "../energy.h"
#include "../energy2.h"
#include "out_energy3.h"



bool    GetGrpHouInt2Def(uint  *mpw, uchar  ibGrp)
{
  uchar i;
  for (i=0; i<GetGroupsSize(ibGrp); i++)
  {
    uchar c = GetGroupsNodeCanal(ibGrp,i);

    if (mpw[c] == 0xFFFF)
      return(0);
  }

  return(1);
}



void    OutEngGrpHouExt1(void)
{
static float mpreEngGrp[bGROUPS];

  if (bInBuff6 > wHOURS/48) 
    Result(bRES_BADADDRESS);
  else if ((bInBuff6 == 0) && (bInBuff7 > GetCurrHouIndex()))
    Result(bRES_BADADDRESS);
  else
  {
    uchar g;
    for (g=0; g<bGROUPS; g++) mpreEngGrp[g] = 0;            

    uchar i;
    for (i=0; i<bInBuff7+1; i++)
    {
      LoadImpHou((GetDayHouIndex(bInBuff6)+i) % wHOURS);
      for (g=0; g<bGROUPS; g++)
      {
        if ((InBuff(8 + g/8) & (0x80 >> g%8)) != 0) 
          mpreEngGrp[g] += GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], g, 1);
      } 
    }      

    InitPushPtr();
    uint wSize = 0;

    for (i=0; i<4+bGROUPS/8; i++) PushChar(InBuff(4+i));


    LoadImpHouFree((GetDayHouIndex(bInBuff6)+bInBuff7) % wHOURS);
    for (g=0; g<bGROUPS; g++)
    {
      if ((InBuff(8 + g/8) & (0x80 >> g%8)) != 0) 
      {
        if (GetGrpHouInt2Def(mpwImpHouCan[ PrevSoftHou() ], g) == 0)
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else
        {
          PushFloat(mpreEngGrp[g]);
        }

        wSize += sizeof(float);
      } 
    }

    OutptrOutBuff(4+bGROUPS/8+wSize);
  }
}



void    OutEngGrpHouExt2(void)
{
  if (bInBuff6 > wHOURS/48) 
    Result(bRES_BADADDRESS);
  else if ((bInBuff6 == 0) && (bInBuff7 > GetCurrHouIndex()))
    Result(bRES_BADADDRESS);
  else
  {
    InitPushPtr();
    uint wSize = 0;

    uchar i;
    for (i=0; i<4+bGROUPS/8; i++) PushChar(InBuff(4+i));

    LoadImpHouFree((GetDayHouIndex(bInBuff6)+bInBuff7) % wHOURS);

    uchar g;
    for (g=0; g<bGROUPS; g++)
    {
      if ((InBuff(8 + g/8) & (0x80 >> g%8)) != 0)
      {
        if (GetGrpHouInt2Def(mpwImpHouCan[ PrevSoftHou() ], g) == 0)
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else
        {
          PushFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], g, 1));
        }

        wSize += sizeof(float);
      } 
    }

    OutptrOutBuff(4+bGROUPS/8+wSize);
  }
}

