/*------------------------------------------------------------------------------
AUTOMATIC_5,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/digitals.h"
#include "../../serial/ports.h"
#include "../../sensors/sensor34/extended_5_34.h"
#include "extended_5_a.h"
#include "extended_5_b.h"
#include "extended_5_c.h"
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
    case 2:  return ReadCntDayTariffB(ibCan, bTrf);
#endif

#ifndef SKIP_C
    case 3:  return ReadCntDayTariffC(ibCan, bTrf);
#endif

#ifndef SKIP_H
    case 10: return ReadCntDayTariffH(bTrf);
#endif

#ifndef SKIP_34
    case 34: return ReadCntDayTariff34(ibCan, bTrf-1); // не номер тарифа, а индекс тарифа
#endif

    default: return false;
  }
}
