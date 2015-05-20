/*------------------------------------------------------------------------------
AUTOMATIC_5.C

 Значения счетчиков на начало текущих суток по тарифам (отчет № 18a от 01.02.2008)
------------------------------------------------------------------------------*/

#include "../main.h"
//#include "../memory/mem_digitals.h"
//#include "../memory/mem_realtime.h"
//#include "../memory/mem_profile.h"
//#include "../digitals/digitals.h"
//#include "../digitals/digitals_display.h"
//#include "../devices/devices.h"
//#include "../serial/ports.h"
//#include "../time/rtc.h"
//#include "../console.h"
//#include "extended_5_a.h"
//#include "extended_5_b.h"
//#include "extended_5_c.h"
#include "extended_5.h"



bool    ReadCntDayTariff(uchar  ibCan, uchar  bTrf)
{
  Clear();

  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  return ReadCntDayTariffA(bTrf);
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return ReadCntDayTariffB(bTrf);
#endif

#ifndef SKIP_C
    case 3:  return ReadCntDayTariffC(bTrf);
#endif

#ifndef SKIP_H
    case 10: return ReadCntDayTariffH(bTrf);
#endif

    default: return 0;
  }
}
