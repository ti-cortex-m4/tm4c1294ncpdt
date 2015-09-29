/*------------------------------------------------------------------------------
U_PARAM!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_params0.h"
#include "../../memory/mem_uni.h"
#include "../../include/queries_uni.h"
#include "../../serial/ports.h"
#include "../../realtime/realtime.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../hardware/watchdog.h"
#include "../../digitals/params/params.h"
#include "../../digitals/params/params2.h"
#include "../../digitals/params/params_storage.h"
#include "response_uni.h"
#include "u_config.h"
#include "uni_float.h"
#include "u_param.h"



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



uint    GetParamIndexUni(digital  di)
{
  uint i;
  for (i=0; i<wPARAMS; i++)
  {
    if( (mpdiParam[i].ibPort   == di.ibPort) &&
        (mpdiParam[i].ibPhone  == di.ibPhone) &&
        (mpdiParam[i].bDevice  == di.bDevice) &&
        (mpdiParam[i].bAddress == di.bAddress) &&
        (mpdiParam[i].ibLine   == di.ibLine)) return i;
  }

  return 0xFFFF;
}



float   FixParamsUni(digital  di, float  fl)
{
  if ((di.ibLine == PAR_P) || (di.ibLine == PAR_P1) || (di.ibLine == PAR_P2) || (di.ibLine == PAR_P3))
  {
    if ((di.bDevice == 3) && (boFixParamsBugs == false))
    {
      fl *= 1000;
    }
  }

  if ((di.ibLine == PAR_Q) || (di.ibLine == PAR_Q1) || (di.ibLine == PAR_Q2) || (di.ibLine == PAR_Q3))
  {
    if ((di.bDevice == 3) && (boFixParamsBugs == false))
    {
      fl *= 1000;
    }
  }

  if ((di.ibLine == PAR_I) || (di.ibLine == PAR_I1) || (di.ibLine == PAR_I2) || (di.ibLine == PAR_I3))
  {
    if (((di.bDevice == 2) || (di.bDevice == 8) || (di.bDevice == 12)) && (boFixParamsBugs == false))
    {
    }
    else if ((di.bDevice == 3) && (boFixParamsBugs == false))
    {
    }
    else
    {
      fl /= 1000;
    }
  }

  return fl;
}



uint    PushParamsUni(uchar  ibPtr, uchar  ibCan)
{
uchar   i;
uint    j;

  uint wSize = 0;

  uchar p;
  for (p=0; p<23; p++)
  {
    if ((InBuff(ibPtr + 7 - p/8) & (0x01 << p%8)) != 0)
    {
      wSize += sizeof(float);

      float fl = 0;

      i = GetParamLineUni(p);
      if (i == 0xFF)
      {
        PushFloatUni(ST4_NOTSUPPORTED, 0);
      }
      else
      {
        digital diT = mpdiDevicesUni[ibCan-1];
        diT.ibLine = i;

        j = GetParamIndexUni(diT);
        if (j == 0xFFFF)
        {
          PushFloatUni(ST4_NOTPRESENTED, 0);
        }
        else
        {
          fl = mpreParamsBuff[ PrevSoftTim() ][ j ];
          if (ValidFloat(fl))
          {
            PushFloatUni(ST4_OK, FixParamsUni(diT, fl));
          }
          else
          {
            PushFloatUni(ST4_BADDIGITAL, fl);
          }
        }
      }
    }
  }

  return wSize;
}



time    GetTimeParamUni(int  i)
{
  if (boMntParams == true)
  {
    ulong dw = DateToMntIndex(*GetCurrTimeDate());
    dw -= i;
    return MntIndexToDate(dw);
  }
  else
  {
    ulong dw = DateToHouIndex(*GetCurrTimeDate());
    dw -= i;
    return HouIndexToDate(dw);
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
    uint iwTim = bInBuffA*0x100+bInBuffB;
    LoadParamsTim((wTIMES + iwHardTim - iwTim) % wTIMES);

    uint wSize = 0;

    InitPushUni();

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
      PushParamsUni(12, c);

    time ti = GetTimeParamUni(iwTim);
    Output2_Code(wSize, ((boParamsFlag == true) ? bUNI_OK : bUNI_NOTREADY), ti);
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
    uint wSize = 2;

    time ti;
    while (i < j)
    {
      uchar ibCan = ((i-1) % cbDevicesUni)+1;
      uint iwTim = (i-1) / cbDevicesUni;
      i++;

      LoadParamsTim((wTIMES + iwHardTim - iwTim) % wTIMES);

      ti = GetTimeParamUni(iwTim);

      PushInt(ibCan);
      Push(&ti, sizeof(time));
      wSize += 2+6;

      wSize += PushParamsUni(10, ibCan);

      if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result2(bUNI_OUTOVERFLOW); return; }
      ResetWatchdog();
    }

    Output2_Code(wSize, ((boParamsFlag == true) ? bUNI_OK : bUNI_NOTREADY), ti);
  }
}
