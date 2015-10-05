/*------------------------------------------------------------------------------
OUT_PARAMS!C


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
#include "../digitals/params/params_div.h"
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
  uint iwPrm = bInBuff5*0x100 + bInBuff6;
  if (iwPrm < wPARAMS)
  {
    InitPushCRC();
    Push(&mpdiParam[iwPrm],sizeof(digital));
    Output(sizeof(digital));
  }
  else Result(bRES_BADADDRESS);
}


void    OutSetParam(void)
{
  if (enGlobal != GLB_WORK)
  {
    uint iwPrm = bInBuff5*0x100 + bInBuff6;
    if (iwPrm < wPARAMS)
    {
      digital di;

      di.ibPort   = InBuff(7);
      di.ibPhone  = InBuff(8);
      di.bDevice  = InBuff(9);
      di.bAddress = InBuff(10);
      di.ibLine   = InBuff(11);

      if (ValidParam(&di) == true)
      {
        mpdiParam[iwPrm] = di;

        if (iwPrm == wPARAMS - 1)
          SaveCache(&flParams);

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
  uint iwPrm = bInBuff5*0x100 + bInBuff6;
  if (iwPrm < wPARAMS)
  {
    InitPushCRC();
    PushFloat(mpreParamsDiv[iwPrm]);
    Output(sizeof(float));
  }
  else Result(bRES_BADADDRESS);
}


void    OutSetParamDiv(void)
{
  if (enGlobal != GLB_WORK)
  {
    uint iwPrm = bInBuff5*0x100 + bInBuff6;
    if (iwPrm < wPARAMS)
    {
      InitPop(7);

      mpreParamsDiv[iwPrm] = PopFloat();

      if (iwPrm == wPARAMS - 1)
        SaveCache(&flParamsDiv);

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

    fBeginParam = false;

    bool f = 1;

    uchar i;
    for (i=0; i<10; i++)
    {
      sprintf(szHi+13,"%03u",(uint)10*bInBuff5+i+1);

      float fl = 0;
      if (f == 1)
      {
        if (mpboEnblParams[(uint)10*bInBuff5+i] != true)
          fl = 0;
        else
        {
          uchar p = ibPort;
          float2 fl2 = ReadParam((uint)10*bInBuff5+i);

          f = fl2.fValid;
          fl = fl2.flValue;

          ibPort = p;
        }
      }

      if (f == 1)
        PushFloat(fl);
      else
      {
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
      }
    }

    Output(sizeof(time)+(uint)10*sizeof(float));
    NextPause(); // внимание !

    LoadDisplay();
  }
  else Result(bRES_BADADDRESS);
}


void    OutGetParamBuff(void)
{
  if (((uint)10*bInBuff5 < wPARAMS) && ((uint)10*bInBuff6 <= wPARAMS))
  {
    InitPushCRC();

    Push(&mptiParamsBuff[ (uint)10*bInBuff5 ],              (uint)10*bInBuff6*sizeof(time));
    Push(&mpreParamsBuff[ ibSoftTim ][ (uint)10*bInBuff5 ], (uint)10*bInBuff6*sizeof(float));

    Output((uint)10*bInBuff6*(sizeof(time)+sizeof(float)));
  }
  else Result(bRES_BADADDRESS);
}


void    OutGetParamFull(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (((uint)10*bInBuff5 < wPARAMS) && ((uint)10*bInBuff6 <= wPARAMS))
    {
      uint iwTim = bInBuff7*0x100+bInBuff8;
      if (iwTim < wTIMES)
      {
        if (LoadParamsTim((wTIMES + iwHardTim - iwTim) % wTIMES) == true)
        {
          InitPushCRC();

          PushIntBig(iwHardTim);
          PushIntBig(wTIMES);
          PushBool(boMntParams);
          PushTime(tiCurr);

          uint wSize = 2 + 2 + 1 + sizeof(time);

          uint i;
          for (i=(uint)10*bInBuff5; i<(uint)10*(bInBuff5+bInBuff6); i++)
          {
            PushFloat(mpreParamsBuff[ PrevSoftTim() ][ i ]);
            wSize += sizeof(float);
          }

          Output(wSize);
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
    MakeParamsDiv();
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

    fBeginParam = false;

    bool f = 1;

    uchar i;
    for (i=0; i<bPARAM_BLOCK; i++)
    {
      sprintf(szHi+14,"%2u",i+1);

      float fl = 0;
      if (f == 1)
      {
        digital di;
        di.ibPort   = mpdiDigital[bInBuff5].ibPort;
        di.ibPhone  = mpdiDigital[bInBuff5].ibPhone;
        di.bDevice  = mpdiDigital[bInBuff5].bDevice;
        di.bAddress = mpdiDigital[bInBuff5].bAddress;
        di.ibLine   = mppaParamsLines[i];

        mpdiParam[wPARAMS-1] = di;

        mpboEnblParams[wPARAMS-1] = true;
        MakeParamDiv(wPARAMS-1);

        if (boUseParamsDiv == true)
        {
          uint p = GetParamIndex(di);
          if (p != 0xFFFF)
            mpreParamsDiv[wPARAMS-1] = mpreParamsDiv[p];
        }

        if (mpboEnblParams[wPARAMS-1] != true)
          fl = 0;
        else
        {
          ibDig = bInBuff5;

          uchar p = ibPort;
          float2 fl2 = ReadParam(wPARAMS-1);

          f = fl2.fValid;
          fl = fl2.flValue;

          ibPort = p;
        }
      }

      if (f == 1)
        PushFloat(fl);
      else
      {
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
      }
    }

    Output(sizeof(time)+bPARAM_BLOCK*sizeof(float));
    NextPause(); // внимание !

    LoadDisplay();
  }
}
