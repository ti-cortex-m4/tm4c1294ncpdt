/*------------------------------------------------------------------------------
SERIALS_READ.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../digitals/digitals.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../sensors/device_b.h"
#include "../sensors/automatic_b.h"
#include "../sensors/device_c.h"
#include "../sensors/automatic_c.h"
#include "../time/delay.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "serials_read.h"



ulong2  ReadSerialCanB(uchar  ibCan)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    DelayOff();
    QueryOpenB();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return GetLong2Error();
  }

  if (r == bMINORREPEATS) return GetLong2Error();
  ShowPercent(25);

  return QuerySerialB_Full();
}



ulong2  ReadSerialCanC(uchar  ibCan)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    DelayOff();
    QueryOpenC();

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return GetLong2Error();
  }

  if (r == bMINORREPEATS) return GetLong2Error();
  ShowPercent(25);

  return QuerySerialC_Full();
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
    case 12: return ReadSerialCanB(ibCan);
#endif

#ifndef SKIP_C
    case 3: return ReadSerialCanC(ibCan);
#endif

    default: return GetLong2Error();
  }
}
