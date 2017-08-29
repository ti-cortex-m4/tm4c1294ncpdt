/*------------------------------------------------------------------------------
AUTOMATIC_A!C


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
#include "../digitals/max_repeats.h"
#include "device_a.h"



#ifndef SKIP_A

bool    QueryOpenA_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryOpenA();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  return(1);
}


time2   QueryTimeA_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryTimeA();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (i == MaxRepeats()) return GetTime2Error();
  ShowPercent(bPercent);

  return GetTime2(ReadTimeA(), true);
}


bool    QueryEnergyA_Full(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEnergyA(bTime);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadEnergyA();
  return(1);
}



bool    QueryIdA_Full(void)
{
uchar  x;

  for (x=0; x<MaxRepeats(); x++)
  {
    DelayOff();
    QueryIdA();

    if ((Input() == SER_GOODCHECK) && (ReadIdA() == 1)) break;
    if (fKey == true) return(0);

    ShowLo(szFailure20); Delay(1000);
    mpcwFailure2[ibDig]++;
  }

  Clear();
  if (x == MaxRepeats()) return(0);

  return(1);
}


bool    QueryEnergyA_Full2(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEnergyA(bTime);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);

    if (QueryIdA_Full() == 0) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadEnergyA();
  return(1);
}

#endif
