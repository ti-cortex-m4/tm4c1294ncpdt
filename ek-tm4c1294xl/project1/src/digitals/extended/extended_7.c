/*------------------------------------------------------------------------------
EXTENDED_7.C

 Значения счетчиков
 на начало суток
 из буфера прямого опроса (отчет № 69 от 11.11.2010)
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_energy.h"
#include "../../digitals/digitals.h"
#include "../../time/rtc.h"
#include "../../flash/files.h"
#include "../../energy.h"
#include "extended_7.h"



file const              flCntBoxCan7 = {EXT_7_BOX_VALUES, &mpCntBoxCan7, sizeof(mpCntBoxCan7)};



bool    SaveCntDayCan7(uchar  ibDayTo)
{
  return SaveBuff(EXT_7_DAY_VALUES + ibDayTo*VALUE7_CAN_PAGES, mpCntDayCan7, sizeof(mpCntDayCan7));
}


bool    LoadCntDayCan7(uchar  ibDayFrom)
{
  return LoadBuff(EXT_7_DAY_VALUES + ibDayFrom*VALUE7_CAN_PAGES, mpCntDayCan7, sizeof(mpCntDayCan7));
}



void    InitExtended7(void)
{
  LoadFile(&flCntBoxCan7);
}


void    ResetExtended7(void) 
{
  memset(&mpCntDayCan7, 0, sizeof(mpCntDayCan7));

  uchar d;
  for (d=0; d<bDAYS; d++)
  {
    SaveCntDayCan7(d);
  }


  memset(&mpCntBoxCan7, 0, sizeof(mpCntBoxCan7));
  SaveFile(&flCntBoxCan7);


  cwDayCan7 = 0;
}



void    NextDayExtended7(void)
{ 
  cwDayCan7++;

  memset(&mpCntDayCan7, 0, sizeof(mpCntDayCan7));
  memset(&mpCntBoxCan7, 0, sizeof(mpCntBoxCan7));

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if (GetDigitalDevice(c) == 0)
    {
      double db = *PGetCanImpAll(mpimAbsCan,c);
      db *= mpdbValueCntHou[c];
      db += mpdbCount[c];

      value6 vl;
      vl.bStatus = ST4_OK;
      vl.dbValue = db;
      vl.tiUpdate = *GetCurrTimeDate();

      mpCntDayCan7[c] = vl;
      mpCntBoxCan7[c] = vl;
    }
  }

  SaveCntDayCan7(ibHardDay);
  SaveFile(&flCntBoxCan7);
}



void    MakeExtended7(uchar  ibCan, double  db)
{
  value6 vl;
  vl.bStatus = ST4_OK;
  vl.dbValue = db;
  vl.tiUpdate = *GetCurrTimeDate();

  if (mpCntBoxCan7[ibCan].bStatus == ST4_NONE)
  {
    mpCntBoxCan7[ibCan] = vl;
    SaveFile(&flCntBoxCan7);

    mpCntDayCan7[ibCan] = vl;
    SaveCntDayCan7(ibHardDay);
  }
}
