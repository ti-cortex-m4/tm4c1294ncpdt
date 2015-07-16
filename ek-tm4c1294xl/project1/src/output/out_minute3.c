/*------------------------------------------------------------------------------
OUT_MINUTE3.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../energy.h"
#include "../kernel/array_mnt.h"
#include "out_minute3.h"



void    OutImpMntCanExt(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();
    uint wSize = 0;

    uchar i;
    for (i=0; i<bMINUTES; i++)
    {
      if (LoadImpMnt((bMINUTES+iwHardMnt-i) % bMINUTES) == false) { Result(bRES_BADFLASH); return; }

      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
        {
          PushInt(mpwImpMntCan[ PrevSoftMnt() ][ c ]);
          wSize += sizeof(uint);
        }
      }
    }

    OutptrOutBuff(wSize);
  }
  else Result(bRES_NEEDWORK);
}


void    OutPowMntCanExt(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();
    uint wSize = 0;

    uchar i;
    for (i=0; i<bMINUTES; i++)
    {
      if (LoadImpMnt((bMINUTES+iwHardMnt-i) % bMINUTES) == false) { Result(bRES_BADFLASH); return; }

      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
        {
          wSize += PushFloat(GetCanMntInt2Real(mpwImpMntCan[ PrevSoftMnt() ], c, 20));
        }
      }
    }

    OutptrOutBuff(wSize);
  }
  else Result(bRES_NEEDWORK);
}



void    OutImpCanMntExt(void)
{
  InitPushPtr();

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    if (LoadImpMnt((bMINUTES+iwHardMnt-1) % bMINUTES) == false) { Result(bRES_BADFLASH); return; }

    Push( &mpwImpMntCan[ PrevSoftMnt() ], sizeof(uint)*bCANALS );
    OutptrOutBuff(sizeof(uint)*bCANALS);
  }
}


void    OutPowCanMntExt(void)
{
  InitPushPtr();
  uint wSize = 0;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    if (LoadImpMnt((bMINUTES+iwHardMnt-1) % bMINUTES) == false) { Result(bRES_BADFLASH); return; }

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
      {
        wSize += PushFloat(GetCanMntInt2Real(mpwImpMntCan[ PrevSoftMnt() ], c, 20));
      }
    }

    OutptrOutBuff(wSize);
  }
}

