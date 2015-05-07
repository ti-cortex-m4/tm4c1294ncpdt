/*------------------------------------------------------------------------------
OUT_PARAMS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_digitals0.h"
#include "../memory/mem_realtime.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../devices/devices.h"
#include "../digitals/digitals.h"
#include "../digitals/digitals_pause.h"
#include "../digitals/digitals_messages.h"
#include "../digitals/params/params.h"
#include "../digitals/params/params2.h"
#include "../digitals/params/params_storage.h"
#include "../engine.h"
#include "../console.h"



void    OutGetParams100(void)
{
  if ((uint)100*bInBuff5 < wPARAMS)
  {
    InitPushCRC();
    Push(&mpdiParam[ (uint)100*bInBuff5 ],(uint)100*sizeof(digital));
    Output((uint)100*sizeof(digital));
  }
  else Result(bRES_BADADDRESS);
}


void    OutGetParams(void)
{
  uint iwParam = bInBuff5*0x100 + bInBuff6;
  if (iwParam < wPARAMS)
  {
    InitPushCRC();
    Push(&mpdiParam[iwParam],sizeof(digital));
    Output(sizeof(digital));
  }
  else Result(bRES_BADADDRESS);
}


void    OutSetParam(void)
{
  if (enGlobal != GLB_WORK)
  {
    uint iwParam = bInBuff5*0x100 + bInBuff6;
    if (iwParam < wPARAMS)
    {
      digital di;

      di.ibPort   = InBuff(7);
      di.ibPhone  = InBuff(8);
      di.bDevice  = InBuff(9);
      di.bAddress = InBuff(10);
      di.ibLine   = InBuff(11);

      if (TrueParam(&di) == true)
      {
        mpdiParam[iwParam] = di;

        if (iwParam == wPARAMS - 1)
          SaveFile(&flParams);

        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDREPROGRAM);
}



void    OutGetParamDiv(void)
{
  uint iwParam = bInBuff5*0x100 + bInBuff6;
  if (iwParam < wPARAMS)
  {
    InitPushCRC();
    PushFloat(mpreParamDiv[iwParam]);
    Output(sizeof(real));
  }
  else Result(bRES_BADADDRESS);
}


void    OutSetParamDiv(void)
{
  if (enGlobal != GLB_WORK)
  {
    uint iwParam = bInBuff5*0x100 + bInBuff6;
    if (iwParam < wPARAMS)
    {
      InitPop(7);

      mpreParamDiv[iwParam] = PopFloat();

      if (iwParam == wPARAMS - 1)
        SaveFile(&flParamsDiv);

      LongResult(bRES_OK);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDREPROGRAM);
}


void    OutGetParamCurr(void)
{
  if ((uint)10*bInBuff5 < wPARAMS)
  {
    SaveDisplay();
    ShowHi(szDirectParam); Clear();

    InitPushCRC();
    Push(&tiCurr, sizeof(time));

    boBeginParam = FALSE;

    bool f = 1;
    uchar i;
    for (i=0; i<10; i++)
    {
      sprintf(szHi+13,"%03u",(uint)10*bInBuff5+i+1);

      if (f == 1)
      {
        if (mpboEnblPar[(uint)10*bInBuff5+i] != TRUE)
          reBuffA = 0;
        else
        {
          uchar p = ibPort;
          f = ReadParam((uint)10*bInBuff5+i);
          ibPort = p;
        }
      }

      if (f == 1)
        PushFloat(reBuffA);
      else
      {
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
      }
    }

    Output(sizeof(time)+(uint)10*sizeof(real));
    NextPause();                                      // внимание !

    LoadDisplay();
  }
  else Result(bRES_BADADDRESS);
}


void    OutGetParamBuff(void)
{
  if (((uint)10*bInBuff5 < wPARAMS) && ((uint)10*bInBuff6 <= wPARAMS))
  {
    InitPushCRC();

    Push(&mptiParBuff[ (uint)10*bInBuff5 ],              (uint)10*bInBuff6*sizeof(time));
    Push(&mpreParBuff[ ibSoftTim ][ (uint)10*bInBuff5 ], (uint)10*bInBuff6*sizeof(real));

    Output((uint)10*bInBuff6*(sizeof(time)+sizeof(real)));
  }
  else Result(bRES_BADADDRESS);
}


void    OutGetParamFull(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (((uint)10*bInBuff5 < wPARAMS) && ((uint)10*bInBuff6 <= wPARAMS))
    {
      if (bInBuff7*0x100+bInBuff8 < wTIMES)
      {
        if (LoadPrmTim((wTIMES + iwHardTim - (bInBuff7*0x100+bInBuff8)) % wTIMES) == 1)
        {
          InitPushCRC();

          PushInt(iwHardTim);
          PushInt(wTIMES);
          PushChar(boMntParams);
          Push(&tiCurr, sizeof(time));

          Push(&mpreParBuff[ PrevSoftTim() ][ (uint)10*bInBuff5 ], (uint)10*bInBuff6*sizeof(real));

          Output(5+sizeof(time)+(uint)10*bInBuff6*sizeof(real));
        }
        else Result(bRES_BADFLASH);
      }
      else Result(bRES_BADADDRESS);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



void    OutGetParamDivs(void)
{
  if (enGlobal != GLB_WORK)
  {
    MakeParamDivAll();
    Result(bRES_OK);
  }
  else Result(bRES_NEEDREPROGRAM);
}



void    OutGetParamsAll(void)
{
  if (bInBuff5 >= bCANALS)
    Result(bRES_BADADDRESS);
  else if ((GetDigitalPhone(bInBuff5) != 0) || (GetDigitalDevice(bInBuff5) == 0))
    Result(bRES_BADDIGITAL);
  else
  {
    SaveDisplay();
    ShowHi(szDirectParam); Clear();

    InitPushCRC();
    Push(&tiCurr, sizeof(time));

    boBeginParam = FALSE;

    bool f = 1;
    uchar i;
    for (i=0; i<bPARAM_BLOCK; i++)
    {
      sprintf(szHi+14,"%2u",i+1);

      if (f == 1)
      {
        digital di;
        di.ibPort   = mpdiDigital[bInBuff5].ibPort;
        di.ibPhone  = mpdiDigital[bInBuff5].ibPhone;
        di.bDevice  = mpdiDigital[bInBuff5].bDevice;
        di.bAddress = mpdiDigital[bInBuff5].bAddress;
        di.ibLine   = mppaParamMap[i];

        mpdiParam[wPARAMS-1] = di;

        mpboEnblPar[wPARAMS-1] = TRUE;
        MakeParamDiv(wPARAMS-1);

        if (boUseParamsDiv == TRUE)
        {
          uint iw = GetParamIndex(di);
          if (iw != 0xFFFF)
            mpreParamDiv[wPARAMS-1] = mpreParamDiv[iw];
        }

        if (mpboEnblPar[wPARAMS-1] != TRUE)
          reBuffA = 0;
        else
        {
          ibDig = bInBuff5;

          uchar p = ibPort;
          f = ReadParam(wPARAMS-1);
          ibPort = p;
        }
      }

      if (f == 1)
        PushFloat(reBuffA);
      else
      {
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
      }
    }

    Output(sizeof(time)+bPARAM_BLOCK*sizeof(real));
    NextPause();                                      // внимание !

    LoadDisplay();
  }
}
