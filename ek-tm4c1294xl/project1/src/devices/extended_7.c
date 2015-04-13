/*------------------------------------------------------------------------------
EXTENDED_7.C

 Сохранение значений счетчиков на начало суток
------------------------------------------------------------------------------*/

#include        "../main.h"
//#include        "../memory/mem_digitals.h"
//#include        "../memory/mem_realtime.h"
//#include        "../memory/mem_profile.h"
#include        "../memory/mem_extended_7.h"
#include        "../digitals/digitals.h"
//#include        "../digitals/digitals_display.h"
#include        "../devices/devices.h"
#include        "../serial/ports.h"
//#include        "../time/rtc.h"
#include        "extended_7.h"



bool    SaveCntDayCan7(uchar  ibDayTo)
{
  OpenOut(wFLA_CNTDAYCAN7 + ibDayTo*bVALUE6);

  if (Save_Far(mpCntDayCan7, sizeof(value6)*bCANALS) == 0)
    return(0);

  return( CloseOut() );
}


bool    LoadCntDayCan7(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mpCntDayCan7Buff, mpCntDayCan7, sizeof(value6)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(wFLA_CNTDAYCAN7 + ibDayFrom*bVALUE6);
    return( Load_Far(mpCntDayCan7Buff, sizeof(value6)*bCANALS) );
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

  uchar ibCan;
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    if (GetDigitalDevice(ibCan) == 0)
    {
      reBuffA  = *PGetCanImpAll(mpimAbsCan,ibCan);
      reBuffA *= *PGetCanReal(mpreValueCntHou,ibCan);
      reBuffA += *PGetCanReal(mpreCount,ibCan);

      v6Buff.bSelf = ST4_OK; 
      v6Buff.reSelf = reBuffA;
      v6Buff.tiSelf = *PGetCurrTimeDate();

      mpCntDayCan7[ibCan] = v6Buff;
    }
  }
}



void    MakeExtended7(uchar  ibCan)
{
  if (mpCntDayCan7[ibCan].bSelf == ST4_NONE)
  {
    v6Buff.bSelf = ST4_OK; 
    v6Buff.reSelf = reBuffA;
    v6Buff.tiSelf = *PGetCurrTimeDate();

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
    uint wBuffD = 2;

    uchar i;
    for (i=0; i<bCANALS; i++)
    {
      if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
      {
        Push(&mpCntDayCan7Buff[i], sizeof(value6));
        wBuffD += sizeof(value6);
      }
    }

    OutptrOutBuff(wBuffD);
  }
}
