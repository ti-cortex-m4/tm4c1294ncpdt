/*------------------------------------------------------------------------------
EXTENDED_7.C

 Сохранение значений счетчиков на начало суток
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_extended_7.h"
#include        "../digitals/digitals.h"
#include        "../devices/devices.h"
#include        "../serial/ports.h"
#include        "../time/rtc.h"
#include        "../flash/files.h"
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



void    ResetExtended7(void) 
{ 
  cwDayCan7 = 0;

  memset(&mpCntDayCan7, 0, sizeof(mpCntDayCan7));

  uchar i;
  for (i=0; i<bDAYS; i++)
    SaveCntDayCan7(i);
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
      real reBuffA  = *PGetCanImpAll(mpimAbsCan,c);
      reBuffA *= *PGetCanReal(mpreValueCntHou,c);
      reBuffA += *PGetCanReal(mpreCount,c);

      value6 v6Buff;
      v6Buff.bSelf = ST4_OK; 
      v6Buff.reSelf = reBuffA;
      v6Buff.tiSelf = *GetCurrTimeDate();

      mpCntDayCan7[c] = v6Buff;
    }
  }
}



void    MakeExtended7(uchar  ibCan, real  reBuffA)
{
  if (mpCntDayCan7[ibCan].bSelf == ST4_NONE)
  {
    value6 v6Buff;
    v6Buff.bSelf = ST4_OK; 
    v6Buff.reSelf = reBuffA;
    v6Buff.tiSelf = *GetCurrTimeDate();

    mpCntDayCan7[ibCan] = v6Buff;
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
