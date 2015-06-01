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
#include "../../time/timedate_display.h"
#include "../../console.h"
#include "../../engine.h"
#include "../../energy2.h"
#include "extended_6.h"
#include "extended_6_show.h"



//                                         0123456789ABCDEF
static char const       szNone[]        = "*    пусто      ";



void    ShowCntMonCan6(uchar  ibCan, uchar  ibMon, bool  fShowValue)
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
      vl = mpCntBoxCan6[ibCan];
    else 
      vl = mpCntMonCan6[ibCan];
  }

  switch (vl.bStatus)
  {
    case ST4_NONE: ShowLo(szNone); break;
    case ST4_OK:   (fShowValue) ? ShowDouble(vl.dbValue) : ShowTimeDate(vl.tiUpdate); break;
    default:       Clear(); sprintf(szLo, "*  ошибка: %02X", vl.bStatus); break;
  }  
}



void    ShowExtended6(uchar  ibCan)
{
  value6 vl = mpCntBoxCan6[ibCan];

  switch (vl.bStatus)
  {
    case ST4_NONE: ShowLo(szNone); break;
    case ST4_OK:   ShowDouble(vl.dbValue); break;
    default:       Clear(); sprintf(szLo, "*  ошибка: %02X", vl.bStatus); break;
  }  
}
