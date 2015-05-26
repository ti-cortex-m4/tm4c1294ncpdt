/*------------------------------------------------------------------------------
EXTENDED_4_OUTPUT.C

 «начени€ счетчиков на конец мес€цев из буфера с дозапросом (oтчет є52 от 21.11.2009)
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_extended_6.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_pause.h"
#include "../../digitals/digitals_display.h"
#include "../../digitals/digitals_messages.h"
#include "../../devices/devices.h"
#include "../../sensors/device_f.h"
#include "../../sensors/automatic_p.h"
#include "../../sensors/automatic2.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../engine.h"
#include "../../energy2.h"
#include "extended_4.h"



void    PushData4(uchar  ibCan, uchar  ibMon, bool  fDouble)
{
  if (GetDigitalDevice(ibCan) == 0)
  {
    PushChar(ST4_OK);
    PushInt(0xFF);
    PushInt(0xFF);
    PushFloat(mpreCntMonCan[ PrevSoftMon() ][ibCan]);
    PushTime(tiZero);
  }
  else
  {
  	value6 vl = mpCntMonCan4[ibCan];
    PushChar(vl.bSelf);
    PushInt(0xFF);
    PushInt(0xFF);
    PushFloat(vl.reSelf);
    PushTime(vl.tiUpdate);
  }
}



void    OutExtended40(void)
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
        PushData4(c, InBuff(6), false);
        wSize += (1+2+2+4+6);
      }
    }

    OutptrOutBuff(wSize);
  }
}



void    OutExtended401(void)
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
    PushChar(boExt4Flag);
    PushChar(bExt4Months);
    PushInt(cwDayCan6);
    PushInt(cwMonCan6);
    uint wSize = 1+1+2+2;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        PushData4(c, InBuff(6), false);
        wSize += (1+2+2+4+6);
      }
    }

    OutptrOutBuff(wSize);
  }
}



void    OutExtended41(void)
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
    PushData4(InBuff(7), InBuff(6), false);
    OutptrOutBuff(1+2+2+4+6);
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
      sprintf(szHi,"ћес€ц: %-2u",ibMon+1); sprintf(szHi+14,"%2u",ibCan+1);
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
      Push(&mpboExt4EnblCan[c], sizeof(uchar));
      wSize += sizeof(uchar);
    }
  }

  OutptrOutBuff(wSize);
}
