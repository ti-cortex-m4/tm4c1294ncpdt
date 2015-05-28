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



static uchar PushData4(uchar  ibCan, uchar  ibMon, bool  fDouble)
{
  if (GetDigitalDevice(ibCan) == 0)
  {
    uchar bSize = 0;

    bSize += PushChar(ST4_OK);
    bSize += PushInt(0xFFFF);
    bSize += PushInt(0xFFFF);
    bSize += PushFloatOrDouble(mpdbCntMonCan[ PrevSoftMon() ][ibCan], fDouble);
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



void    OutExtended44(bool  fDouble)
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



static void OutData4(uchar  bStatus, double  dbValue, bool  fDouble)
{
  InitPushPtr();
  uchar bSize = 0;

  bSize += PushChar(bStatus);
  bSize += PushInt(0);
  bSize += PushInt(0);
  bSize += PushFloatOrDouble(dbValue, fDouble);
  bSize += PushTime(*GetCurrTimeDate());

  OutptrOutBuff(bSize);
}


void    OutExtended42(bool  fDouble)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if ((InBuff(6) >= bMONTHS) || (InBuff(7) >= bCANALS))
    Result(bRES_BADADDRESS);
  else
  {
    uchar ibMon = InBuff(6);
    uchar ibCan = InBuff(7);

    if (GetDigitalDevice(ibCan) == 0)
    {
      if (LoadCntMon(ibMon) == true)
        OutData4(ST4_OK, mpdbCntMonCan[ PrevSoftMon() ][ibCan], fDouble);
      else
        OutData4(ST4_BADFLASH, 0, fDouble);
    }
    else if (mpboEnblCan[ibCan] == false)
    {
      OutData4(ST4_DISABLED, 0, fDouble);
    }
    else if (GetDigitalPhone(ibCan) != 0)
    {
      OutData4(ST4_MODEM_LINK, 0, fDouble);
    }
    else
    {
      SaveDisplay();

      ShowHi(szClear); 
      sprintf(szHi,"Месяц: %-2u",ibMon+1); sprintf(szHi+14,"%2u",ibCan+1);
      Clear(); 

      uchar p = ibPort;
      double2 db2 = ReadCntMonCan(ibMon,ibCan);
      ibPort = p;

      if (db2.fValid)
        OutData4(ST4_OK, db2.dbValue, fDouble);
      else
        OutData4(ST4_BADDIGITAL, 0, fDouble);

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
      wSize += PushBool(mpboExt4EnblCan[c]);
    }
  }

  OutptrOutBuff(wSize);
}
