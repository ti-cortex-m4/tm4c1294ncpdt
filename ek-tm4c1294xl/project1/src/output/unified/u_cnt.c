/*------------------------------------------------------------------------------
U_CNT.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_ports.h"
#include        "../../memory/mem_extended_1.h"
#include        "../../memory/mem_extended_5.h"
#include        "../../include/states.h"
#include        "../../include/queries_uni.h"
#include        "../../serial/ports.h"
#include        "../../time/rtc.h"
#include        "response_uni.h"
#include        "u_cnt.h"


/*
void    PushCntCanMonAllUni(uchar  ibCanal, uchar  ibMonth)
{
  if (GetDigitalDevice(ibCanal) == 0)
  {
    reBuffA = mpreCntMonCan[ PrevSoftMon() ][ibCanal]; 
    PushRealUni(ST4_OK, &reBuffA);
  }
  else
  {
    v6Buff = mpCntMonCan4[ibMonth][ibCanal]; 
    PushRealUni(v6Buff.bSelf, &v6Buff.reSelf);
  }
}


void    GetCntCanMonAllUni(void) 
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
  else
  { 
    tiAlt = *GetCurrTimeDate();
    dwBuffC = DateToMonIndex();
    dwBuffC -= bInBuffB;
    MonIndexToDate(dwBuffC);

    InitPushUni();
    i = (bMONTHS+ibHardMon-bInBuffB-1) % bMONTHS;
    LoadCntMon(i);

    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
    {
      PushCntCanMonAllUni(ibCan-1, i);
    }

    Output2_Code((uint)4*bInBuff9, ((boExt4Flag == TRUE) ? bUNI_OK : bUNI_NOTREADY), &tiAlt);
  }
}



void    PushCntCanMonTarUni(uchar  ibCanal, uchar  ibMonth, uchar  ibTariff)
{
  if (IsCntMonCanTariff(ibCanal) == 0)
  {
    reBuffA = 0; 
    PushRealUni(ST4_NOTSUPPORTED, &reBuffA);
  }
  else
  {
    v6tBuff = mpCntMonCan4T[ibMonth][ibCanal]; 
    PushRealUni(v6tBuff.bSelf, &v6tBuff.mpreSelf[ibTariff]);
  }
}


void    GetCntCanMonTarUni(void) 
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
    tiAlt = *GetCurrTimeDate();
    dwBuffC = DateToMonIndex();
    dwBuffC -= bInBuffB;
    MonIndexToDate(dwBuffC);

    InitPushUni();

    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
    {
      for (i=bInBuffC; i<bInBuffC+bInBuffD; i++)
      {
        PushCntCanMonTarUni(ibCan-1, tiAlt.bMonth-1, i-1);
      }
    }

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((boExt4TFlag == TRUE) ? bUNI_OK : bUNI_NOTREADY), &tiAlt);
  }
}



void    GetCntCanMonUni(void) 
{
  if (bInBuffC == 0)
    GetCntCanMonAllUni();
  else
    GetCntCanMonTarUni();
}
*/


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
      PushTime(&mptiEsc_S[c-1]);
      PushFloat(mpreEsc_S[c-1]);
    }

    Output2_Code((uint)(4+6)*bInBuff9, ((boDsblEscS != TRUE) ? bUNI_OK : bUNI_NOTREADY), GetCurrTimeDate());
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

    uchar ibCan;
    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
    {
      uchar i;
      for (i=bInBuffA; i<bInBuffA+bInBuffB; i++)
      {
        PushTime(&mpvaValue51[ibCan-1].tiSelf);
        PushFloat(mpvaValue51[ibCan-1].vaValue50.mpreSelf[i-1]);
      }
    }

    Output2_Code((uint)(4+6)*bInBuff9*bInBuffB, ((boExt5Flag == TRUE) ? bUNI_OK : bUNI_NOTREADY), GetCurrTimeDate());
  }
}



void    GetCntCanUni(void) 
{
  if (bInBuffA == 0)
    GetCntCanAllUni();
  else
    GetCntCanTarUni();
}
