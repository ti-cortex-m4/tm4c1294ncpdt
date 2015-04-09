/*------------------------------------------------------------------------------
AUTOMATIC3.C
              
 «начени€ счетчиков по тарифам на начало мес€ца
------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "engine.h"
#include        "automatic_b.h"
#include        "automatic_c.h"
#include        "automatic_k.h"
#include        "automatic_p.h"
#include        "ports.h"
#include        "sensors.h"



bit     IsCntMonCanTariff(uchar  ibCanal)
{
  LoadCurrDigital(ibCanal);

  switch (diCurr.bDevice)
  {
    case 2:  return(1);

    case 3:  return(1);

    case 13: return(1);

    case 21: return(1);

    default: return(0);
  }
}


status4 ReadCntMonCanTariff(uchar  ibMonth, uchar  ibCanal, uchar  ibTariff)
{
  Clear();

  LoadCurrDigital(ibCanal);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
    case 2:  return( ReadCntMonCanTariffB(ibMonth,ibTariff) );

    case 3:  return( ReadCntMonCanTariffC(ibMonth,ibTariff) );

    case 13: return( ReadCntMonCanTariffK(ibMonth,ibTariff) );

    case 21: return( ReadCntMonCanTariffP(ibMonth,ibTariff) );

    default: return(ST4_NOTSUPPORTED);
  }
}
*/
