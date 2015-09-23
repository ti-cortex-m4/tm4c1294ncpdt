/*------------------------------------------------------------------------------
OUT_ENERGY2!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_energy.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../energy.h"
#include "../energy2.h"
#include "out_energy2.h"



void    OutEngDayCan(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadImpDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == 1)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar c;
        for (c=0; c<bCANALS; c++)
        {
          if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
          {
            uchar t;
            for (t=0; t<bTARIFFS; t++)
            {
              wSize += PushFloat(GetCanImp2FloatEng(mpimDayCan[ PrevSoftDay() ], c, 0x01 << t));
            }
          }
        }
        OutptrOutBuff(wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutEngMonCan(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadImpMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == 1)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar c;
        for (c=0; c<bCANALS; c++)
        {
          if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
          {
            uchar t;
            for (t=0; t<bTARIFFS; t++)
            {
              wSize += PushFloat(GetCanImp2FloatEng(mpimMonCan[ PrevSoftMon() ], c, 0x01 << t));
            }
          }
        }
        OutptrOutBuff(wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}

