/*------------------------------------------------------------------------------
U_ENERGY.C


------------------------------------------------------------------------------*/
/*
#include        <string.h>
#include        "main.h"
#include        "xdata.h"
#include        "rtc.h"
#include        "nexttime.h"
#include        "timedate.h"
#include        "queries2.h"
#include        "ports.h"
#include        "groups.h"
#include        "engine.h"
#include        "energy.h"
#include        "power.h"
#include        "recalc_def.h"
#include        "general.h"
#include        "postinput2.h"



#ifndef MODBUS

void    GetCanCurrDef(impulse  _xdata  *mpimT, uchar  ibCanal);
void    GetGrpCurrDef(impulse  _xdata  *mpimT, uchar  ibGroup);



void    GetDayCanMaxDef2(void)
{
  dwBuffC = (ulong)48;
}


void    GetDayGrpMaxDef2(uchar  ibGroup)
{
  GetDayCanMaxDef2();
  dwBuffC *= GetGroupsSize(ibGroup);
}


void    GetMonCanMaxDef2(void)
{
  tiAlt.bMonth = ((12 - 1 + tiCurr.bMonth - bInBuffB) % 12) + 1;
  tiAlt.bYear = (tiAlt.bMonth > tiCurr.bMonth) ? tiCurr.bYear-1 : tiCurr.bYear;

  dwBuffC = (ulong)48*DaysInMonth();
}


void    GetMonGrpMaxDef2(uchar  ibGroup)
{
  GetMonCanMaxDef2();
  dwBuffC *= GetGroupsSize(ibGroup);
}



bit     CheckDefCanDayUni(void)
{
  LoadDefDay((bDAYS+ibHardDay-bInBuffB) % bDAYS);

  for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
  {
    GetDayCanMaxDef2();
    GetCanCurrDef(mpdeDayCan, ibCan-1);

    if (dwBuffC != dwTmp) return 1;
  }

  return 0;
}


bit     CheckDefGrpDayUni(void)
{
  LoadDefDay((bDAYS+ibHardDay-bInBuffB) % bDAYS);

  for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
  {
    GetDayGrpMaxDef2(ibGrp-1);
    GetGrpCurrDef(mpdeDayCan, ibGrp-1);

    if (dwBuffC != dwTmp) return 1;
  }

  return 0;
}


bit     CheckDefCanMonUni(void)
{
  LoadDefMon((bMONTHS+ibHardMon-bInBuffB) % bMONTHS);

  for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
  {
    GetMonCanMaxDef2();
    GetCanCurrDef(mpdeMonCan, ibCan-1);

    if (dwBuffC != dwTmp) return 1;
  }

  return 0;
}


bit     CheckDefGrpMonUni(void)
{
  LoadDefMon((bMONTHS+ibHardMon-bInBuffB) % bMONTHS);

  for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
  {
    GetMonGrpMaxDef2(ibGrp-1);
    GetGrpCurrDef(mpdeMonCan, ibGrp-1);

    if (dwBuffC != dwTmp) return 1;
  }

  return 0;
}



void    GetEngCanDayUni(void)
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB >= bDAYS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC > bTARIFFS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC+bInBuffD-1 > bTARIFFS)
    Result2(bUNI_BADDATA);
  else
  { 
    InitPushUni();
    LoadImpDay((bDAYS+ibHardDay-bInBuffB) % bDAYS);

    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
    {
      for (i=bInBuffC; i<bInBuffC+bInBuffD; i++)
      {
        reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ], ibCan-1, 0x01 << (i-1));
        PushReal();
      }
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToDayIndex();
    dwBuffC -= bInBuffB;
    DayIndexToDate(dwBuffC);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((CheckDefCanDayUni() == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}


void    GetEngGrpDayUni(void)
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB >= bDAYS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC > bTARIFFS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC+bInBuffD-1 > bTARIFFS)
    Result2(bUNI_BADDATA);
  else
  { 
    InitPushUni();
    LoadImpDay((bDAYS+ibHardDay-bInBuffB) % bDAYS);

    for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
    {
      for (i=bInBuffC; i<bInBuffC+bInBuffD; i++)
      {
        reBuffA = *PGetGrpImp2RealEng(mpimDayCan[ PrevSoftDay() ], ibGrp-1, 0x01 << (i-1));
        PushReal();
      }
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToDayIndex();
    dwBuffC -= bInBuffB;
    DayIndexToDate(dwBuffC);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((CheckDefGrpDayUni() == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}



void    GetEngCanMonUni(void)
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB >= bMONTHS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC > bTARIFFS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC+bInBuffD-1 > bTARIFFS)
    Result2(bUNI_BADDATA);
  else
  { 
    InitPushUni();
    LoadImpMon((bMONTHS+ibHardMon-bInBuffB) % bMONTHS);

    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
    {
      for (i=bInBuffC; i<bInBuffC+bInBuffD; i++)
      {
        reBuffA = *PGetCanImp2RealEng(mpimMonCan[ PrevSoftMon() ], ibCan-1, 0x01 << (i-1));
        PushReal();
      }
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToMonIndex();
    dwBuffC -= bInBuffB;
    MonIndexToDate(dwBuffC);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((CheckDefCanMonUni() == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}


void    GetEngGrpMonUni(void)
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB >= bMONTHS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC > bTARIFFS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC+bInBuffD-1 > bTARIFFS)
    Result2(bUNI_BADDATA);
  else
  { 
    InitPushUni();
    LoadImpMon((bMONTHS+ibHardMon-bInBuffB) % bMONTHS);

    for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
    {
      for (i=bInBuffC; i<bInBuffC+bInBuffD; i++)
      {
        reBuffA = *PGetGrpImp2RealEng(mpimMonCan[ PrevSoftMon() ], ibGrp-1, 0x01 << (i-1));
        PushReal();
      }
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToMonIndex();
    dwBuffC -= bInBuffB;
    MonIndexToDate(dwBuffC);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((CheckDefGrpMonUni() == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}



void    GetMaxGrpDayUni(void)
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB >= bDAYS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC > bTARIFFS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC+bInBuffD-1 > bTARIFFS)
    Result2(bUNI_BADDATA);
  else
  { 
    InitPushUni();
    LoadPowDay((bDAYS+ibHardDay-bInBuffB) % bDAYS);

    for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
    {
      for (i=bInBuffC; i<bInBuffC+bInBuffD; i++)
      {
        reBuffA = *PGetGrpMaxPowReal(&mppoDayGrp[ PrevSoftDay() ], ibGrp-1, i-1);
        PushReal();
        tiAlt = *PGetGrpMaxPowTime(mppoDayGrp[ PrevSoftDay() ], ibGrp-1, i-1);
        PushChar(tiAlt.bDay);
        PushChar(tiAlt.bHour*2 + tiAlt.bMinute/30);
      }
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToDayIndex();
    dwBuffC -= bInBuffB;
    DayIndexToDate(dwBuffC);

    Output2_Code((uint)6*bInBuff9*bInBuffD, ((CheckDefGrpDayUni() == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}


void    GetMaxGrpMonUni(void)
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB >= bMONTHS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC > bTARIFFS)
    Result2(bUNI_BADDATA);
  else if (bInBuffC+bInBuffD-1 > bTARIFFS)
    Result2(bUNI_BADDATA);
  else
  { 
    InitPushUni();
    LoadPowMon((bMONTHS+ibHardMon-bInBuffB) % bMONTHS);

    for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
    {
      for (i=bInBuffC; i<bInBuffC+bInBuffD; i++)
      {
        reBuffA = *PGetGrpMaxPowReal(&mppoMonGrp[ PrevSoftMon() ], ibGrp-1, i-1);
        PushReal();
        tiAlt = *PGetGrpMaxPowTime(mppoMonGrp[ PrevSoftMon() ], ibGrp-1, i-1);
        PushChar(tiAlt.bDay);
        PushChar(tiAlt.bHour*2 + tiAlt.bMinute/30);
      }
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToMonIndex();
    dwBuffC -= bInBuffB;
    MonIndexToDate(dwBuffC);

    Output2_Code((uint)6*bInBuff9*bInBuffD, ((CheckDefGrpMonUni() == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}

#endif
*/
