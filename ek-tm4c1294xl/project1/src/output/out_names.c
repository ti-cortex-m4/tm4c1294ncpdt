/*------------------------------------------------------------------------------
OUT_NAMES.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_uni.h"
#include        "../memory/mem_ports.h"
#include        "../serial/ports.h"



void    CommonX(void  *pbData, uint  wSize)
{
  if (5+wSize < wOUTBUFF_SIZE-bMARGIN)
  {
    InitPushCRC();
    Push(pbData, wSize);
    Output(wSize);
  }
  else Result(bRES_OUTOVERFLOW);
}



void    GetObjectNameExt(void)
{
  CommonX(&szObjectName, bNAME);
}


void    SetObjectNameExt(void)
{
uchar   i;

  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    for (i=0; i<bNAME; i++) 
      szObjectName[i] = InBuff(6+i);

    szObjectName[bNAME-1] = 0;

    LongResult(bRES_OK);
  }
  else Result(bRES_NEEDPROGRAM);
}



void    GetCanalsNameExt(void)
{
  if (bInBuff6 < bCANALS)
    CommonX(&mpszCanalsName[ bInBuff6 ], bNAME);
  else
    Result(bRES_BADADDRESS);
}


void    SetCanalsNameExt(void)
{
uchar   i;

  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    if (bInBuff6 < bCANALS)
    {
      for (i=0; i<bNAME; i++)
        mpszCanalsName[bInBuff6][i] = InBuff(7+i);

      mpszCanalsName[bInBuff6][bNAME-1] = 0;

      LongResult(bRES_OK);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}



void    GetGroupsNameExt(void)
{
  if (bInBuff6 < bGROUPS)
    CommonX(&mpszGroupsName[ bInBuff6 ], bNAME);
  else
    Result(bRES_BADADDRESS);
}


void    SetGroupsNameExt(void)
{
uchar   i;

  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    if (bInBuff6 < bGROUPS)
    {
      for (i=0; i<bNAME; i++)
        mpszGroupsName[bInBuff6][i] = InBuff(7+i);

      mpszGroupsName[bInBuff6][bNAME-1] = 0;

      LongResult(bRES_OK);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}
