/*------------------------------------------------------------------------------
U_DAY.C


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
#include        "engine.h"
#include        "energy.h"
#include        "general.h"
#include        "watchdog.h"
#include        "postinput2.h"



#ifndef MODBUS

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

      iwHou = PrevDayIndex(j);
      for (i=0; i<48; i++)
      {
        LoadImpHouFree(iwHou);

        for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
        {   
          if (GetDefCan(ibCan-1) == 1) 
            mpbDefUni[k-1 - ((ibCan - bInBuff7) / 8)] |= (uchar)(0x01 << ((ibCan - bInBuff7) % 8));
        }

        if (++iwHou >= wHOURS) iwHou = 0;
      }

      Push(mpbDefUni, k);
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToDayIndex();
    dwBuffC -= bInBuffB;
    DayIndexToDate(dwBuffC);

    Output2_Code((uint)k*bInBuffD, 0, &tiAlt);
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

      iwHou = PrevDayIndex(j);
      for (i=0; i<48; i++)
      {
        LoadImpHouFree(iwHou);

        for (ibGrp=bInBuff7; ibGrp<bInBuff7+bInBuff9; ibGrp++)
        {   
          if (GetDefGrp(ibGrp-1) == 1) 
            mpbDefUni[k-1 - ((ibGrp - bInBuff7) / 8)] |= (uchar)(0x01 << ((ibGrp - bInBuff7) % 8));
        }

        if (++iwHou >= wHOURS) iwHou = 0;
      }

      Push(mpbDefUni, k);
    }

    tiAlt = *PGetCurrTimeDate();
    dwBuffC = DateToDayIndex();
    dwBuffC -= bInBuffB;
    DayIndexToDate(dwBuffC);

    Output2_Code((uint)k*bInBuffD, 0, &tiAlt);
  }
}

#endif
*/
