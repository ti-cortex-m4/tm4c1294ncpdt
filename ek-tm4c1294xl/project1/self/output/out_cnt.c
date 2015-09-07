/*------------------------------------------------------------------------------
OUT_CNT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../serial/ports.h"
#include "../digitals/digitals.h"
#include "../energy.h"
#include "out_cnt.h"



void    OutCntCanOld(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff5 < bCANALS)
    {
      InitPushPtr();
      OutptrOutBuff(PushFloat(GetCntCurrImp(bInBuff5)));
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutCntCanNew(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff5 < bCANALS)
    {
      InitPushPtr();
      OutptrOutBuff(PushFloat(GetCntCurrImp(bInBuff5)));
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



void    OutCntCanOldAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();
    uint wSize = 0;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      wSize += PushFloat(GetCntCurrImp(c));
    }

    OutptrOutBuff(wSize);
  }
  else Result(bRES_NEEDWORK);
}


void    OutCntCanNewAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if (GetDigitalDevice(c) == 0)
        reBuffA = *GetCntCurrImp(c);
      else
      if ((GetDigitalDevice(c) == 5) || (GetDigitalDevice(c) == 6))
        reBuffA = *PGetCanReal(mpreEsc_S,c);
      else
      {
        if (boLoadMnt == true)
          reBuffA = *PGetCanReal(mpreValueCntHou,c) * mpdwBase[c];
        else
          reBuffA = *PGetCanReal(mpreEsc_S,c);
      }

      PushFloat();
    }
    OutptrOutBuff(sizeof(real)*bCANALS);
  }
  else Result(bRES_NEEDWORK);
}
