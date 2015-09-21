/*------------------------------------------------------------------------------
OUT_CNT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_current.h"
#include "../memory/mem_extended_1.h"
#include "../serial/ports.h"
#include "../digitals/digitals.h"
#include "../digitals/digitals_pause.h"
#include "../sensors/automatic2.h"
#include "../time/rtc.h"
#include "../display/display.h"
#include "../energy.h"
#include "unified/uni_float.h"
#include "out_cnt.h"



void    OutCntCanOld(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff5 < bCANALS)
    {
      InitPushPtr();
      OutptrOutBuff(PushFloat(GetCntCurrImp(bInBuff5)));
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}


void    OutCntCanNew(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (bInBuff5 < bCANALS)
    {
      InitPushPtr();
      OutptrOutBuff(PushFloat(GetCntCurrImp(bInBuff5)));
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



void    OutCntCanOldAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();
    uint wSize = 0;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      wSize += PushFloat(GetCntCurrImp(c));
    }

    OutptrOutBuff(wSize);
  }
  else Result(bRES_NEEDWORK);
}


void    OutCntCanNewAll(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();
    uint wSize = 0;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      float fl;

      if (GetDigitalDevice(c) == 0)
        fl = GetCntCurrImp(c);
      else if ((GetDigitalDevice(c) == 5) || (GetDigitalDevice(c) == 6))
        fl = mpdbEsc_S[c];
      else
      {
        if (boEnblCurrent == true)
          fl = mpdbValueCntHou[c] * mpdwBase[c];
        else
          fl = mpdbEsc_S[c];
      }

      wSize += PushFloat(fl);
    }

    OutptrOutBuff(wSize);
  }
  else Result(bRES_NEEDWORK);
}



void    OutCntCanCurr(bool  fDouble)
{
  SaveDisplay();
  ShowHi(szClear); sprintf(szHi,"Порт %u: CRC%03u",ibPort+1,bInBuff5); Clear();

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      sprintf(szHi+14,"%2u",c+1);

      if (GetDigitalDevice(c) == 0)
        wSize += PushFloatOrDoubleCRC(ST4_OK, GetCntCurrImp(c), fDouble);
      else if (mpboEnblCan[c] == false)
        wSize += PushFloatOrDoubleCRC(ST4_DISABLED, 0, fDouble);
      else if (GetDigitalPhone(c) != 0)
        wSize += PushFloatOrDoubleCRC(ST4_MODEM_LINK, 0, fDouble);
      else
      {
        LoadCurrDigital(c);
        if (mpboChannelsA[diCurr.ibLine] == true)
          wSize += PushFloatOrDoubleCRC(ST4_OK, mpdbChannelsC[diCurr.ibLine], fDouble);
        else
        {
          uchar p = ibPort;
          double2 db2 = ReadCntCurrCan(c);
          ibPort = p;

          if (!db2.fValid)
            wSize += PushFloatOrDoubleCRC(ST4_BADDIGITAL, 0, fDouble);
          else
            wSize += PushFloatOrDoubleCRC(ST4_OK, db2.dbValue, fDouble);
        }
      }

      wSize += PushTime(*GetCurrTimeDate());
    }
  }

  OutptrOutBuff(wSize);

  LoadDisplay();
  NextPause(); // внимание !
}
