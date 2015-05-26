/*------------------------------------------------------------------------------
EXTENDED_4_DISPLAY.C

 «начени€ счетчиков на конец мес€цев из буфера с дозапросом (oтчет є52 от 21.11.2009)
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
#include "../../engine.h"
#include "../../energy2.h"
#include "extended_4.h"



void    ShowTimeDateF2(void)
{
  sprintf(szLo,"%02u:%02u %02u.%02u.%02u",
                 tiAlt.bHour,
                 tiAlt.bMinute,
                 tiAlt.bDay,   
                 tiAlt.bMonth,
                 tiAlt.bYear);
}



void    ShowCntMonCanF2(void)
{
  switch (bStatus)
  {
    case ST4_NONE:         ShowLo(szNone);         break;
    case ST4_OK:           (ibZ == 0) ? ShowFloat(reBuffA) : ShowTimeDateF2(); break;
    case ST4_BADDIGITAL:   ShowLo(szBadDigital);   break;
    case ST4_BADFLASH:     ShowLo(szBadFlash);     break;
    case ST4_BADPORT:      ShowLo(szModemLink);      break;
    case ST4_BADENABLING:  ShowLo(szDisabled);  break;
    default:               sprintf(szLo, "*  ошибка: %02X", bStatus); break;
  }  
}



void    ShowExtended4(uchar  ibCan, uchar  ibMon)
{
  value6 va;

  if (GetDigitalDevice(ibCan) == 0)
  {
    LoadCntMon(ibMon);

    va.bSelf = ST4_OK; 
    va.reSelf = mpreCntMonCan[ PrevSoftMon() ][ibCan];
    va.tiUpdate = tiZero;
    bStatus = ST4_OK;
  }
  else
  {
    LoadExt4Values(ibMon);

    va = mpCntMonCan4[ibCan];
    bStatus = va.bSelf;
  }

  reBuffA = va.reSelf;
  tiAlt = va.tiUpdate;

  ShowCntMonCanF2();
}

