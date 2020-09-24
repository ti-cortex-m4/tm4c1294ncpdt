/*------------------------------------------------------------------------------
AUTOMATIC_B!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../time/timedate.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/serials.h"
#include "../../digitals/max_repeats.h"
#include "../automatic1.h"
#include "../device_b.h"
#include "automatic2.h"



bool    QueryIdB_Full(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryIdB();

    if ((Input() == SER_GOODCHECK) && (ReadIdB() == 1)) break;
    if (fKey == true) return false;

    ShowLo(szFailure20); Delay(1000);
    mpcwFailure2[ibDig]++;
  }

  Clear();
  if (i == MaxRepeats()) return false;

  return true;
}



bool    QueryOpenB_Full(uchar  ibCan, uchar  bPercent)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryOpenB();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (r == MaxRepeats()) return false;
  ShowPercent(bPercent);

  if ((fSerialsManual == false) && (mfSerialFlags[ibCan] == false))
  {
    ulong2 dw2 = QuerySerialB_Full();
    Clear();
    if (dw2.fValid == false) return false;
  }

  return true;
}



time2   QueryTimeB_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryTimeB();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (i == MaxRepeats()) return GetTime2Error();
  ShowPercent(bPercent);

  return GetTime2(ReadTimeB(), true);
}



bool    QueryEnergyB_Full(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEnergyB(bTime);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (i == MaxRepeats()) return false;
  ShowPercent(bPercent);

  ReadEnergyB();
  return true;
}



bool    QueryEnergyB_Full2(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEnergyB(bTime);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return false;

    if (QueryIdB_Full() == 0) return false;
  }

  if (i == MaxRepeats()) return false;
  ShowPercent(bPercent);

  ReadEnergyB();
  return true;
}



ulong2  QuerySerialB_Full(void)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QuerySerialB();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return GetLong2Error();
  }

  if (r == MaxRepeats()) return GetLong2Error();

  ulong dwSerial = ReadSerialB();
  ProcessSerials(ibDig, dwSerial);

  return GetLong2(dwSerial, true);
}
