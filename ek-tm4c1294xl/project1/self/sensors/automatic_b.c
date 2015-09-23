/*------------------------------------------------------------------------------
AUTOMATIC_B!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../time/delay.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../time/timedate.h"
#include "../devices/devices.h"
#include "../digitals/digitals_messages.h"

#include "automatic1.h"
#include "device_b.h"



bool    QueryIdB_Full(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryIdB();

    if ((Input() == SER_GOODCHECK) && (ReadIdB() == 1)) break;
    if (fKey == true) return false;

    ShowLo(szFailure20); Delay(1000);
    mpcwFailure2[ibDig]++;
  }

  Clear();
  if (i == bMINORREPEATS) return false;

  return true;
}



bool    QueryOpenB_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryOpenB();

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == true) return false;
  }

  if (i == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  return true;
}



time2   QueryTimeB_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeB();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (i == bMINORREPEATS) return GetTime2Error();
  ShowPercent(bPercent);

  return GetTime2(ReadTimeB(), true);
}



bool    QueryEnergyB_Full(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyB(bTime);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (i == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  ReadEnergyB();
  return true;
}



bool    QueryEnergyB_Full2(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyB(bTime);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return false;

    if (QueryIdB_Full() == 0) return false;
  }

  if (i == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  ReadEnergyB();
  return true;
}
