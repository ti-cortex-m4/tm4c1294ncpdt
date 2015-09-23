/*------------------------------------------------------------------------------
EXTENDED_4_SHOW!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_energy.h"
#include "../../realtime/realtime.h"
#include "../../digitals/digitals.h"
#include "../../time/timedate.h"
#include "../../time/timedate_display.h"
#include "../../energy2.h"
#include "extended_4.h"
#include "extended_4_in.h"
#include "extended_4_show.h"



//                                         0123456789ABCDEF
static char const       szNone[]        = "*    пусто      ",
                        szBadDigital[]  = "*   ошибка !    ",
                        szBadFlash[]    = "* ошибка памяти ",
                        szModemLink[]   = "*    модем      ",
                        szDisabled[]    = "*  запрещено    ";



void    ShowCntMonCanF(bool  fShowValue)
{
  switch (bStatus4)
  {
    case ST4_NONE:         ShowLo(szNone);         break;
    case ST4_OK:           (fShowValue) ? ShowDouble(dbValue4) : ShowTimeDate(tiUpdate4); break;
    case ST4_BADDIGITAL:   ShowLo(szBadDigital);   break;
    case ST4_BADFLASH:     ShowLo(szBadFlash);     break;
    case ST4_MODEM_LINK:   ShowLo(szModemLink);    break;
    case ST4_DISABLED:     ShowLo(szDisabled);     break;
    default:               Clear(); sprintf(szLo, "*  ошибка: %02X", bStatus4); break;
  }  
}



void    ShowExtended4(uchar  ibCan, uchar  ibMon, bool  fShowValue)
{
  if (GetDigitalDevice(ibCan) == 0)
  {
    LoadCntMon(ibMon);

    bStatus4 = ST4_OK;
    dbValue4 = mpdbCntMonCan[ PrevSoftMon() ][ibCan];
    tiUpdate4 = tiZero;
  }
  else
  {
    LoadExt4Values(ibMon);

    value6 vl = mpCntMonCan4[ibCan];

    bStatus4 = vl.bStatus;
    dbValue4 = vl.dbValue;
    tiUpdate4 = vl.tiUpdate;
  }

  ShowCntMonCanF(fShowValue);
}
