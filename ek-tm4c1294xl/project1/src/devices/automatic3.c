/*------------------------------------------------------------------------------
AUTOMATIC3,C

 «начени€ счетчиков на начало мес€цев по тарифам
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../digitals/digitals.h"
#include "../display/display.h"
#include "../serial/ports.h"
#include "extended_4t_b.h"
#include "../sensors/automatic_c.h"
#include "automatic3.h"



bool    SupportedCntMonCanTariff(uchar  ibCan)
{
  LoadCurrDigital(ibCan);

  switch (diCurr.bDevice)
  {
    case 2:  return true;

    case 3:  return true;

    case 13: return true;

    case 21: return true;

    default: return false;
  }
}


status  ReadCntMonCanTariff(uchar  ibMon, uchar  ibCan, uchar  ibTrf)
{
  Clear();

  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
    case 2:  return ReadCntMonCanTariffB(ibMon, ibTrf);

    case 3:  return ReadCntMonCanTariffC(ibMon, ibTrf);

//    case 13: return ReadCntMonCanTariffK(ibMon, ibTrf);

//    case 21: return ReadCntMonCanTariffP(ibMon, ibTrf);

    default: return ST4_NOTSUPPORTED;
  }
}
