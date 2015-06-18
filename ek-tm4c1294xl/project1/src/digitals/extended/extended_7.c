/*------------------------------------------------------------------------------
EXTENDED_7,C

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
#include "../../nvram/cache.h"
#include "../../energy.h"
#include "extended_7.h"



bool    SaveCntDay7(uchar  ibDayTo)
{
  return SaveArrayX(EXT_7_DAY_VALUES, sizeof(mpCntDayCan7), ibDayTo, &mpCntDayCan7);
}


bool    LoadCntDay7(uchar  ibDayFrom)
{
  return LoadArrayX(EXT_7_DAY_VALUES, sizeof(mpCntDayCan7), ibDayFrom, &mpCntDayCan7);
}



bool    SaveCntDayCan7(uchar  ibDayTo, uchar  ibCan, value6  *pvl)
{
  return SaveArrayXY(EXT_7_DAY_VALUES, sizeof(mpCntDayCan7), ibDayTo, sizeof(value6), ibCan, pvl);
}


bool    LoadCntDayCan7(uchar  ibDayFrom, uchar  ibCan, value6  *pvl)
{
  return LoadArrayXY(EXT_7_DAY_VALUES, sizeof(mpCntDayCan7), ibDayFrom, sizeof(value6), ibCan, pvl);
}



void    ResetExtended7(void) 
{
  memset(&mpCntDayCan7, 0, sizeof(mpCntDayCan7));

  uchar d;
  for (d=0; d<bDAYS; d++)
  {
    SaveCntDay7(d);
  }


  cwDayCan7 = 0;
}



void    NextDayExtended7(void)
{ 
  cwDayCan7++;

  memset(&mpCntDayCan7, 0, sizeof(mpCntDayCan7));

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
    }
  }

  SaveCntDay7(ibHardDay);
}



void    MakeExtended7(uchar  ibCan, double  db)
{
  value6 vl1;
  LoadCntDayCan7(ibHardDay, ibCan, &vl1);

  if (vl1.bStatus == ST4_NONE)
  {
    value6 vl2;
    vl2.bStatus = ST4_OK;
    vl2.dbValue = db;
    vl2.tiUpdate = *GetCurrTimeDate();

    SaveCntDayCan7(ibHardDay, ibCan, &vl2);
  }
}
