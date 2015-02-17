/*------------------------------------------------------------------------------
OUT_MINUTE3.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../ports.h"
#include        "../energy.h"



void    OutImpMntCanExt(void)
{
uchar   c, i, j;
uint    w;

  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();
    w = 0;

    for (i=0; i<bMINUTES; i++)
    {
      j = (bMINUTES+ibSoftMnt-i) % bMINUTES;

      for (c=0; c<bCANALS; c++)
      {
        if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
        {
          Push(&mpwImpMntCan[ j ][ c ], sizeof(uint));
          w += sizeof(uint);
        }
      }
    }

    OutptrOutBuff(w);
  }
  else Result(bRES_NEEDWORK);
}


void    OutPowMntCanExt(void)
{
uchar   c, i, m;
uint    w;
real    re;

  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();
    w = 0;

    for (i=0; i<bMINUTES; i++)
    {
      m = (bMINUTES+ibSoftMnt-i) % bMINUTES;

      for (c=0; c<bCANALS; c++)
      {
        if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
        {
          re = GetCanMntInt2Real(mpwImpMntCan[ m ], c, 20);
          PushReal(re);

          w += sizeof(real);
        }
      }
    }

    OutptrOutBuff(w);
  }
  else Result(bRES_NEEDWORK);
}
