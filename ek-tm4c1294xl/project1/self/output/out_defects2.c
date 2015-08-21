/*------------------------------------------------------------------------------
OUT_DEFECTS2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_energy_spec.h"
#include "../groups.h"
#include "../realtime/realtime.h"
#include "../serial/ports.h"
#include "../special/recalc_def.h"
#include "out_defects2.h"



void    OutImpCanHou48Def(void)
{
  uint iwHou = GetDayHouIndex(bInBuff6);
            
  InitPushPtr();
  uint wSize = 0;

  uchar j;
  for (j=0; j<48; j++)
  {
    if (LoadImpHouFree(iwHou) == 0) break;
    else 
    {
      uchar i;
      for (i=0; i<bCANALS; i++)
      {
        if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
        {
          if ((bInBuff6 == 0) && (j > GetCurrHouIndex()))
            PushInt(0xFFFF);
          else
            PushInt( mpwImpHouCan[ PrevSoftHou() ][ i ] );

          wSize += sizeof(uint);
          if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        } 
      }
    } 
          
    if (++iwHou >= wHOURS) iwHou = 0;
  }      

  if (j == 48) 
    OutptrOutBuff(wSize);
  else 
    Result(bRES_BADFLASH);
}


void    OutPowGrpHou48Def(void)
{
  uint iwHou = GetDayHouIndex(bInBuff6);
            
  InitPushPtr();
  uint wSize = 0;

  uchar j;
  for (j=0; j<48; j++)
  {
    if (LoadImpHouFree(iwHou) == 0) break;
    else 
    {
      uchar i;
      for (i=0; i<bGROUPS; i++)
      {
        if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
        {
          if ((bInBuff6 == 0) && (j > GetCurrHouIndex()))
            PushRealDef();
          else {
            if (GetGrpHouDef(mpwImpHouCan[ PrevSoftHou() ], i) == 0)
            {
              reBuffA = *PGetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], i, 2);
              PushReal();
            }
            else
              PushRealDef();
          }

          wSize += sizeof(float);
          if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        } 
      }
    } 
          
    if (++iwHou >= wHOURS) iwHou = 0;
  }      

  if (j == 48) 
    OutptrOutBuff(wSize);
  else 
    Result(bRES_BADFLASH);
}



void    GetDayCanMaxDef(void)
{
  dwBuffC = (ulong)48;
}


void    GetMonCanMaxDef(void)
{
  tiAlt.bMonth = ((12 - 1 + tiCurr.bMonth - bInBuff6) % 12) + 1;
  tiAlt.bYear = (tiAlt.bMonth > tiCurr.bMonth) ? tiCurr.bYear-1 : tiCurr.bYear;

  dwBuffC = (ulong)48*DaysInMonth();
}


void    GetDayGrpMaxDef(uchar  ibGroup)
{
  GetDayCanMaxDef();
  dwBuffC *= GetGroupsSize(ibGroup);
}


void    GetMonGrpMaxDef(uchar  ibGroup)
{
  GetMonCanMaxDef();
  dwBuffC *= GetGroupsSize(ibGroup);
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
uchar   i,j,k;

  memset(&mpdeTmpGrp, 0, sizeof(mpdeTmpGrp));

  for (i=0; i<GetGroupsSize(ibGrp); i++)
  {
    j = GetGroupsNodeCanal(ibGrp,i);
    for (k=0; k<bTARIFFS; k++)
      mpdeTmpGrp.mpdwImp[k] += mpimT[j].mpdwImp[k];
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

       uchar i;
       for (i=0; i<bCANALS; i++)
        {
          if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
          {
            GetDayCanMaxDef();
            PushLong(&dwBuffC);
            wSize += sizeof(ulong);

            Push(&mpdeDayCan[ i ], sizeof(impulse));
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

       uchar i;
       for (i=0; i<bCANALS; i++)
        {
          if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
          {
            GetMonCanMaxDef();
            PushLong(&dwBuffC);
            wSize += sizeof(ulong);

            Push(&mpdeMonCan[ i ], sizeof(impulse));
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

        uchar i;
        for (i=0; i<bGROUPS; i++)
        {
          if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
          {
            GetDayGrpMaxDef(i);
            PushLong(&dwBuffC);
            wSize += sizeof(ulong);

            PushGrpDef(mpdeDayCan, i);
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

       uchar i;
       for (i=0; i<bGROUPS; i++)
        {
          if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
          {
            GetMonGrpMaxDef(i);
            PushLong(&dwBuffC);
            wSize += sizeof(ulong);

            PushGrpDef(mpdeMonCan, i);
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

        uchar i;
        for (i=0; i<bCANALS; i++)
        {
          GetDayCanMaxDef();
          GetCanCurrDef(mpdeDayCan, i);

          PushChar((dwBuffC == dwTmp) ? 0xFF : 0);
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

        uchar i;
        for (i=0; i<bCANALS; i++)
        {
          GetMonCanMaxDef();
          GetCanCurrDef(mpdeMonCan, i);

          PushChar(dwBuffC == dwTmp ? 0xFF : 0);
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

        uchar i;
        for (i=0; i<bGROUPS; i++)
        {
          GetDayGrpMaxDef(i);
          GetGrpCurrDef(mpdeDayCan, i);

          PushChar((dwBuffC == dwTmp) ? 0xFF : 0);
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

        uchar i;
        for (i=0; i<bGROUPS; i++)
        {
          GetMonGrpMaxDef(i);
          GetGrpCurrDef(mpdeMonCan, i);

          PushChar((dwBuffC == dwTmp) ? 0xFF : 0);
        }

        OutptrOutBuff(bGROUPS);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}
