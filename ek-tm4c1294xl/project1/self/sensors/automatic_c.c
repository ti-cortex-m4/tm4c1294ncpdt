/*------------------------------------------------------------------------------
AUTOMATIC_C.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
#include "../digitals/digitals_messages.h"
#include "automatic1.h"
#include "device_c.h"



#ifndef SKIP_C

bool    QueryIdC_Full(void)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryIdC();

    if ((RevInput() == SER_GOODCHECK) && (ReadIdC() == 1)) break;
    if (fKey == true) return false;

    ShowLo(szFailure20); Delay(1000);
    mpcwFailure2[ibDig]++;
  }

  Clear();
  if (i == bMINORREPEATS) return false;

  return(1);
}


bool    QueryEnergyDayC_Full2(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyDayC(bTime);

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return false;

    if (QueryIdC_Full() == 0) return false;
  }

  if (i == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  ReadEnergyC();
  return(1);
}


bool    QueryEnergyMonC_Full2(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyMonC(bTime);

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return false;

    if (QueryIdC_Full() == 0) return false;
  }

  if (i == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  ReadEnergyC();
  return(1);
}


bool    QueryEnergyAbsC_Full2(uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyAbsC();

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return false;

    if (QueryIdC_Full() == 0) return false;
  }

  if (i == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  ReadEnergyC();
  return(1);
}


time2   QueryTimeC_Full(void)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeC();

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (i == bMINORREPEATS) return GetTime2Error();

  return GetTime2(ReadTimeC(), true);
}

#endif
