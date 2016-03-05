/*------------------------------------------------------------------------------
SERIALS_READ.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../digitals/digitals.h"
#include "../serial/ports.h"
#include "serials_read.h"



ulong2  ReadSerialB(uchar  ibCan)
{
  return QuerySerialB_Full();
}



ulong2  ReadSerial(uchar  ibCan)
{
  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
/*
#ifndef SKIP_B
    case 8:
    case 2:  return ReadTimeCanB();

    case 12: return GetTime2(tiCurr, true);
#endif
*/
    default: return GetLong2Error();
  }
}
