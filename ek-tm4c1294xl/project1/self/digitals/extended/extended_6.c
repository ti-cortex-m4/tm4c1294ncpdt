/*------------------------------------------------------------------------------
EXTENDED_6,C

 «начени€ счетчиков
 на начало текущих суток (дл€ текущего мес€ца) или на конец мес€ца (дл€ остальных мес€цев)
 из буфера пр€мого опроса ('ќтчет є52 от 21.11.2009')
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

#include "../../energy2.h"
#include "extended_6.h"



cache const             chExt6Flag = {EXT_6_FLAG, &fExt6Flag, sizeof(bool)};
file const              flCntBoxCan6 = {EXT_6_BOX_VALUES, &mpCntBoxCan6, sizeof(mpCntBoxCan6)};



bool    SaveCntMonCan6(uchar  ibMonTo)
{
  return SaveBuff(EXT_6_MON_VALUES + ibMonTo*VALUE6_CAN_PAGES, mpCntMonCan6, sizeof(mpCntMonCan6));
}


bool    LoadCntMonCan6(uchar  ibMonFrom)
{
  return LoadBuff(EXT_6_MON_VALUES + ibMonFrom*VALUE6_CAN_PAGES, mpCntMonCan6, sizeof(mpCntMonCan6));
}



void    InitExtended6(void)
{
  LoadCacheBool(&chExt6Flag, false);
  LoadFile(&flCntBoxCan6);
}


void    ResetExtended6(bool  fFull)
{ 
  if (fFull)
  {
    fExt6Flag = false;
    SaveCache(&chExt6Flag);
  }


  memset(&mpCntMonCan6, 0, sizeof(mpCntMonCan6));

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    SaveCntMonCan6(m);
  }


  memset(&mpCntBoxCan6, 0, sizeof(mpCntBoxCan6));
  SaveFile(&flCntBoxCan6);


  cwDayCan6 = 0;
  cwMonCan6 = 0;
}



void    NextDayExtended6(void)
{ 
  cwDayCan6++;

  memset(&mpCntBoxCan6, 0, sizeof(mpCntBoxCan6));
  SaveFile(&flCntBoxCan6);
}


void    NextMonExtended6(void) 
{ 
  cwMonCan6++;

  memset(&mpCntMonCan6, 0, sizeof(mpCntMonCan6));
  SaveCntMonCan6(ibHardMon);
}



void    MakeExtended6(uchar  ibCan, double  db)
{
  value6 vl;
  vl.bStatus = ST4_OK;
  vl.dbValue = db;
  vl.tiUpdate = *GetCurrTimeDate();
 
  mpCntMonCan6[ibCan] = vl;
  SaveCntMonCan6(ibHardMon);

  if (mpCntBoxCan6[ibCan].bStatus == ST4_NONE)
  {
    mpCntBoxCan6[ibCan] = vl;
    SaveFile(&flCntBoxCan6);
  }
}




bool    SupportedExtended6(uchar  ibCan)
{
  return ((fExt6Flag == true) && ((GetDigitalDevice(ibCan) == 4) || (GetDigitalDevice(ibCan) == 21)));
}


bool    SupportedExtended6_CurrMon(uchar  ibCan, uchar  ibMon)
{
  return (SupportedExtended6(ibCan) && (ibMon == (*GetCurrTimeDate()).bMonth - 1));
}
