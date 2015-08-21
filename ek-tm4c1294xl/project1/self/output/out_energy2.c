/*------------------------------------------------------------------------------
OUT_ENERGY2.C


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "../memory/mem_settings.h"
//#include "../memory/mem_ports.h"
//#include "../memory/mem_realtime.h"
//#include "../memory/mem_energy.h"
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

        uchar i;
        for (i=0; i<bCANALS; i++)
        {
          if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
          {
            uchar j;
            for (j=0; j<bTARIFFS; j++)
            {
              wSize += PushReal(GetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ], i, 0x01 << j));
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

        uchar i;
        for (i=0; i<bCANALS; i++)
        {
          if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
          {
            uchar j;
            for (j=0; j<bTARIFFS; j++)
            {
              wSize += PushReal(*PGetCanImp2RealEng(mpimMonCan[ PrevSoftMon() ], i, 0x01 << j));
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

