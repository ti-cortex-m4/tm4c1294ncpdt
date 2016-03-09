/*------------------------------------------------------------------------------
SERIALS_READ.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../digitals/digitals.h"
#include "../serial/ports.h"
#include "../sensors/automatic_b.h"
#include "serials_read.h"



ulong2  ReadSerialCanB(void)
{
  return QuerySerialB_Full();
}



ulong2  ReadSerialCan(uchar  ibCan)
{
  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {

#ifndef SKIP_B
    case 8:
    case 2:
    case 12: return ReadSerialCanB();
#endif

    default: return GetLong2Error();
  }
}
