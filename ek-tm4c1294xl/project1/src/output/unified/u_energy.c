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
#include        "../../groups.h"
#include        "../../energy.h"
#include        "../../energy2.h"
#include        "response_uni.h"
#include        "u_energy.h"



ulong   GetCanCurrDef(impulse  *mpimT, uchar  ibCan);
ulong   GetGrpCurrDef(impulse  *mpimT, uchar  ibGrp);



ulong   GetDayCanMaxDefCount(void)
{
  return (ulong)48;
}


ulong   GetDayGrpMaxDefCount(uchar  ibGrp)
{
  return GetDayCanMaxDefCount() * GetGroupsSize(ibGrp);
}


ulong   GetMonCanMaxDefCount(uchar  bMonth)
{
  uchar m = ((12 - 1 + tiCurr.bMonth - bInBuffB) % 12) + 1;
  uchar y = (bMonth > tiCurr.bMonth) ? tiCurr.bYear-1 : tiCurr.bYear;

  return (ulong)48*GetDaysInMonthYM(y, m);
}


ulong   GetMonGrpMaxDefCount(uchar  bMonth, uchar  ibGrp)
{
  return GetMonCanMaxDefCount(bMonth) * GetGroupsSize(ibGrp);
}



bool    CheckDefCanDayUni(void)
{
  LoadDefDay((bDAYS+ibHardDay-bInBuffB) % bDAYS);

  uchar c;
  for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
  {
    ulong dw1 = GetDayCanMaxDefCount();
    ulong dw2 = GetCanCurrDef(mpdeDayCan, c-1);

    if (dw1 != dw2) return 1;
  }

  return 0;
}


bool    CheckDefGrpDayUni(void)
{
  LoadDefDay((bDAYS+ibHardDay-bInBuffB) % bDAYS);

  uchar g;
  for (g=bInBuff7; g<bInBuff7+bInBuff9; g++)
  {
    ulong dw1 = GetDayGrpMaxDefCount(g-1);
    ulong dw2 = GetGrpCurrDef(mpdeDayCan, g-1);

    if (dw1 != dw2) return 1;
  }

  return 0;
}


bool    CheckDefCanMonUni(uchar  bMonth)
{
  LoadDefMon((bMONTHS+ibHardMon-bInBuffB) % bMONTHS);

  uchar c;
  for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
  {
    ulong dw1 = GetMonCanMaxDefCount(bMonth);
    ulong dw2 = GetCanCurrDef(mpdeMonCan, c-1);

    if (dw1 != dw2) return 1;
  }

  return 0;
}


bool    CheckDefGrpMonUni(uchar  bMonth)
{
  LoadDefMon((bMONTHS+ibHardMon-bInBuffB) % bMONTHS);

  uchar g;
  for (g=bInBuff7; g<bInBuff7+bInBuff9; g++)
  {
    ulong dw1 = GetMonGrpMaxDefCount(bMonth, g-1);
    ulong dw2 = GetGrpCurrDef(mpdeMonCan, g-1);

    if (dw1 != dw2) return 1;
  }

  return 0;
}



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


void    GetEngGrpDayUni(void)
{
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

    uchar g;
    for (g=bInBuff7; g<bInBuff7+bInBuff9; g++)
    {
      uchar i;
      for (i=bInBuffC; i<bInBuffC+bInBuffD; i++)
      {
        PushReal(GetGrpImp2RealEng(mpimDayCan[ PrevSoftDay() ], g-1, 0x01 << (i-1)));
      }
    }

    ulong dw = DateToDayIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = DayIndexToDate(dw);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((CheckDefGrpDayUni() == 0) ? bUNI_OK : bUNI_DEFECT), &ti);
  }
}



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


void    GetEngGrpMonUni(void)
{
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

    uchar ibGrp;
    for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
    {
      uchar i;
      for (i=bInBuffC; i<bInBuffC+bInBuffD; i++)
      {
        PushReal(GetGrpImp2RealEng(mpimMonCan[ PrevSoftMon() ], ibGrp-1, 0x01 << (i-1)));
      }
    }

    ulong dw = DateToMonIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = MonIndexToDate(dw);

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((CheckDefGrpMonUni(ti.bMonth) == 0) ? bUNI_OK : bUNI_DEFECT), &ti);
  }
}


/*
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
