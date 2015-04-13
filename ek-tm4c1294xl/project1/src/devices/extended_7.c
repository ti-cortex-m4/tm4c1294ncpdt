/*------------------------------------------------------------------------------
EXTENDED_7.C

 Сохранение значений счетчиков на начало суток
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_energy.h"
#include        "../memory/mem_extended_7.h"
#include        "../digitals/digitals.h"
#include        "../devices/devices.h"
#include        "../serial/ports.h"
#include        "../time/rtc.h"
#include        "../flash/files.h"
#include        "../energy.h"
#include        "extended_7.h"



bool    SaveCntDayCan7(uchar  ibDayTo)
{
  OpenOut(FLS_EXT_7_VALUES + ibDayTo*VALUE7_CAN_PAGES);

  if (Save(mpCntDayCan7, sizeof(value6)*bCANALS) == 0)
    return 0;

  return CloseOut();
}


bool    LoadCntDayCan7(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mpCntDayCan7Buff, mpCntDayCan7, sizeof(mpCntDayCan7));
    return 1;
  }
  else
  {
    OpenIn(FLS_EXT_7_VALUES + ibDayFrom*VALUE7_CAN_PAGES);
    return Load(mpCntDayCan7Buff, sizeof(mpCntDayCan7));
  }
}



void    InitExtended7(void)
{
}


void    ResetExtended7(void) 
{ 
  cwDayCan7 = 0;

  memset(&mpCntDayCan7, 0, sizeof(mpCntDayCan7));

  uchar d;
  for (d=0; d<bDAYS; d++)
    SaveCntDayCan7(d);
}



void    NextDayExtended7(void) 
{ 
  cwDayCan7++;

  SaveCntDayCan7(ibHardDay);

  memset(&mpCntDayCan7, 0, sizeof(mpCntDayCan7));

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if (GetDigitalDevice(c) == 0)
    {
      real re  = *PGetCanImpAll(mpimAbsCan,c);
      re *= mpreValueCntHou[c];
      re += mpreCount[c];

      value6 va;
      va.bSelf = ST4_OK; 
      va.reSelf = re;
      va.tiSelf = *GetCurrTimeDate();

      mpCntDayCan7[c] = va;
    }
  }
}



void    MakeExtended7(uchar  ibCan, real  re)
{
  if (mpCntDayCan7[ibCan].bSelf == ST4_NONE)
  {
    value6 va;
    va.bSelf = ST4_OK; 
    va.reSelf = re;
    va.tiSelf = *GetCurrTimeDate();

    mpCntDayCan7[ibCan] = va;
  }
}



void    OutExtended7(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bDAYS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntDayCan7( (bDAYS+ibHardDay-InBuff(6)) % bDAYS );

    InitPushPtr();            
    PushInt(cwDayCan7);
    uint wSize = 2;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
      {
        Push(&mpCntDayCan7Buff[c], sizeof(value6));
        wSize += sizeof(value6);
      }
    }

    OutptrOutBuff(wSize);
  }
}
