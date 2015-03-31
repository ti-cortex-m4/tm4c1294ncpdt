/*------------------------------------------------------------------------------
U_ENERGY.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_ports.h"
#include        "../../memory/mem_realtime.h"
#include        "../../memory/mem_energy.h"
#include        "../../memory/mem_energy_spec.h"
#include        "../../include/states.h"
#include        "../../include/queries_uni.h"
#include        "../../serial/ports.h"
#include        "../../realtime/realtime.h"
#include        "../../time/rtc.h"
#include        "../../time/timedate.h"
#include        "../../time/calendar.h"
#include        "../../special/recalc_def.h"
#include        "../../energy.h"
#include        "../../energy2.h"
#include        "response_uni.h"
#include        "u_energy.h"


/*
#ifndef MODBUS

void    GetCanCurrDef(impulse  _xdata  *mpimT, uchar  ibCanal);
void    GetGrpCurrDef(impulse  _xdata  *mpimT, uchar  ibGroup);
*/


ulong   GetDayCanMaxDefCount(void)
{
  return (ulong)48;
}

/*
void    GetDayGrpMaxDef2(uchar  ibGroup)
{
  GetDayCanMaxDefCount();
  dwBuffC *= GetGroupsSize(ibGroup);
}
*/

ulong   GetMonCanMaxDefCount(uchar  bMonth)
{
  uchar m = ((12 - 1 + tiCurr.bMonth - bInBuffB) % 12) + 1;
  uchar y = (bMonth > tiCurr.bMonth) ? tiCurr.bYear-1 : tiCurr.bYear;

  return (ulong)48*GetDaysInMonthYM(y, m);
}

/*
void    GetMonGrpMaxDef2(uchar  ibGroup)
{
  GetMonCanMaxDefCount();
  dwBuffC *= GetGroupsSize(ibGroup);
}
*/


bool    CheckDefCanDayUni(void)
{
  LoadDefDay((bDAYS+ibHardDay-bInBuffB) % bDAYS);

  uchar c;
  for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
  {
    ulong dw1 = GetDayCanMaxDefCount();
    GetCanCurrDef(mpdeDayCan, c-1);

    if (dw1 != dwTmp) return 1;
  }

  return 0;
}

/*
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
*/

bool    CheckDefCanMonUni(uchar  bMonth)
{
  LoadDefMon((bMONTHS+ibHardMon-bInBuffB) % bMONTHS);

  uchar c;
  for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
  {
    ulong dw1 = GetMonCanMaxDefCount(bMonth);
    GetCanCurrDef(mpdeMonCan, c-1);

    if (dw1 != dwTmp) return 1;
  }

  return 0;
}

/*
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
*/


void    GetEngCanDayUni(void)
{
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

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      uchar i;
      for (i=bInBuffC; i<bInBuffC+bInBuffD; i++)
      {
        PushReal(GetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ], c-1, 0x01 << (i-1)));
      }
    }

    ulong dw = DateToDayIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = DayIndexToDate(dw);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((CheckDefCanDayUni() == 0) ? bUNI_OK : bUNI_DEFECT), &ti);
  }
}

/*
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

    tiAlt = *GetCurrTimeDate();
    dwBuffC = DateToDayIndex();
    dwBuffC -= bInBuffB;
    DayIndexToDate(dwBuffC);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((CheckDefGrpDayUni() == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}
*/


void    GetEngCanMonUni(void)
{
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

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      uchar i;
      for (i=bInBuffC; i<bInBuffC+bInBuffD; i++)
      {
        PushReal(GetCanImp2RealEng(mpimMonCan[ PrevSoftMon() ], c-1, 0x01 << (i-1)));
      }
    }

    ulong dw = DateToMonIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = MonIndexToDate(dw);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((CheckDefCanMonUni(ti.bMonth) == 0) ? bUNI_OK : bUNI_DEFECT), &ti);
  }
}

/*
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

    tiAlt = *GetCurrTimeDate();
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

    tiAlt = *GetCurrTimeDate();
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

    tiAlt = *GetCurrTimeDate();
    dwBuffC = DateToMonIndex();
    dwBuffC -= bInBuffB;
    MonIndexToDate(dwBuffC);

    Output2_Code((uint)6*bInBuff9*bInBuffD, ((CheckDefGrpMonUni() == 0) ? bUNI_OK : bUNI_DEFECT), &tiAlt);
  }
}

#endif
*/
