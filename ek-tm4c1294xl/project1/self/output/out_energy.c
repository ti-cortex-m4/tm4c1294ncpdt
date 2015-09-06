/*------------------------------------------------------------------------------
OUT_ENERGY.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../energy.h"
#include "../energy2.h"
#include "out_energy.h"



static uint PushEngDayGrp(uchar  ibGrp, bool  fSum, bool  fDouble)
{
uchar  t;
double db;

  uint wSize = 0;

  if (fSum == false)
  {
    for (t=0; t<bTARIFFS; t++)
    {
      db = GetGrpImp2DoubleEng(mpimDayCan[ PrevSoftDay() ], ibGrp, 0x01 << t);

      wSize += PushFloatOrDouble(db, fDouble);
    }
  }
  else
  {
    db = 0;
    for (t=0; t<bTARIFFS; t++)
    {
      db += GetGrpImp2DoubleEng(mpimDayCan[ PrevSoftDay() ], ibGrp, 0x01 << t);
    }

    wSize += PushFloatOrDouble(db, fDouble);
  }

  return wSize;
}


static uint PushEngMonGrp(uchar  ibGrp, bool  fSum, bool  fDouble)
{
uchar  t;
double db;

  uint wSize = 0;

  if (fSum == false)
  {
    for (t=0; t<bTARIFFS; t++)
    {
      db = GetGrpImp2DoubleEng(mpimMonCan[ PrevSoftMon() ], ibGrp, 0x01 << t);

      wSize += PushFloatOrDouble(db, fDouble);
    }
  }
  else
  {
    db = 0;
    for (t=0; t<bTARIFFS; t++)
    {
      db += GetGrpImp2DoubleEng(mpimMonCan[ PrevSoftMon() ], ibGrp, 0x01 << t);
    }

    wSize += PushFloatOrDouble(db, fDouble);
  }

  return wSize;
}



void    OutEngDayGrp(bool  fAllGroups, uchar  ibDay, bool  fSum)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (ibDay < bDAYS)
    {
      if (LoadImpDay( ibDay ) == 1)
      {
        if (fAllGroups == 1)
        {
          InitPushPtr();
          uint wSize = 0;

          uchar g;
          for (g=0; g<bGROUPS; g++)
          {
            PushEngDayGrp(g, fSum, false);
          }

          OutptrOutBuff(wSize);
        }
        else
        {
          if (bInBuff5 < bGROUPS)
          {
            InitPushPtr();
            OutptrOutBuff(PushEngDayGrp(bInBuff5, fSum, false));
          }
          else Result(bRES_BADADDRESS);
        }
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutEngMonGrp(bool  fAllGroups, uchar  ibMon, bool  fSum)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (ibMon < bMONTHS)
    {
      if (LoadImpMon( ibMon ) == 1)
      {
        if (fAllGroups == 1)
        {
          InitPushPtr();
          uint wSize = 0;

          uchar g;
          for (g=0; g<bGROUPS; g++)
          {
            wSize += PushEngMonGrp(g, fSum, false);
          }

          OutptrOutBuff(wSize);
        }
        else
        {
          if (bInBuff5 < bGROUPS)
          {
            InitPushPtr();
            OutptrOutBuff(PushEngMonGrp(bInBuff5, fSum, false));
          }
          else Result(bRES_BADADDRESS);
        }
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



void    OutEngDayGrpExt(bool  fDouble)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadImpDay((bDAYS+ibHardDay-bInBuff6) % bDAYS) == true)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
            wSize += PushEngDayGrp(g, false, fDouble);
        }

        OutptrOutBuff(wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutEngDayGrpExtSum(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadImpDay((bDAYS+ibHardDay-bInBuff6) % bDAYS) == true)
      {
        InitPushPtr();

        uchar i;
        for (i=0; i<3+bGROUPS/8; i++)
          PushChar(InBuff(4+i));

        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
            wSize += PushEngDayGrp(g, true, false);
        }

        OutptrOutBuff(3+bGROUPS/8+wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



void    OutEngMonGrpExt(bool  fDouble)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadImpMon((bMONTHS+ibHardMon-bInBuff6) % bMONTHS) == true)
      {
        InitPushPtr();

        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
            wSize += PushEngMonGrp(g, false, fDouble);
        }

        OutptrOutBuff(wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutEngMonGrpExtSum(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadImpMon((bMONTHS+ibHardMon-bInBuff6) % bMONTHS) == true)
      {
        InitPushPtr();

        uchar i;
        for (i=0; i<3+bGROUPS/8; i++)
          PushChar(InBuff(4+i));

        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
            wSize += PushEngMonGrp(g, true, false);
        }

        OutptrOutBuff(3+bGROUPS/8+wSize);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}
