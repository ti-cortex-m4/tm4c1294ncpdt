/*------------------------------------------------------------------------------
EXTENDED_6.C

 —охранение значений счетчиков на конец(!) мес€ца чтением первого значени€ счетчиков текущих (также запрос 255 242)
------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "engine.h"
#include        "files.h"
#include        "rtc.h"
#include        "display.h"
#include        "energy.h"
#include        "general.h"
#include        "timedate.h"
#include        "nexttime.h"
#include        "sensors.h"
#include        "queries.h"
#include        "ports.h"
#include        "keyboard.h"



extern  message         code    szExt4None;



void    ResetExtended6(void) 
{ 
  cwDayCan6 = 0;
  cwMonCan6 = 0;
  memset(&mpCntMonCan6, 0, sizeof(mpCntMonCan6));
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
  memset(&mpCntMonCan6[ibHardMon], 0, sizeof(value6)*bCANALS);
}


void    MakeExtended6(uchar  ibCanal)
{
  v6Buff.bSelf = ST4_OK; 
  v6Buff.reSelf = reBuffA;
  v6Buff.tiSelf = *PGetCurrTimeDate();
 
  mpCntMonCan6[ibHardMon][ibCanal] = v6Buff;

  if (mpCntCan6[ibCanal].bSelf == ST4_NONE)
    mpCntCan6[ibCanal] = v6Buff; 
}


#ifndef MODBUS

void    OutExtended6(void)
{
uchar   i;

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
    wBuffD = 2+2;

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
          if (InBuff(6) == (*PGetCurrTimeDate()).bMonth - 1)
            Push(&mpCntCan6[i], sizeof(value6));
          else 
            Push(&mpCntMonCan6[InBuff(6)][i], sizeof(value6));
        }

        wBuffD += sizeof(value6);
      }
    }

    OutptrOutBuff(wBuffD);
  }
}

#endif


void    ShowTimeDate6(void)
{
  sprintf(szLo,"%02bu:%02bu %02bu.%02bu.%02bu",
                 tiAlt.bHour,
                 tiAlt.bMinute,
                 tiAlt.bDay,   
                 tiAlt.bMonth,
                 tiAlt.bYear);
}


void    ShowCntMonCan6(uchar  ibCanal, uchar  ibMonth)
{
  if (GetDigitalDevice(ibCanal) == 0)
  {
    LoadCntMon(ibMonth);

    v6Buff.bSelf = ST4_OK; 
    v6Buff.reSelf = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCanal);
    v6Buff.tiSelf = tiZero;
  }
  else
  {
    if (ibMonth == (*PGetCurrTimeDate()).bMonth - 1)
      v6Buff = mpCntCan6[ibCanal];
    else 
      v6Buff = mpCntMonCan6[ibMonth][ibCanal];
  }

  reBuffA = v6Buff.reSelf;
  tiAlt = v6Buff.tiSelf;

  switch (v6Buff.bSelf)
  {
    case ST4_NONE: ShowLo(szExt4None);                                 break;
    case ST4_OK:   (ibZ == 0) ? ShowReal(&reBuffA) : ShowTimeDate6();  break;    
    default:       sprintf(szLo, "*  ошибка: %02bX   ", v6Buff.bSelf); break;
  }  
}


bit     CheckDirectCnt1(uchar  ibCanal)
{
  return (((boDirectCntD == boTrue) && (GetDigitalDevice(ibCanal) == 4)) || 
                                       (GetDigitalDevice(ibCanal) == 21));
}


bit     CheckDirectCnt2(uchar  ibCanal, uchar  ibMonth)
{
  return (CheckDirectCnt1(ibCanal) && (ibMonth == (*PGetCurrTimeDate()).bMonth - 1));
}


void    ShowDirectCnt(uchar  ibCanal)
{
  v6Buff = mpCntCan6[ibCanal];

  reBuffA = v6Buff.reSelf;
  tiAlt = v6Buff.tiSelf;

  switch (v6Buff.bSelf)
  {
    case ST4_NONE: ShowLo(szExt4None); break;
    case ST4_OK:   ShowReal(&reBuffA); break;    
    default:       sprintf(szLo, "*  ошибка: %02bX   ", v6Buff.bSelf); break;
  }  
}


#ifndef MODBUS

void    LoadDirectCntReal(uchar  ibCanal)
{
  v6Buff = mpCntCan6[ibCanal];
  reBuffA = v6Buff.reSelf;
}


void    LoadDirectCntTime(uchar  ibCanal)
{
  v6Buff = mpCntCan6[ibCanal];
  tiAlt = v6Buff.tiSelf;
}

#endif
*/
