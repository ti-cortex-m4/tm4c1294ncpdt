/*------------------------------------------------------------------------------
EXTENDED_4_OUT.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_extended_6.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_pause.h"
#include "../../sensors/automatic2.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../engine.h"
#include "../../energy2.h"
#include "extended_4.h"
#include "extended_4_out.h"



uchar    PushData4(uchar  ibCan, uchar  ibMon, bool  fDouble)
{
  if (GetDigitalDevice(ibCan) == 0)
  {
    uchar bSize = 0;

    bSize += PushChar(ST4_OK);
    bSize += PushInt(0xFFFF);
    bSize += PushInt(0xFFFF);
    bSize += PushFloatOrDouble(mpreCntMonCan[ PrevSoftMon() ][ibCan], fDouble);
    bSize += PushTime(tiZero);

    return bSize;
  }
  else
  {
    uchar bSize = 0;

    value6 vl = mpCntMonCan4[ibCan];
    bSize += PushChar(vl.bStatus);
    bSize += PushInt(0xFFFF);
    bSize += PushInt(0xFFFF);
    bSize += PushFloatOrDouble(vl.dbValue, fDouble);
    bSize += PushTime(vl.tiUpdate);

    return bSize;
  }
}



void    OutExtended40(bool  fDouble)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntMon(InBuff(6));
    LoadExt4Values(InBuff(6));

    InitPushPtr();

    uint wSize = 0;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        wSize += PushData4(c, InBuff(6), fDouble);
      }
    }

    OutptrOutBuff(wSize);
  }
}



void    OutExtended401(bool  fDouble)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntMon(InBuff(6));
    LoadExt4Values(InBuff(6));

    InitPushPtr();

    uint wSize = 0;

    wSize += PushChar(boExt4Flag);
    wSize += PushChar(bExt4Months);
    wSize += PushInt(cwDayCan6);
    wSize += PushInt(cwMonCan6);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        wSize += PushData4(c, InBuff(6), fDouble);
      }
    }

    OutptrOutBuff(wSize);
  }
}



void    OutExtended41(bool  fDouble)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if ((InBuff(6) >= bMONTHS) || (InBuff(7) >= bCANALS))
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntMon(InBuff(6));
    LoadExt4Values(InBuff(6));

    InitPushPtr();            
    uint wSize = PushData4(InBuff(7), InBuff(6), fDouble);
    OutptrOutBuff(wSize);
  }
}



void    OutExtended42(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if ((InBuff(6) >= bMONTHS) || (InBuff(7) >= bCANALS))
    Result(bRES_BADADDRESS);
  else
  {
    uchar ibMon = InBuff(6);
    uchar ibCan = InBuff(7);

    value4 va;
    memset(&va, 0, sizeof(va));
    va.tiSelf = *GetCurrTimeDate();

    if (GetDigitalDevice(ibCan) == 0)
    {
      if (LoadCntMon(ibMon) == 1)
      {
        va.bSelf = ST4_OK;
        va.reSelf = mpreCntMonCan[ PrevSoftMon() ][ibCan];
      }
      else
      {
        va.bSelf = ST4_BADFLASH;
        va.reSelf = 0;
      }

      InitPushPtr();            
      Push(&va, sizeof(value4));
      OutptrOutBuff(sizeof(value4));
    }
    else if (mpboEnblCan[ibCan] == FALSE)
    {
      va.bSelf = ST4_BADENABLING;
      va.reSelf = 0;

      InitPushPtr();            
      Push(&va, sizeof(value4));
      OutptrOutBuff(sizeof(value4));
    }
    else if (GetDigitalPhone(ibCan) != 0)
    {
      va.bSelf = ST4_BADPORT;
      va.reSelf = 0;

      InitPushPtr();            
      Push(&va, sizeof(value4));
      OutptrOutBuff(sizeof(value4));
    }
    else
    {
      SaveDisplay();

      ShowHi(szClear); 
      sprintf(szHi,"Месяц: %-2u",ibMon+1); sprintf(szHi+14,"%2u",ibCan+1);
      Clear(); 

      uchar p = ibPort;
      bool f = ReadCntMonCan(ibMon,ibCan);
      ibPort = p;

      if (f == 1)
      {
        va.bSelf = ST4_OK;
        va.reSelf = reBuffA;
      }
      else
      {
        va.bSelf = ST4_BADDIGITAL;
        va.reSelf = 0;
      }

      InitPushPtr();            
      Push(&va, sizeof(value4));
      OutptrOutBuff(sizeof(value4));

      LoadDisplay();
      NextPause(); // внимание !
    }     
  }
}



void    OutExtended43(void)
{
  InitPushPtr();

  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      wSize += PushChar(mpboExt4EnblCan[c]);
    }
  }

  OutptrOutBuff(wSize);
}
