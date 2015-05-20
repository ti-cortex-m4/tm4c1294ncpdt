/*------------------------------------------------------------------------------
U_CNT.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_extended_1.h"
#include "../../memory/mem_extended_4.h"
#include "../../memory/mem_extended_5.h"
#include "../../memory/mem_extended_4t.h"
#include "../../include/states.h"
#include "../../include/queries_uni.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "../../devices/automatic_4t.h"
#include "../../devices/extended_4.h"
#include "../../devices/extended_4t.h"
#include "../../time/rtc.h"
#include "../../time/calendar.h"
#include "../../energy2.h"
#include "response_uni.h"
#include "u_float.h"
#include "u_cnt.h"



void    PushCntCanMonAllUni(uchar  ibCan, uchar  ibMon)
{
  if (GetDigitalDevice(ibCan) == 0)
  {
    real re = mpreCntMonCan[ PrevSoftMon() ][ibCan];
    PushFloatUni(ST4_OK, re);
  }
  else
  {
    value6 va = mpCntMonCan4[ibCan];
    PushFloatUni(va.bSelf, va.reSelf);
  }
}


void    GetCntCanMonAllUni(void) 
{
  if ((bInBuff6 != 0) || (bInBuff8 != 0) || (bInBuffA != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuffB >= bMONTHS)
    Result2(bUNI_BADDATA);
  else
  { 
    ulong dw = DateToMonIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = MonIndexToDate(dw);

    InitPushUni();

    uchar ibMon = (bMONTHS+ibHardMon-bInBuffB-1) % bMONTHS;
    LoadCntMon(ibMon);
    LoadExt4Values(ibMon);

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      PushCntCanMonAllUni(c-1, ibMon);
    }

    Output2_Code((uint)4*bInBuff9, ((boExt4Flag == TRUE) ? bUNI_OK : bUNI_NOTREADY), ti);
  }
}



void    PushCntCanMonTarUni(uchar  ibCan, uchar  ibMon, uchar  ibTar)
{
  if (SupportedCntMonCanTariff(ibCan) == false)
  {
    real re = 0;
    PushFloatUni(ST4_NOTSUPPORTED, re);
  }
  else
  {
    value4t va = mpCntMonCan4T[ibCan];
    PushFloatUni(va.bStatus, va.mpdbValuesT[ibTar]);
  }
}


void    GetCntCanMonTarUni(void) 
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
    ulong dw = DateToMonIndex(*GetCurrTimeDate());
    dw -= bInBuffB;
    time ti = MonIndexToDate(dw);

    InitPushUni();

    uchar ibMon = (bMONTHS+ibHardMon-bInBuffB-1) % bMONTHS;
    LoadExt4TValues(ibMon);

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      uchar t;
      for (t=bInBuffC; t<bInBuffC+bInBuffD; t++)
      {
        PushCntCanMonTarUni(c-1, ti.bMonth-1, t-1);
      }
    }

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((boExt4TFlag == TRUE) ? bUNI_OK : bUNI_NOTREADY), ti);
  }
}


void    GetCntCanMonUni(void) 
{
  if (bInBuffC == 0)
    GetCntCanMonAllUni();
  else
    GetCntCanMonTarUni();
}



void    GetCntCanAllUni(void) 
{
  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bCANALS)
    Result2(bUNI_BADDATA);
  else
  { 
    InitPushUni();

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      PushTime(mptiEsc_S[c-1]);
      PushFloat(mpreEsc_S[c-1]);
    }

    Output2_Code((uint)(4+6)*bInBuff9, ((boDsblEscS != TRUE) ? bUNI_OK : bUNI_NOTREADY), *GetCurrTimeDate());
  }
}


void    GetCntCanTarUni(void) 
{
  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9-1 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuffA > bTARIFFS)
    Result2(bUNI_BADDATA);
  else if (bInBuffA+bInBuffB-1 > bTARIFFS)
    Result2(bUNI_BADDATA);
  else
  { 
    InitPushUni();

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      uchar t;
      for (t=bInBuffA; t<bInBuffA+bInBuffB; t++)
      {
        PushTime(mpCntDayCan5[c-1].tiUpdate);
        PushFloat(mpCntDayCan5[c-1].stValue.mpdbValuesT[t-1]);
      }
    }

    Output2_Code((uint)(4+6)*bInBuff9*bInBuffB, ((boExt5Flag == TRUE) ? bUNI_OK : bUNI_NOTREADY), *GetCurrTimeDate());
  }
}


void    GetCntCanUni(void) 
{
  if (bInBuffA == 0)
    GetCntCanAllUni();
  else
    GetCntCanTarUni();
}
