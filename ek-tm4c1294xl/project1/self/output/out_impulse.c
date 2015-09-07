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
#include "out_impulse.h"



static uchar PushImpulse(impulse  *pim)
{
  uchar bSize = 0;

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    bSize += PushLong((*pim).mpdwImp[t]);
  }

  return bSize;
}



void    OutImpMntCan(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if ((bInBuff5 < bCANALS) && (bInBuff6 < bMINUTES))
      Outptr(&mpwImpMntCan[ bInBuff6 ][ bInBuff5 ], sizeof(uint));
    else
      Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutImpMntCanAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff5 < bMINUTES)
      Outptr(&mpwImpMntCan[ bInBuff5 ], sizeof(uint)*bCANALS);
    else
      Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutImpHhrCan(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if ((bInBuff5 < bCANALS) && (bInBuff6*0x100 + bInBuff7 < wHOURS))
    {
      if (LoadImpHou( bInBuff6*0x100 + bInBuff7 ) == 1)
        Outptr(&mpwImpHouCan[ PrevSoftHou() ][ bInBuff5 ], sizeof(uint));
      else
        Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutImpHhrCanAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff5*0x100 + bInBuff6 < wHOURS)
    {
      if (LoadImpHou( bInBuff5*0x100 + bInBuff6 ) == 1)
        Outptr(&mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS);
      else
        Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutImpDayCan(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if ((bInBuff5 < bCANALS) && (bInBuff6 < bDAYS))
    {
      if (LoadImpDay( bInBuff6 ) == 1)
        Outptr(&mpimDayCan[ PrevSoftDay() ][ bInBuff5 ], sizeof(impulse));
      else
        Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutImpDayCanAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff5 < bDAYS)
    {
      if (LoadImpDay( bInBuff5 ) == 1)
      {
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    wSize += PushImpulse(&mpimDayCan[ PrevSoftDay() ][ c ]);
  }

  OutptrOutBuff(wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutImpMonCan(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if ((bInBuff5 < bCANALS) && (bInBuff6 < bMONTHS))
    {
      if (LoadImpMon( bInBuff6 ) == 1)
        Outptr(&mpimMonCan[ PrevSoftMon() ][ bInBuff5 ], sizeof(impulse));
      else
        Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutImpMonCanAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff5 < bMONTHS)
    {
      if (LoadImpMon( bInBuff5 ) == 1)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar c;
        for (c=0; c<bCANALS; c++)
        {
          wSize += PushImpulse(&mpimMonCan[ PrevSoftMon() ][ c ]);
        }

        OutptrOutBuff(wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutImpAbsCan(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff5 < bCANALS)
      Outptr(&mpimAbsCan[ bInBuff5 ], sizeof(impulse));
    else
      Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutImpAbsCanAll(void)
{
  if (enGlobal != GLB_PROGRAM)
    Outptr(&mpimAbsCan, sizeof(mpimAbsCan));
  else
    Result(bRES_NEEDWORK);
}



void    OutImpDayCanExt(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadImpDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == true)
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
      if (LoadImpMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == true)
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
