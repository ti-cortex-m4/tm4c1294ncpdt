/*------------------------------------------------------------------------------
UNI_CNT!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_extended_1.h"
#include "../../memory/mem_extended_4.h"
#include "../../memory/mem_extended_5.h"
#include "../../memory/mem_extended_4t.h"
#include "../../include/queries_uni.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "../../digitals/extended/automatic_4t.h"
#include "../../digitals/extended/extended_4.h"
#include "../../digitals/extended/extended_4t.h"
#include "../../time/rtc.h"
#include "../../time/calendar.h"
#include "../../energy2.h"
#include "response_uni.h"
#include "uni_float.h"
#include "uni_cnt.h"



uchar   PushCntCanMonAllUni(uchar  ibCan, uchar  ibMon, bool  fDouble)
{
  if (GetDigitalDevice(ibCan) == 0)
  {
    double db = mpdbCntMonCan[ PrevSoftMon() ][ibCan];
    return PushFloatOrDoubleUni(ST_OK, db, fDouble);
  }
  else
  {
    value6 vl = mpCntMonCan4[ibCan];
    return PushFloatOrDoubleUni(vl.bStatus, vl.dbValue, fDouble);
  }
}


void    GetCntCanMonAllUni(bool  fDouble)
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
    uint wSize = 0;

    uchar ibMon = (bMONTHS+ibHardMon-bInBuffB-1) % bMONTHS; // неизвестно, нужно ли здесь -1
    LoadCntMon(ibMon);
    LoadExt4Values(ibMon);

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      wSize += PushCntCanMonAllUni(c-1, ibMon, fDouble);
    }

    Output2_Code(wSize, ((fExt4Flag == true) ? bUNI_OK : bUNI_NOTREADY), ti);
  }
}



uchar   PushCntCanMonTarUni(uchar  ibCan, uchar  ibMon, uchar  ibTrf, bool  fDouble)
{
  if (SupportedExtended4T(ibCan) == false)
  {
    return PushFloatOrDoubleUni(ST_NOTSUPPORTED, 0, fDouble);
  }
  else
  {
    value4t vl = mpCntMonCan4T[ibCan];
    return PushFloatOrDoubleUni(vl.bStatus, vl.mpdbValuesT[ibTrf], fDouble);
  }
}


void    GetCntCanMonTrfUni(bool  fDouble)
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
    uint wSize = 0;

    uchar ibMon = (bMONTHS+ibHardMon-bInBuffB) % bMONTHS;
    LoadExt4TValues(ibMon);

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      uchar t;
      for (t=bInBuffC; t<bInBuffC+bInBuffD; t++)
      {
        wSize += PushCntCanMonTarUni(c-1, ti.bMonth-1, t-1, fDouble);
      }
    }

    Output2_Code(wSize, ((fExt4TFlag == true) ? bUNI_OK : bUNI_NOTREADY), ti);
  }
}


void    GetCntCanMonUni(bool  fDouble)
{
  if (bInBuffC == 0)
    GetCntCanMonAllUni(fDouble);
  else
    GetCntCanMonTrfUni(fDouble);
}



void    GetCntCanAllUni(bool  fDouble)
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
    uint wSize = 0;

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      wSize += PushTime(mptiEsc_S[c-1]);
      wSize += PushFloatOrDouble(mpdbEsc_S[c-1], fDouble);
    }

    Output2_Code(wSize, ((boDsblEscS != true) ? bUNI_OK : bUNI_NOTREADY), *GetCurrTimeDate());
  }
}


void    GetCntCanTrfUni(bool  fDouble)
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
    uint wSize = 0;

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      uchar t;
      for (t=bInBuffA; t<bInBuffA+bInBuffB; t++)
      {
        wSize += PushTime(mpCntDayCan5[c-1].tiUpdate);
        wSize += PushFloatOrDouble(mpCntDayCan5[c-1].stValue.mpdbValuesT[t-1], fDouble);
      }
    }

    Output2_Code(wSize, ((fExt5Flag == true) ? bUNI_OK : bUNI_NOTREADY), *GetCurrTimeDate());
  }
}


void    GetCntCanUni(bool  fDouble)
{
  if (bInBuffA == 0)
    GetCntCanAllUni(fDouble);
  else
    GetCntCanTrfUni(fDouble);
}
