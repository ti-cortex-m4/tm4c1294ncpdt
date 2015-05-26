/*------------------------------------------------------------------------------
EXTENDED_4_DISPLAY.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_extended_6.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_pause.h"
#include "../../digitals/digitals_display.h"
#include "../../digitals/digitals_messages.h"
#include "../../devices/devices.h"
#include "../../sensors/device_f.h"
#include "../../sensors/automatic_p.h"
#include "../../sensors/automatic2.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../time/timedate_display.h"
#include "../../engine.h"
#include "../../energy2.h"
#include "extended_4_in.h"
#include "extended_4.h"



//                                         0123456789ABCDEF
static char const       szNone[]        = "*    пусто      ",
                        szBadDigital[]  = "*   ошибка !    ",
                        szBadFlash[]    = "* ошибка памяти ",
                        szModemLink[]   = "*    модем      ",
                        szDisabled[]    = "*  запрещено    ";



void    ShowCntMonCanF(void)
{
  switch (bStatus4)
  {
    case ST4_NONE:         ShowLo(szNone);         break;
    case ST4_OK:           (ibZ == 0) ? ShowDouble(dbValue4) : ShowTimeDate(tiUpdate4); break;
    case ST4_BADDIGITAL:   ShowLo(szBadDigital);   break;
    case ST4_BADFLASH:     ShowLo(szBadFlash);     break;
    case ST4_MODEM_LINK:   ShowLo(szModemLink);    break;
    case ST4_DISABLED:     ShowLo(szDisabled);     break;
    default:               sprintf(szLo, "*  ошибка: %02X", bStatus4); break;
  }  
}



void    ShowExtended4(uchar  ibCan, uchar  ibMon)
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
    LoadExt4Values(ibMon);

    vl = mpCntMonCan4[ibCan];
  }

  bStatus4 = vl.bStatus;
  dbValue4 = vl.dbValue;
  tiUpdate4 = vl.tiUpdate;

  ShowCntMonCanF();
}
