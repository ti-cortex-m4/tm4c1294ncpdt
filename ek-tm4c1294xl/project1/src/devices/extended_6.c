/*------------------------------------------------------------------------------
EXTENDED_6.C

 —охранение значений счетчиков на конец(!) мес€ца чтением первого значени€ счетчиков текущих (также запрос 255 242)
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_realtime.h"
//#include        "../memory/mem_profile.h"
#include        "../memory/mem_extended_6.h"
#include        "../digitals/digitals.h"
//#include        "../digitals/digitals_display.h"
//#include        "../devices/devices.h"
#include        "../serial/ports.h"
#include        "../time/rtc.h"
#include        "../console.h"
#include        "../energy2.h"
#include        "extended_6.h"



void    ResetExtended6(void) 
{ 
  cwDayCan6 = 0;
  cwMonCan6 = 0;
  memset(&mpCntMonCan6_, 0, sizeof(mpCntMonCan6_));
  memset(&mpCntCan6, 0, sizeof(mpCntCan6));
}


void    NextDayExtended6(void)
{ 
  cwDayCan6++;
  memset(&mpCntCan6, 0, sizeof(mpCntCan6));
}


void    NextMonExtended6(void) 
{ 
  cwMonCan6++;
  memset(&mpCntMonCan6_[ibHardMon], 0, sizeof(value6)*bCANALS);
}


void    MakeExtended6(uchar  ibCan)
{
  v6Buff.bSelf = ST4_OK; 
  v6Buff.reSelf = reBuffA;
  v6Buff.tiSelf = *GetCurrTimeDate();
 
  mpCntMonCan6_[ibHardMon][ibCan] = v6Buff;

  if (mpCntCan6[ibCan].bSelf == ST4_NONE)
    mpCntCan6[ibCan] = v6Buff;
}



void    OutExtended6(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntMon(InBuff(6));

    InitPushPtr();            
    PushInt(cwDayCan6);
    PushInt(cwMonCan6);
    uint wBuffD = 2+2;

    uchar i;
    for (i=0; i<bCANALS; i++)
    {
      if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
      {
        if (GetDigitalDevice(i) == 0)
        {
          v6Buff.bSelf = ST4_OK; 
          v6Buff.reSelf = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], i);
          v6Buff.tiSelf = tiZero;
          Push(&v6Buff, sizeof(value6));
        }
        else
        {
          if (InBuff(6) == (*GetCurrTimeDate()).bMonth - 1)
            Push(&mpCntCan6[i], sizeof(value6));
          else 
            Push(&mpCntMonCan6_[InBuff(6)][i], sizeof(value6));
        }

        wBuffD += sizeof(value6);
      }
    }

    OutptrOutBuff(wBuffD);
  }
}



void    ShowTimeDate6(void)
{
  sprintf(szLo,"%02u:%02u %02u.%02u.%02u",
                 tiAlt.bHour,
                 tiAlt.bMinute,
                 tiAlt.bDay,   
                 tiAlt.bMonth,
                 tiAlt.bYear);
}


void    ShowCntMonCan6(uchar  ibCan, uchar  ibMon)
{
  if (GetDigitalDevice(ibCan) == 0)
  {
    LoadCntMon(ibMon);

    v6Buff.bSelf = ST4_OK; 
    v6Buff.reSelf = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCan);
    v6Buff.tiSelf = tiZero;
  }
  else
  {
    if (ibMon == (*GetCurrTimeDate()).bMonth - 1)
      v6Buff = mpCntCan6[ibCan];
    else 
      v6Buff = mpCntMonCan6_[ibMon][ibCan];
  }

  reBuffA = v6Buff.reSelf;
  tiAlt = v6Buff.tiSelf;

  switch (v6Buff.bSelf)
  {
    case ST4_NONE: ShowLo(szExt4None); break;
    case ST4_OK:   (ibZ == 0) ? ShowReal(&reBuffA) : ShowTimeDate6(); break;
    default:       Clear(); sprintf(szLo, "*  ошибка: %02X", v6Buff.bSelf); break;
  }  
}


bool    CheckDirectCnt1(uchar  ibCan)
{
  return (((boDirectCntD == TRUE) && (GetDigitalDevice(ibCan) == 4)) ||
                                     (GetDigitalDevice(ibCan) == 21));
}


bool    CheckDirectCnt2(uchar  ibCan, uchar  ibMon)
{
  return (CheckDirectCnt1(ibCan) && (ibMon == (*GetCurrTimeDate()).bMonth - 1));
}


void    ShowDirectCnt(uchar  ibCan)
{
  v6Buff = mpCntCan6[ibCan];

  reBuffA = v6Buff.reSelf;
  tiAlt = v6Buff.tiSelf;

  switch (v6Buff.bSelf)
  {
    case ST4_NONE: ShowLo(szExt4None); break;
    case ST4_OK:   ShowReal(&reBuffA); break;    
    default:       Clear(); sprintf(szLo, "*  ошибка: %02X", v6Buff.bSelf); break;
  }  
}


void    LoadDirectCntReal(uchar  ibCan)
{
  v6Buff = mpCntCan6[ibCan];
  reBuffA = v6Buff.reSelf;
}


void    LoadDirectCntTime(uchar  ibCan)
{
  v6Buff = mpCntCan6[ibCan];
  tiAlt = v6Buff.tiSelf;
}
