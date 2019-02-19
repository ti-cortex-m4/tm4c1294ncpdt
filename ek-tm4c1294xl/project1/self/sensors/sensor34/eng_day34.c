/*------------------------------------------------------------------------------
ENG_DAY34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
//#include "../../memory/mem_digitals.h"
//#include "../../serial/ports.h"
//#include "../../serial/ports_devices.h"
//#include "../../devices/devices.h"
//#include "unix_time_gmt34.h"
#include "eng_day34.h"



bool    QueryEngDay34_Full(time  ti, uchar  bPercent)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryEngDates34();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return 0;
  }

  if (r == MaxRepeats()) return 0;
  ShowPercent(bPercent);

  ReadEngDates34();

  return 1;
}
