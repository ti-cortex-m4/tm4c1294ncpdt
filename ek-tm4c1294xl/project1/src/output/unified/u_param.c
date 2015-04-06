/*------------------------------------------------------------------------------
U_PARAM.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_ports.h"
//#include        "../../memory/mem_realtime.h"
//#include        "../../memory/mem_energy.h"
//#include        "../../memory/mem_energy_spec.h"
#include        "../../include/states.h"
//#include        "../../include/queries_uni.h"
#include        "../../serial/ports.h"
//#include        "../../realtime/realtime.h"
//#include        "../../time/rtc.h"
//#include        "../../time/timedate.h"
//#include        "../../time/calendar.h"
#include        "../../digitals/params/params.h"
#include        "../../digitals/params/params2.h"
#include        "../../digitals/params/params_storage.h"
//#include        "../../groups.h"
//#include        "../../energy.h"
//#include        "../../impulses/max_power.h"
//#include        "../../energy2.h"
#include        "response_uni.h"
#include        "u_param.h"



uchar   GetParamLineUni(uchar  i)
{
  switch (i)
  {
    case  0: return PAR_P1;
    case  1: return PAR_P2;
    case  2: return PAR_P3;
    case  3: return PAR_P;

    case  4: return PAR_Q1;
    case  5: return PAR_Q2;
    case  6: return PAR_Q3;
    case  7: return PAR_Q;

    case  8: return PAR_S1;
    case  9: return PAR_S2;
    case 10: return PAR_S3;
    case 11: return PAR_S;

    case 12: return PAR_C1;
    case 13: return PAR_C2;
    case 14: return PAR_C3;
    case 15: return PAR_C;

    case 16: return PAR_U1;
    case 17: return PAR_U2;
    case 18: return PAR_U3;

    case 19: return PAR_I1;
    case 20: return PAR_I2;
    case 21: return PAR_I3;

    case 22: return PAR_F;

    default: return 0xFF;
  }
}



uint    GetParamIndexUni(void)
{
uint    i;

  for (i=0; i<wPARAMS; i++)
  {
    if( (mpdiParam[i].ibPort   == diT.ibPort) &&
        (mpdiParam[i].ibPhone  == diT.ibPhone) &&
        (mpdiParam[i].bDevice  == diT.bDevice) &&
        (mpdiParam[i].bAddress == diT.bAddress) &&
        (mpdiParam[i].ibLine   == diT.ibLine)) return i;
  }

  return 0xFFFF;
}



void    FixParamsUni(void)
{
  if ((diT.ibLine == PAR_P) || (diT.ibLine == PAR_P1) || (diT.ibLine == PAR_P2) || (diT.ibLine == PAR_P3))
  {
    if ((diT.bDevice == 3) && (boFixParamBugs == FALSE))
    {
      reBuffA *= 1000;
    }
  }

  if ((diT.ibLine == PAR_Q) || (diT.ibLine == PAR_Q1) || (diT.ibLine == PAR_Q2) || (diT.ibLine == PAR_Q3))
  {
    if ((diT.bDevice == 3) && (boFixParamBugs == FALSE))
    {
      reBuffA *= 1000;
    }
  }

  if ((diT.ibLine == PAR_I) || (diT.ibLine == PAR_I1) || (diT.ibLine == PAR_I2) || (diT.ibLine == PAR_I3))
  {
    if (((diT.bDevice == 2) || (diT.bDevice == 8) || (diT.bDevice == 12)) && (boFixParamBugs == FALSE)) 
    { 
    }
    else if ((diT.bDevice == 3) && (boFixParamBugs == FALSE)) 
    { 
    }
    else
    {    
      reBuffA /= 1000;
    }
  }
}



void    PushParamsUni(uchar  ibPtr)
{
uchar   i;
uint    j;

  for (ibGrp=0; ibGrp<23; ibGrp++)
  {
    if ((InBuff(ibPtr + 7 - ibGrp/8) & (0x01 << ibGrp%8)) != 0) 
    {
      wBuffD += sizeof(real);

      i = GetParamLineUni(ibGrp);
      if (i == 0xFF)
      {
        reBuffA = 0; 
        PushRealUni(ST4_NOTSUPPORTED, &reBuffA);
      }
      else
      {
        diT = mpdiDevicesUni[ibCan-1];
        diT.ibLine = i;

        j = GetParamIndexUni();
        if (j == 0xFFFF)
        {
          reBuffA = 0; 
          PushRealUni(ST4_NOTPRESENTED, &reBuffA);
        }
        else
        {
          reBuffA = mpreParBuff[ PrevSoftTim() ][ j ];
              
          if (_chkfloat_(reBuffA) < 2)
          {
            FixParamsUni();

            PushRealUni(ST4_OK, &reBuffA);
          }
          else
            PushRealUni(ST4_BADDIGITAL, &reBuffA);
        }
      }
    }
  }
}



void    GetTimeAltParamUni(int  i)
{
  tiAlt = *GetCurrTimeDate();
  if (boQuickParam == TRUE)
  {
    dwBuffC = DateToMntIndex();
    dwBuffC -= i;
    MntIndexToDate(dwBuffC);
  }
  else
  {
    dwBuffC = DateToHouIndex();
    dwBuffC -= i;
    HouIndexToDate(dwBuffC);
  }
}



void    GetParamUni1(void)
{
  MakeDevicesUni();

  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > cbDevicesUni)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9 > cbDevicesUni + 1)
    Result2(bUNI_BADDATA);
  else if (bInBuffA*0x100+bInBuffB >= wTIMES)
    Result2(bUNI_BADDATA);
  else
  {
    iwTim = bInBuffA*0x100+bInBuffB;
    LoadParTim((wTIMES + iwHardTim - iwTim) % wTIMES);

    wBuffD = 0;

    InitPushUni();
    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
      PushParamsUni(12);

    GetTimeAltParamUni(iwTim);

    Output2_Code(wBuffD, ((boEnableParam == TRUE) ? bUNI_OK : bUNI_NOTREADY), &tiAlt);
  }
}



void    GetParamUni2(void)
{
uint    i,j;

  MakeDevicesUni();

  i = bInBuff6*0x100+bInBuff7;
  j = bInBuff8*0x100+bInBuff9;

  if (i > cwParamTim*cbDevicesUni)
    Result2_Info(bUNI_BADDATA, 1);
  else if (i+j-1 > cwParamTim*cbDevicesUni)
    Result2_Info(bUNI_BADDATA, 2);
  else
  {
    j += i;

    InitPushUni();
    PushInt(cwParamTim*cbDevicesUni);
    wBuffD = 2;

    while (i < j)
    {
      ibCan = ((i-1) % cbDevicesUni)+1;
      iwTim = (i-1) / cbDevicesUni;
      i++;

      LoadParTim((wTIMES + iwHardTim - iwTim) % wTIMES);

      GetTimeAltParamUni(iwTim);

      PushInt(ibCan);
      Push(&tiAlt, sizeof(time));
      wBuffD += 2+6;

      PushParamsUni(10);

      if (wBuffD >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      ResetWDT();
    }

    Output2_Code(wBuffD, ((boEnableParam == TRUE) ? bUNI_OK : bUNI_NOTREADY), &tiAlt);
  }
}

#endif
