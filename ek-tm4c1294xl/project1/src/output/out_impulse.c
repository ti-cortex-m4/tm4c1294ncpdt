/*------------------------------------------------------------------------------
OUT_IMPULSE.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../serial/ports.h"
#include        "../realtime/realtime.h"
#include        "../energy2.h"



void    PushImpulse(impulse  *pim)
{
uchar   t;
ulong   dw;

	for (t=0; t<bTARIFFS; t++)
	{
    dw = (*pim).mpdwImp[t];
    PushLong(dw);
	}
}



void    OutImpDayCanExt(void)
{
uchar   c;
uint    w;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadImpDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == TRUE)
      {
        InitPushPtr();
        w = 0;

        for (c=0; c<bCANALS; c++)
        {
          if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
          {
          	PushImpulse(&mpimDayCan[ PrevSoftDay() ][ c ]);
            w += sizeof(impulse);
          }
        }
        OutptrOutBuff(w);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutImpMonCanExt(void)
{
uchar   c;
uint    w;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadImpMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == TRUE)
      {
        InitPushPtr();
        w = 0;

        for (c=0; c<bCANALS; c++)
        {
          if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
          {
          	PushImpulse(&mpimMonCan[ PrevSoftMon() ][ c ]);
            w += sizeof(impulse);
          }
        }
        OutptrOutBuff(w);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}
