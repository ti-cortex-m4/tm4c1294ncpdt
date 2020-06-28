/*------------------------------------------------------------------------------
automatic_get_time_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "device39.h"
#include "time39.h"
#include "io39.h"
#include "caller39.h"
#include "error39.h"
#include "fragment_open_time_39.h"
#include "automatic_get_time_39.h"



static time2 Fault(uchar  bError)
{
  return GetTime2Error1(Error39(bError));
}



time2   ReadTimeCan39_Internal(void)
{
  caller39 c = InitCaller39();

  time2 tm2 = FragmentOpenTime39(&c);
  if (!tm2.fValid) return Fault(70+0);

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return Fault(70+1);

  return GetTime0(tm2.tiValue);
}



time2   ReadTimeCan39(void)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    time2 tm2 = ReadTimeCan39_Internal();
    if (fKey == true) break;
    if (tm2.fValid)
    {
      tiChannelC = tm2.tiValue;
      mpboChannelsA[0] = true;

      return GetTime0(tm2.tiValue);
    }
  }

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return Fault(70+2);

  return Fault(70+3);
}



time2   ReadTimeCan39_Short(void)
{
  Clear();

  time2 tm2 = ReadTimeCan39_Internal();
  if (tm2.fValid)
  {
    tiChannelC = tm2.tiValue;
    mpboChannelsA[0] = true;

    return GetTime0(tm2.tiValue);
  }

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return Fault(70+4);

  return Fault(70+5);
}
