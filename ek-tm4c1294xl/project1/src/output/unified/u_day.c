/*------------------------------------------------------------------------------
U_DAY.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_ports.h"
#include        "../../memory/mem_realtime.h"
#include        "../../memory/mem_energy.h"
#include        "../../memory/mem_uni.h"
#include        "../../include/states.h"
#include        "../../include/queries_uni.h"
#include        "../../serial/ports.h"
#include        "../../realtime/realtime.h"
#include        "../../time/rtc.h"
#include        "../../time/timedate.h"
#include        "../../time/calendar.h"
#include        "../../special/recalc_def.h"
#include        "../../impulses/max_power.h"
#include        "../../hardware/watchdog.h"
#include        "../../groups.h"
#include        "../../energy.h"
#include        "../../energy2.h"
#include        "response_uni.h"
#include        "u_def.h"
#include        "u_day.h"



void    GetDefCanDayUni(void) 
{
uchar   i,j,k;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0) || (bInBuffC != 0))
    Result2_Info(bUNI_BADDATA, 1);
  else if ((bInBuff9 == 0) || (bInBuffD == 0)) 
    Result2_Info(bUNI_BADDATA, 2);
  else if (bInBuff7 > bCANALS)
    Result2_Info(bUNI_BADDATA, 3);
  else if (bInBuff7+bInBuff9-1 > bCANALS)
    Result2_Info(bUNI_BADDATA, 4);
  else if (bInBuffB >= wHOURS/48)
    Result2_Info(bUNI_BADDATA, 5);
  else if (bInBuffB + bInBuffD >= wHOURS/48)
    Result2_Info(bUNI_BADDATA, 6);
  else
  {
    InitPushUni();
    k = (((bInBuff9-1) / 16)+1)*2;

    for (j=bInBuffB; j<bInBuffB+bInBuffD; j++)
    {
      ResetWDT();
      memset(&mpbDefUni, 0, sizeof(mpbDefUni));

      uint iwHou = GetDayHouIndex(j);
      for (i=0; i<48; i++)
      {
        LoadImpHouFree(iwHou);

        uchar c;
        for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
        {   
          if (GetDefCan(c-1) == 1) 
            mpbDefUni[k-1 - ((c - bInBuff7) / 8)] |= (uchar)(0x01 << ((c - bInBuff7) % 8));
        }

        if (++iwHou >= wHOURS) iwHou = 0;
      }

      Push(mpbDefUni, k);
    }

    ulong dw = DateToDayIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = DayIndexToDate(dw);

    Output2_Code((uint)k*bInBuffD, 0, &ti);
  }
}



void    GetDefGrpDayUni(void) 
{
uchar   i,j,k;

  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0) || (bInBuffC != 0))
    Result2_Info(bUNI_BADDATA, 1);
  else if ((bInBuff9 == 0) || (bInBuffD == 0)) 
    Result2_Info(bUNI_BADDATA, 2);
  else if (bInBuff7 > bGROUPS)
    Result2_Info(bUNI_BADDATA, 3);
  else if (bInBuff7+bInBuff9-1 > bGROUPS)
    Result2_Info(bUNI_BADDATA, 4);
  else if (bInBuffB >= wHOURS/48)
    Result2_Info(bUNI_BADDATA, 5);
  else if (bInBuffB + bInBuffD >= wHOURS/48)
    Result2_Info(bUNI_BADDATA, 6);
  else
  {
    InitPushUni();
    k = (((bInBuff9-1) / 16)+1)*2;

    for (j=bInBuffB; j<bInBuffB+bInBuffD; j++)
    {
      ResetWDT();
      memset(&mpbDefUni, 0, sizeof(mpbDefUni));

      uint iwHou = GetDayHouIndex(j);
      for (i=0; i<48; i++)
      {
        LoadImpHouFree(iwHou);

        uchar g;
        for (g=bInBuff7; g<bInBuff7+bInBuff9; g++)
        {   
          if (GetDefGrp(g-1) == 1) 
            mpbDefUni[k-1 - ((g - bInBuff7) / 8)] |= (uchar)(0x01 << ((g - bInBuff7) % 8));
        }

        if (++iwHou >= wHOURS) iwHou = 0;
      }

      Push(mpbDefUni, k);
    }

    ulong dw = DateToDayIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = DayIndexToDate(dw);

    Output2_Code((uint)k*bInBuffD, 0, &ti);
  }
}
