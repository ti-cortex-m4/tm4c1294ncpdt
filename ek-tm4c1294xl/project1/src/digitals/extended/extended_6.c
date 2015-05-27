/*------------------------------------------------------------------------------
EXTENDED_6.C

 «начени€ счетчиков
 на начало текущих суток (дл€ текущего мес€ца) или на конец мес€ца (дл€ остальных мес€цев, кроме текущего)
 из буфера при€мого опроса (oтчет є52 от 21.11.2009)
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../digitals/digitals.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../console.h"
#include "../../engine.h"
#include "../../energy2.h"
#include "extended_6.h"



file const              flExt6Flag = {EXT_6_FLAG, &boExt6Flag, sizeof(boolean)};
file const              flCntDayCan6 = {EXT_6_VALUES, &mpCntDayCan6, sizeof(mpCntDayCan6)};



boolean SaveCntMonCan6(uchar  ibMonTo)
{
  return SaveBuff(EXT_6_MON_VALUES + ibMonTo*VALUE6_CAN_PAGES, mpCntMonCan6, sizeof(mpCntMonCan6));
}


boolean LoadCntMonCan6(uchar  ibMonFrom)
{
  return LoadBuff(EXT_6_MON_VALUES + ibMonFrom*VALUE6_CAN_PAGES, mpCntMonCan6, sizeof(mpCntMonCan6));
}



void    InitExtended6(void)
{
  LoadFileBoolean(&flExt6Flag, FALSE);
  LoadFile(&flCntDayCan6);
}


void    ResetExtended6(void) 
{ 
  cwDayCan6 = 0;
  cwMonCan6 = 0;

  boExt6Flag = FALSE;
  SaveFile(&flExt6Flag);


  memset(&mpCntMonCan6, 0, sizeof(mpCntMonCan6));

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    SaveCntMonCan6(m);
  }


  memset(&mpCntDayCan6, 0, sizeof(mpCntDayCan6));
  SaveFile(&flCntDayCan6);
}


void    NextDayExtended6(void)
{ 
  cwDayCan6++;

  memset(&mpCntDayCan6, 0, sizeof(mpCntDayCan6));
  SaveFile(&flCntDayCan6);
}


void    NextMonExtended6(void) 
{ 
  cwMonCan6++;

  memset(&mpCntMonCan6, 0, sizeof(mpCntDayCan6));
  SaveCntMonCan6(ibHardMon);
}


void    CloseExtended6(void)
{
  SaveFile(&flCntDayCan6);
  SaveCntMonCan6(ibHardMon);
}



void    MakeExtended6(uchar  ibCan, real  re)
{
  value6 va;

  va.bStatus = ST4_OK;
  va.dbValue = re;
  va.tiUpdate = *GetCurrTimeDate();
 
  mpCntMonCan6[ibCan] = va;

  if (mpCntDayCan6[ibCan].bStatus == ST4_NONE)
  {
    mpCntDayCan6[ibCan] = va;
  }
}




bool    SupportedExtended6(uchar  ibCan)
{
  return ((boExt6Flag == TRUE) && ((GetDigitalDevice(ibCan) == 4) || (GetDigitalDevice(ibCan) == 21)));
}


bool    SupportedExtended6_CurrMon(uchar  ibCan, uchar  ibMon)
{
  return (SupportedExtended6(ibCan) && (ibMon == (*GetCurrTimeDate()).bMonth - 1));
}
