/*------------------------------------------------------------------------------
OUT_ENERGY3.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_energy.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../energy.h"
#include "../energy2.h"
#include "out_energy3.h"



bool    GetGrpHouInt2Def(uint  *mpwT, uchar  ibGroup)
{
  uchar i;
  for (i=0; i<GetGroupsSize(ibGroup); i++)
  {
    uchar c = GetGroupsNodeCanal(ibGroup,i);

    if (*PGetCanInt(mpwT,c) == 0xFFFF)
      return(0);
  }

  return(1);
}



void    OutEngGrpHouExt1(void)
{
uchar   i,j;

  if (bInBuff6 > wHOURS/48) 
    Result(bRES_BADADDRESS);
  else if ((bInBuff6 == 0) && (bInBuff7 > GetHouIndex())) 
    Result(bRES_BADADDRESS);
  else
  {
    for (i=0; i<bGROUPS; i++) mpreEngGrp[i] = 0;            

    for (j=0; j<bInBuff7+1; j++)
    {
      LoadImpHou((GetCurrHouIndex(bInBuff6)+j) % wHOURS);
      for (i=0; i<bGROUPS; i++)
      {
        if ((InBuff(8 + i/8) & (0x80 >> i%8)) != 0) 
          mpreEngGrp[i] += *PGetGrpHouInt2float(mpwImpHouCan[ PrevSoftHou() ], i, 1);
      } 
    }      

    InitPushPtr();
    uint wSize = 0;

    for (i=0; i<4+bGROUPS/8; i++) PushChar(InBuff(4+i));


    LoadImpHouFree((GetCurrHouIndex(bInBuff6)+bInBuff7) % wHOURS);
    for (i=0; i<bGROUPS; i++)
    {
      if ((InBuff(8 + i/8) & (0x80 >> i%8)) != 0) 
      {
        if (GetGrpHouInt2Def(mpwImpHouCan[ PrevSoftHou() ], i) == 0)
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else
        {
          reBuffA = mpreEngGrp[i];
          Pushfloat();
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
  else if ((bInBuff6 == 0) && (bInBuff7 > GetHouIndex())) 
    Result(bRES_BADADDRESS);
  else
  {
    InitPushPtr();
    uint wSize = 0;

    uchar   i;
    for (i=0; i<4+bGROUPS/8; i++) PushChar(InBuff(4+i));

    LoadImpHouFree((GetCurrHouIndex(bInBuff6)+bInBuff7) % wHOURS);
    for (i=0; i<bGROUPS; i++)
    {
      if ((InBuff(8 + i/8) & (0x80 >> i%8)) != 0) 
      {
        if (GetGrpHouInt2Def(mpwImpHouCan[ PrevSoftHou() ], i) == 0)
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else
        {
          Pushfloat(GetGrpHouInt2float(mpwImpHouCan[ PrevSoftHou() ], i, 1));
        }

        wSize += sizeof(float);
      } 
    }

    OutptrOutBuff(4+bGROUPS/8+wSize);
  }
}

