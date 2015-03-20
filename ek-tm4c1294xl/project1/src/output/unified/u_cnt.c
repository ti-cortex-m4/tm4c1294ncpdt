/*------------------------------------------------------------------------------
U_CNT.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "rtc.h"
#include        "timedate.h"
#include        "queries2.h"
#include        "ports.h"
#include        "general.h"
#include        "engine.h"
#include        "sensors.h"
#include        "nexttime.h"
#include        "postinput2.h"
#include        "automatic3.h"



#ifndef MODBUS

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
    tiAlt = *PGetCurrTimeDate();
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

    Output2_Code((uint)4*bInBuff9, ((boExt4Flag == boTrue) ? bUNI_OK : bUNI_NOTREADY), &tiAlt);
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
    tiAlt = *PGetCurrTimeDate();
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

    Output2_Code((uint)4*bInBuff9*bInBuffD, ((boExt4TFlag == boTrue) ? bUNI_OK : bUNI_NOTREADY), &tiAlt);
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

    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
    {
      tiAlt = mptiEsc_S[ibCan-1];
      Push(&tiAlt, sizeof(time));
      reBuffA = mpreEsc_S[ibCan-1];
      PushReal();
    }

    tiAlt = *PGetCurrTimeDate();

    Output2_Code((uint)(4+6)*bInBuff9, ((boDisableEsc3 != boTrue) ? bUNI_OK : bUNI_NOTREADY), &tiAlt);
  }
}



void    GetCntCanTarUni(void) 
{
uchar   i;

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

    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
    {
      for (i=bInBuffA; i<bInBuffA+bInBuffB; i++)
      {
        tiAlt = mpvaValue51[ibCan-1].tiSelf;
        Push(&tiAlt, sizeof(time));
        reBuffA = mpvaValue51[ibCan-1].vaValue50.mpreSelf[i-1];
        PushReal();
      }
    }

    tiAlt = *PGetCurrTimeDate();

    Output2_Code((uint)(4+6)*bInBuff9*bInBuffB, ((boExt5Flag == boTrue) ? bUNI_OK : bUNI_NOTREADY), &tiAlt);
  }
}



void    GetCntCanUni(void) 
{
  if (bInBuffA == 0)
    GetCntCanAllUni();
  else
    GetCntCanTarUni();
}

#endif
*/
