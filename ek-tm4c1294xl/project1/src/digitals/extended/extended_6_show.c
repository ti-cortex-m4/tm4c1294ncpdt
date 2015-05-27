/*------------------------------------------------------------------------------
EXTENDED_6_SHOW.C

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



//                                         0123456789ABCDEF
static char const       szNone[]        = "*    пусто      ";



void    ShowTimeDate6(time  ti)
{
  sprintf(szLo,"%02u:%02u %02u.%02u.%02u",
               ti.bHour,
               ti.bMinute,
               ti.bDay,
               ti.bMonth,
               ti.bYear);
}


void    ShowCntMonCan6(uchar  ibCan, uchar  ibMon)
{
value6 vl;

  if (GetDigitalDevice(ibCan) == 0)
  {
    LoadCntMon(ibMon);

    vl.bStatus = ST4_OK;
    vl.dbValue = mpdbCntMonCan[ PrevSoftMon() ][ibCan];
    vl.tiUpdate = tiZero;
  }
  else
  {
    LoadCntMonCan6(ibMon);

    if (ibMon == (*GetCurrTimeDate()).bMonth - 1)
      vl = mpCntDayCan6[ibCan];
    else 
      vl = mpCntMonCan6[ibCan];
  }

  reBuffA = vl.dbValue;
  tiAlt = vl.tiUpdate;

  switch (vl.bStatus)
  {
    case ST4_NONE: ShowLo(szNone); break;
    case ST4_OK:   (ibZ == 0) ? ShowFloat(reBuffA) : ShowTimeDate6(tiAlt); break;
    default:       Clear(); sprintf(szLo, "*  ошибка: %02X", vl.bStatus); break;
  }  
}



void    ShowDirectCnt(uchar  ibCan)
{
  value6 vl = mpCntDayCan6[ibCan];

  reBuffA = vl.dbValue;
  tiAlt = vl.tiUpdate;

  Clear();

  switch (vl.bStatus)
  {
    case ST4_NONE: ShowLo(szNone); break;
    case ST4_OK:   ShowFloat(reBuffA); break;
    default:       Clear(); sprintf(szLo, "*  ошибка: %02X", vl.bStatus); break;
  }  
}
