/*------------------------------------------------------------------------------
automatic_get_cntcurr_38*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
// #include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../digitals/digitals.h"
#include "device39.h"
#include "query_engabs_39.h"
#include "io39.h"
#include "automatic_get_cntcurr_39.h"



ulong64_ QueryCntCurr38_Full(void)
{
  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetULong64Error(1);
//  DelayOff();

  Query39_SNRM();
  if (Input39() != SER_GOODCHECK) return GetULong64Error(2);
//  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query39_AARQ(bNS, bNR);
  if (Input39() != SER_GOODCHECK) return GetULong64Error(3);
  if (!ValidateIframe(bNS, bNR)) return GetULong64Error(4);
//  DelayOff();

  bNR++;
  Query39_RR(bNR);
  if (Input39() != SER_GOODCHECK) return GetULong64Error(5);
  if (!ValidateSframe(bNR)) return GetULong64Error(6);
//  DelayOff();


  bNS++;
  bInvokeId++;
  QueryEngAbs39(bNS, bNR, bInvokeId);
  if (Input39() != SER_GOODCHECK) return GetULong64Error(7);
  if (!ValidateIframe(bNS, bNR)) return GetULong64Error(8);
  uint64_t ddw = ReadEngAbs39();
//  DelayOff();

  bNR++;
  Query39_RR(bNR);
  if (Input39() != SER_GOODCHECK) return GetULong64Error(9);
  if (!ValidateSframe(bNR)) return GetULong64Error(10);
//  DelayOff();


  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetULong64Error(11);
//  DelayOff();

  return GetULong64(ddw, true, 0);
}



double2 ReadCntCurr39(void)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    ulong64_ ddw2 = QueryCntCurr38_Full();
    if (fKey == true) break;
    if (ddw2.fValid)
    {
      ShowPercent(50);

      mpdwChannelsA[0] = ddw2.ddwValue % 0x100000000;
      mpdbChannelsC[0] = (double)mpdwChannelsA[0] / 1000;
      mpboChannelsA[0] = true;

      return GetDouble2(mpdbChannelsC[0], true);
    } else {
#ifdef MONITOR_39
      MonitorString("\n Error="); MonitorCharDec(ddw2.bError);
#endif
    }
  }

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
//  DelayOff();

  return GetDouble2Error();
}
