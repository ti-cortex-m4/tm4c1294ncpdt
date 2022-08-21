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
#include "../../sensors/sensor24/automatic_s2.h"
#include "../../sensors/sensor26/automatic_u2.h"
#include "../../sensors/automatic_w.h"
#include "../../sensors/sensor34/extended_4t_34.h"
#include "../../sensors/sensor35/automatic35x2.h"
#include "../../sensors/sensor36/extended_4t_36.h"
#include "../../sensors/sensor38/extended_4t_38.h"
#include "../../sensors/sensor40/extended_4t_40.h"
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

    case 24: return true;

    case 26:
    case 28: return true;

    case 29:
    case 30: return true;

    case 34: return true;

    case 35: return true;

    case 36:
    case 37: return true;

    case 38:
    case 39: return true;

    case 40: return true;

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

    case 24: return ReadCntMonCanTariffS(ibMon, ibTrf);

    case 26: return ReadCntMonCanTariffU(ibMon, ibTrf, 2);
    case 28: return ReadCntMonCanTariffU(ibMon, ibTrf, 4);

    case 29:
    case 30: return ReadCntMonCanTariffW(ibMon, ibTrf);

    case 34: return ReadCntMonCanTariff34(ibMon, ibTrf);

    case 35: return ReadCntMonCanTariff35(ibMon, ibTrf);

    case 36: return ReadCntMonCanTariff36(ibMon, ibTrf, 2);
    case 37: return ReadCntMonCanTariff36(ibMon, ibTrf, 4);

    case 38: 
    case 39: return ReadCntMonCanTariff38(ibMon, ibTrf);

    case 40: return ReadCntMonCanTariff40(ibMon, ibTrf);

    default: return ST_NOTSUPPORTED;
  }
}
