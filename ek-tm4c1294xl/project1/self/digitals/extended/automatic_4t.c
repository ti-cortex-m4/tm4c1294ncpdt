/*------------------------------------------------------------------------------
AUTOMATIC_4T,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/digitals.h"
#include "../../display/display.h"
#include "../../serial/ports.h"
#include "../../sensors/sensor3/automatic_c.h"
#include "../../sensors/automatic_k.h"
#include "../../sensors/sensor21/automatic_p.h"
#include "../../sensors/automatic_w.h"
#include "extended_4t_b.h"
#include "extended_4t_c.h"
#include "automatic_4t.h"



bool    SupportedExtended4T(uchar  ibCan)
{
  LoadCurrDigital(ibCan);

  switch (diCurr.bDevice)
  {
    case 2:  return true;

    case 3:  return true;

    case 13: return true;

    case 21: return true;

    case 29:
    case 30: return true;

    default: return false;
  }
}


status  ReadCntMonCanTariff(uchar  ibCan, uchar  ibMon, uchar  ibTrf)
{
  Clear();

  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
    case 2:  return ReadCntMonCanTariffB(ibCan, ibMon, ibTrf);

    case 3:  return ReadCntMonCanTariffC(ibCan, ibMon, ibTrf);

    case 13: return ReadCntMonCanTariffK(ibMon, ibTrf);

    case 21: return ReadCntMonCanTariffP(ibMon, ibTrf);

    case 29:
    case 30: return ReadCntMonCanTariffW(ibMon, ibTrf);

    default: return ST_NOTSUPPORTED;
  }
}
