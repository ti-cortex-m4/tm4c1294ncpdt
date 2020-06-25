/*------------------------------------------------------------------------------
automatic_get_time_39*c


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



time2   ReadTimeCan39_Internal(void)
{
  caller39 c = InitCaller39();

  time2 tm2 = FragmentOpenTime39(&c);
  if (!tm2.fValid) return GetTime2Error1(Error39(90));

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetTime2Error1(Error39(91));

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
  if (Input39() != SER_GOODCHECK) return GetTime2Error1(Error39(92));

  return GetTime2Error1(Error39(93));
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
  if (Input39() != SER_GOODCHECK) return GetTime2Error1(Error39(94));

  return GetTime2Error1(Error39(95));
}
