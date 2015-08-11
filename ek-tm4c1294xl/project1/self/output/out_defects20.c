/*------------------------------------------------------------------------------
OUT_DEFECTS20.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../groups.h"
/*
#include "queries.h"
#include "ports.h"
#include "engine.h"
#include "energy.h"
#include "general.h"
#include "groups.h"
#include "timedate.h"
#include "nexttime.h"
#include "keyboard.h"
#include "recalc_def.h"
#include "c_defects21.h"



#ifndef MODBUS

void    OutImpCanHou48Def(void)
{
uchar   i,j;

  iwHou = GetDayHouIndex(bInBuff6);
            
  InitPushPtr();
  wBuffD = 0;

  for (j=0; j<48; j++)
  {
    if (LoadImpHouFree(iwHou) == 0) break;
    else 
    {
      for (i=0; i<bCANALS; i++)
      {
        if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
        {
          if ((bInBuff6 == 0) && (j > GetCurrHouIndex()))
            PushInt(0xFFFF);
          else
            PushInt( mpwImpHouCan[ PrevSoftHou() ][ i ] );

          wBuffD += sizeof(uint);
          if (wBuffD >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        } 
      }
    } 
          
    if (++iwHou >= wHOURS) iwHou = 0;
  }      

  if (j == 48) 
    OutptrOutBuff(wBuffD);
  else 
    Result(bRES_BADFLASH);
}


void    OutPowGrpHou48Def(void)
{
uchar   i,j;

  iwHou = GetDayHouIndex(bInBuff6);
            
  InitPushPtr();
  wBuffD = 0;

  for (j=0; j<48; j++)
  {
    if (LoadImpHouFree(iwHou) == 0) break;
    else 
    {
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

          wBuffD += sizeof(float);
          if (wBuffD >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        } 
      }
    } 
          
    if (++iwHou >= wHOURS) iwHou = 0;
  }      

  if (j == 48) 
    OutptrOutBuff(wBuffD);
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
*/

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

/*
void    PushGrpDef(impulse  _xdata  *mpimT, uchar  ibGroup)
{
uchar   i,j,k;

  memset(&mpdeTmpGrp, 0, sizeof(mpdeTmpGrp));

  for (i=0; i<GetGroupsSize(ibGroup); i++)
  {
    j = GetGroupsNodeCanal(ibGroup,i);
    for (k=0; k<bTARIFFS; k++)
      mpdeTmpGrp.mpdwImp[k] += mpimT[j].mpdwImp[k];
  }

  Push(&mpdeTmpGrp, sizeof(impulse));
}



void    OutDayCanDefAll(void)
{
uchar   i;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadDefDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == 1)
      {
        InitPushPtr();
        wBuffD = 0;

        for (i=0; i<bCANALS; i++)
        {
          if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
          {
            GetDayCanMaxDef();
            PushLong(&dwBuffC);
            wBuffD += sizeof(ulong);

            Push(&mpdeDayCan[ i ], sizeof(impulse));
            wBuffD += sizeof(impulse);
          }
        }

        OutptrOutBuff(wBuffD);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutMonCanDefAll(void)
{
uchar   i;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadDefMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == 1)
      {
        InitPushPtr();
        wBuffD = 0;

        for (i=0; i<bCANALS; i++)
        {
          if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
          {
            GetMonCanMaxDef();
            PushLong(&dwBuffC);
            wBuffD += sizeof(ulong);

            Push(&mpdeMonCan[ i ], sizeof(impulse));
            wBuffD += sizeof(impulse);
          }
        }

        OutptrOutBuff(wBuffD);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



void    OutDayGrpDefAll(void)
{
uchar   i;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadDefDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == 1)
      {
        InitPushPtr();
        wBuffD = 0;

        for (i=0; i<bGROUPS; i++)
        {
          if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
          {
            GetDayGrpMaxDef(i);
            PushLong(&dwBuffC);
            wBuffD += sizeof(ulong);

            PushGrpDef(mpdeDayCan, i);
            wBuffD += sizeof(impulse);
          }
        }

        OutptrOutBuff(wBuffD);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutMonGrpDefAll(void)
{
uchar   i;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadDefMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == 1)
      {
        InitPushPtr();
        wBuffD = 0;

        for (i=0; i<bGROUPS; i++)
        {
          if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
          {
            GetMonGrpMaxDef(i);
            PushLong(&dwBuffC);
            wBuffD += sizeof(ulong);

            PushGrpDef(mpdeMonCan, i);
            wBuffD += sizeof(impulse);
          }
        }

        OutptrOutBuff(wBuffD);
      }
      else Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



void    OutDayCanDef(void)
{
uchar   i;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadDefDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == 1)
      {
        InitPushPtr();

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
uchar   i;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadDefMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == 1)
      {
        InitPushPtr();

        InitPushPtr();

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
uchar   i;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bDAYS)
    {
      if (LoadDefDay( (bDAYS+ibHardDay-bInBuff6) % bDAYS ) == 1)
      {
        InitPushPtr();

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
uchar   i;

  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff6 < bMONTHS)
    {
      if (LoadDefMon( (bMONTHS+ibHardMon-bInBuff6) % bMONTHS ) == 1)
      {
        InitPushPtr();

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


#endif
*/
