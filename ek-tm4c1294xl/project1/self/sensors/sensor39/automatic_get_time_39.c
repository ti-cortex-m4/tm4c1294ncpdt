/*------------------------------------------------------------------------------
automatic_get_time_38*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
//#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "device39.h"
#include "time39.h"
#include "io39.h"
#include "automatic_get_time_39.h"



time2   QueryTime38_Full(void)
{
  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetTime2Error();
//  DelayOff();

  Query39_SNRM();
  if (Input39() != SER_GOODCHECK) return GetTime2Error();
//  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query39_AARQ(bNS, bNR);
  if (Input39() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateIframe(bNS, bNR)) return GetTime2Error();
//  DelayOff();

  bNR++;
  Query39_RR(bNR);
  if (Input39() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateSframe(bNR)) return GetTime2Error();
//  DelayOff();


  bNS++;
  bInvokeId++;
  QueryTime39(bNS, bNR, bInvokeId);
  if (Input39() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateIframe(bNS, bNR)) return GetTime2Error();
  time ti = ReadTime39();
//  DelayOff();

  bNR++;
  Query39_RR(bNR);
  if (Input39() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateSframe(bNR)) return GetTime2Error();
//  DelayOff();


  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetTime2Error();
//  DelayOff();

  return GetTime2(ti, true);
}



time2   ReadTimeCan39(void)
{
  Clear();


  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    time2 ti2 = QueryTime38_Full();
    if (fKey == true) break;
    if (ti2.fValid)
    {
      ShowPercent(50);

      tiChannelC = ti2.tiValue;
      mpboChannelsA[0] = true;

      return GetTime2(ti2.tiValue, true);
    }
  }

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetTime2Error();
//  DelayOff();

  return GetTime2Error();
}



time2   ReadTimeCan39_Short(void)
{
  Clear();

  time2 ti2 = QueryTime38_Full();
  if (ti2.fValid)
  {
    tiChannelC = ti2.tiValue;
    mpboChannelsA[0] = true;

    return GetTime2(ti2.tiValue, true);
  }

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetTime2Error();
//  DelayOff();

  return GetTime2Error();
}
