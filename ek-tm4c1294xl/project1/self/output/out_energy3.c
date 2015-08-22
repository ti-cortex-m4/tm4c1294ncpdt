/*------------------------------------------------------------------------------
PRIMARY.C


------------------------------------------------------------------------------*/

#include        "xdata.h"
#include        "queries.h"
#include        "general.h"
#include        "nexttime.h"
#include        "ports.h"
#include        "engine.h"
#include        "energy.h"
#include        "groups.h"



#ifndef MODBUS

bit     GetGrpHouInt2Def(uint  xdata  *mpwT, uchar  ibGroup)
{
uchar   i,j;

  for (i=0; i<GetGroupsSize(ibGroup); i++)
  {
    j = GetGroupsNodeCanal(ibGroup,i);

    if (*PGetCanInt(mpwT,j) == 0xFFFF)
      return(0);
  }

  return(1);
}



void    OutEngGrpHouExt1(void)
{
uchar   i,j;
uint    wSize;

  if (bInBuff6 > wHOURS/48) 
    Result(bRES_BADADDRESS);
  else if ((bInBuff6 == 0) && (bInBuff7 > GetHouIndex())) 
    Result(bRES_BADADDRESS);
  else
  {
    for (i=0; i<bGROUPS; i++) mpreEngGrp[i] = 0;            

    for (j=0; j<bInBuff7+1; j++)
    {
      LoadImpHou((PrevDayIndex(bInBuff6)+j) % wHOURS);
      for (i=0; i<bGROUPS; i++)
      {
        if ((InBuff(8 + i/8) & (0x80 >> i%8)) != 0) 
          mpreEngGrp[i] += *PGetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], i, 1);
      } 
    }      

    InitPushPtr();
    for (i=0; i<4+bGROUPS/8; i++) PushChar(InBuff(4+i));

    wSize = 0;

    LoadImpHouFree((PrevDayIndex(bInBuff6)+bInBuff7) % wHOURS);
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
          PushReal();
        }

        wSize += sizeof(real);
      } 
    }

    OutptrOutBuff(4+bGROUPS/8+wSize);
  }
}



void    OutEngGrpHouExt2(void)
{
uchar   i;
uint    wSize;

  if (bInBuff6 > wHOURS/48) 
    Result(bRES_BADADDRESS);
  else if ((bInBuff6 == 0) && (bInBuff7 > GetHouIndex())) 
    Result(bRES_BADADDRESS);
  else
  {
    InitPushPtr();
    for (i=0; i<4+bGROUPS/8; i++) PushChar(InBuff(4+i));

    wSize = 0;

    LoadImpHouFree((PrevDayIndex(bInBuff6)+bInBuff7) % wHOURS);
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
          reBuffA = *PGetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], i, 1);
          PushReal();
        }

        wSize += sizeof(real);
      } 
    }

    OutptrOutBuff(4+bGROUPS/8+wSize);
  }
}

#endif

