/*------------------------------------------------------------------------------
EXTENDED_7.C

 Сохранение значений счетчиков на начало суток
------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "engine.h"
#include        "energy.h"
#include        "files.h"
#include        "files_far.h"
#include        "rtc.h"
#include        "display.h"
#include        "keyboard.h"
#include        "queries.h"
#include        "ports.h"
#include        "sensors.h"



bit     SaveCntDayCan7(uchar  ibDayTo)
{
  OpenOut(wFLA_CNTDAYCAN7 + ibDayTo*bVALUE6);

  if (Save_Far(mpCntDayCan7Curr, sizeof(value6)*bCANALS) == 0)
    return(0);

  return( CloseOut() );
}


#ifndef MODBUS

bit     LoadCntDayCan7(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mpCntDayCan7Buff, mpCntDayCan7Curr, sizeof(value6)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(wFLA_CNTDAYCAN7 + ibDayFrom*bVALUE6);
    return( Load_Far(mpCntDayCan7Buff, sizeof(value6)*bCANALS) );
  }
}

#endif


void    ResetExtended7(void) 
{ 
uchar   i;

  cwDayCan7 = 0;

  memset(&mpCntDayCan7Curr, 0, sizeof(mpCntDayCan7Curr));

  for (i=0; i<bDAYS; i++)
    SaveCntDayCan7(i);
}



void    NextDayExtended7(void) 
{ 
  cwDayCan7++;

  SaveCntDayCan7(ibHardDay);

  memset(&mpCntDayCan7Curr, 0, sizeof(mpCntDayCan7Curr));

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

      mpCntDayCan7Curr[ibCan] = v6Buff;
    }
  }
}



void    MakeExtended7(uchar  ibCanal)
{
  if (mpCntDayCan7Curr[ibCanal].bSelf == ST4_NONE)
  {
    v6Buff.bSelf = ST4_OK; 
    v6Buff.reSelf = reBuffA;
    v6Buff.tiSelf = *PGetCurrTimeDate();

    mpCntDayCan7Curr[ibCanal] = v6Buff;
  }
}



#ifndef MODBUS

void    OutExtended7(void)
{
uchar   i;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bDAYS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntDayCan7( (bDAYS+ibHardDay-InBuff(6)) % bDAYS );

    InitPushPtr();            
    PushInt(cwDayCan7);
    wBuffD = 2;

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

#endif
*/
