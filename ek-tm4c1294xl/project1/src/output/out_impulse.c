/*------------------------------------------------------------------------------
OUT_IMPULSE,C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../energy2.h"



void    PushImpulse(impulse  *pim)
{
  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    PushLong((*pim).mpdwImp[t]);
  }
}



void    OutImpDayCan(void)
{
        if (enGlobal != GLB_PROGRAM)
        {
          if (bInBuff5 < bDAYS)
          {
            if (LoadImpDay( bInBuff5 ) == 1)
              Outptr(&mpimDayCan[ PrevSoftDay() ], sizeof(impulse)*bCANALS);
            else
              Result(bRES_BADFLASH);
          }
          else Result(bRES_BADADDRESS);
        }
        else Result(bRES_NEEDWORK);
}


void    OutImpMonCan(void)
{
        if (enGlobal != GLB_PROGRAM)
        {
          if (bInBuff5 < bMONTHS)
          {
            if (LoadImpMon( bInBuff5 ) == 1)
              Outptr(&mpimMonCan[ PrevSoftMon() ], sizeof(impulse)*bCANALS);
            else
              Result(bRES_BADFLASH);
          }
          else Result(bRES_BADADDRESS);
        }
        else Result(bRES_NEEDWORK);
}



void    OutImpDayCanExt(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadImpDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == TRUE)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar c;
        for (c=0; c<bCANALS; c++)
        {
          if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
          {
          	PushImpulse(&mpimDayCan[ PrevSoftDay() ][ c ]);
            wSize += sizeof(impulse);
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


void    OutImpMonCanExt(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadImpMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == TRUE)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar c;
        for (c=0; c<bCANALS; c++)
        {
          if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
          {
          	PushImpulse(&mpimMonCan[ PrevSoftMon() ][ c ]);
            wSize += sizeof(impulse);
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
