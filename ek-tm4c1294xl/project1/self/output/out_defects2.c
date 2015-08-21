/*------------------------------------------------------------------------------
OUT_DEFECTS2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_energy_spec.h"
#include "../groups.h"
#include "../realtime/realtime.h"
#include "../serial/ports.h"
#include "../special/recalc_def.h"
#include "../time/timedate.h"
#include "../energy.h"
#include "../energy2.h"
#include "out_defects3.h"
#include "out_defects2.h"



void    OutImpCanHou48Def(void)
{
  uint iwHou = GetDayHouIndex(bInBuff6);
            
  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadImpHouFree(iwHou) == 0) break;
    else 
    {
      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
        {
          if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
            PushInt(0xFFFF);
          else
            PushInt( mpwImpHouCan[ PrevSoftHou() ][ c ] );

          wSize += sizeof(uint);
          if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        } 
      }
    } 
          
    if (++iwHou >= wHOURS) iwHou = 0;
  }      

  if (h == 48) 
    OutptrOutBuff(wSize);
  else 
    Result(bRES_BADFLASH);
}


void    OutPowGrpHou48Def(void)
{
  uint iwHou = GetDayHouIndex(bInBuff6);
            
  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadImpHouFree(iwHou) == 0) break;
    else 
    {
      uchar c;
      for (c=0; c<bGROUPS; c++)
      {
        if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
        {
          if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
            PushFloatDef();
          else {
            if (GetGrpHouDef(mpwImpHouCan[ PrevSoftHou() ], c) == 0)
              PushFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], c, 2));
            else
              PushFloatDef();
          }

          wSize += sizeof(float);
          if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        } 
      }
    } 
          
    if (++iwHou >= wHOURS) iwHou = 0;
  }      

  if (h == 48) 
    OutptrOutBuff(wSize);
  else 
    Result(bRES_BADFLASH);
}



ulong   GetDayCanMaxDef(void)
{
  return (ulong)48;
}


ulong   GetMonCanMaxDef(void)
{
  uchar bMonth = ((12 - 1 + tiCurr.bMonth - bInBuff6) % 12) + 1;
  uchar bYear = (bMonth > tiCurr.bMonth) ? tiCurr.bYear-1 : tiCurr.bYear;

  return (ulong)48*GetDaysInMonthYM(bYear, bMonth);
}


ulong   GetDayGrpMaxDef(uchar  ibGrp)
{
  return GetDayCanMaxDef()*GetGroupsSize(ibGrp);
}


ulong   GetMonGrpMaxDef(uchar  ibGrp)
{
  return GetMonCanMaxDef()*GetGroupsSize(ibGrp);
}


ulong   GetCanCurrDef(impulse  *mpimT, uchar  ibCan)
{
  ulong dw = 0;

  uchar t;
  for (t=0; t<bTARIFFS; t++)
    dw += mpimT[ibCan].mpdwImp[t];

  return dw;
}


ulong   GetGrpCurrDef(impulse  *mpimT, uchar  ibGrp)
{
  ulong dw = 0;

  uchar i;
  for (i=0; i<GetGroupsSize(ibGrp); i++)
  {
    uchar c = GetGroupsNodeCanal(ibGrp,i);

    uchar t;
    for (t=0; t<bTARIFFS; t++)
      dw += mpimT[c].mpdwImp[t];
  }

  return dw;
}


void    PushGrpDef(impulse  *mpimT, uchar  ibGrp)
{
  static impulse mpdeTmpGrp;

  memset(&mpdeTmpGrp, 0, sizeof(mpdeTmpGrp));

  uchar i;
  for (i=0; i<GetGroupsSize(ibGrp); i++)
  {
    uchar c = GetGroupsNodeCanal(ibGrp,i);

    uchar t;
    for (t=0; t<bTARIFFS; t++)
      mpdeTmpGrp.mpdwImp[t] += mpimT[c].mpdwImp[t];
  }

  Push(&mpdeTmpGrp, sizeof(impulse));
}



void    OutDayCanDefAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadDefDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == 1)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar c;
        for (c=0; c<bCANALS; c++)
        {
          if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
          {
            PushLong(GetDayCanMaxDef());
            wSize += sizeof(ulong);

            Push(&mpdeDayCan[ c ], sizeof(impulse));
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


void    OutMonCanDefAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadDefMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == 1)
      {
        InitPushPtr();
        uint wSize = 0;

       uchar c;
       for (c=0; c<bCANALS; c++)
        {
          if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
          {
            PushLong(GetMonCanMaxDef());
            wSize += sizeof(ulong);

            Push(&mpdeMonCan[ c ], sizeof(impulse));
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



void    OutDayGrpDefAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadDefDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == 1)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
          {
            PushLong(GetDayGrpMaxDef(g));
            wSize += sizeof(ulong);

            PushGrpDef(mpdeDayCan, g);
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


void    OutMonGrpDefAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadDefMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == 1)
      {
        InitPushPtr();
        uint wSize = 0;

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
          {
            PushLong(GetMonGrpMaxDef(g));
            wSize += sizeof(ulong);

            PushGrpDef(mpdeMonCan, g);
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



void    OutDayCanDef(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadDefDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == 1)
      {
        InitPushPtr();

        uchar c;
        for (c=0; c<bCANALS; c++)
        {
          ulong dw1 = GetDayCanMaxDef();
          ulong dw2 = GetCanCurrDef(mpdeDayCan, c);

          PushChar((dw1 == dw2) ? 0xFF : 0);
        }

        OutptrOutBuff(bCANALS);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutMonCanDef(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadDefMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == 1)
      {
        InitPushPtr();

        uchar g;
        for (g=0; g<bCANALS; g++)
        {
          ulong dw1 = GetMonCanMaxDef();
          ulong dw2 = GetCanCurrDef(mpdeMonCan, g);

          PushChar(dw1 == dw2 ? 0xFF : 0);
        }

        OutptrOutBuff(bCANALS);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutDayGrpDef(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadDefDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == 1)
      {
        InitPushPtr();

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          ulong dw1 = GetDayGrpMaxDef(g);
          ulong dw2 = GetGrpCurrDef(mpdeDayCan, g);

          PushChar((dw1 == dw2) ? 0xFF : 0);
        }

        OutptrOutBuff(bGROUPS);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutMonGrpDef(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadDefMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == 1)
      {
        InitPushPtr();

        uchar g;
        for (g=0; g<bGROUPS; g++)
        {
          ulong dw1 = GetMonGrpMaxDef(g);
          ulong dw2 = GetGrpCurrDef(mpdeMonCan, g);

          PushChar((dw1 == dw2) ? 0xFF : 0);
        }

        OutptrOutBuff(bGROUPS);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}
