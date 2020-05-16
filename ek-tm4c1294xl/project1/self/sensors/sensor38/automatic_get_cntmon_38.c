/*------------------------------------------------------------------------------
automatic_get_cntmon_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "device36.h"
#include "query_engmon_38.h"
#include "io36.h"
#include "monitor36.h"
#include "automatic_get_cntmon_38.h"



ulong64_ QueryCntMon38_Full(uchar  ibMon)
{
  Query38_DISC();
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  DelayOff();

  Query38_SNRM();
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query38_Open2(bNS, bNR);
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  if (!ValidateIframe(bNS, bNR)) return GetLong64Error();
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  if (!ValidateSframe(bNR)) return GetLong64Error();
  DelayOff();


  bNS++;
  bInvokeId++;
  QueryTime38(bNS, bNR, bInvokeId);
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  if (!ValidateIframe(bNS, bNR)) return GetLong64Error();
  time ti = ReadTime36();
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  if (!ValidateSframe(bNR)) return GetLong64Error();
  DelayOff();


  if (ti.bMonth != ibMon+1)
  {
    uchar bMonth = 4;
    uchar bYear = 20;

    bNS++;
    QueryEngMon38(bNS, bNR, bInvokeId++, bMonth, bYear);
    if (Input38() != SER_GOODCHECK) return GetLong64Error();
    if (!ValidateIframe(bNS, bNR)) return GetLong64Error();
    uint64_t ddw = ReadEngMon38();
    DelayOff();

    bNR++;
    Query38_RR(bNR);
    if (Input38() != SER_GOODCHECK) return GetLong64Error();
    if (!ValidateSframe(bNR)) return GetLong64Error();
    DelayOff();
  }
  else
  {
  }


  Query38_DISC();
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  DelayOff();

  return GetLong64(ddw, true);
}



double2 ReadCntMonCan38(uchar  ibMon)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    ulong64_ ddw2 = QueryCntMon38_Full(ibMon);
    if (fKey == true) break;
    if (ddw2.fValid)
    {
      ShowPercent(50);

      mpdwChannelsA[0] = ddw2.ddwValue % 0x100000000;
      mpdbChannelsC[0] = (double)mpdwChannelsA[0] / 1000;
      mpboChannelsA[0] = true;

      return GetDouble2(mpdbChannelsC[0], true);
    }
  }

  Query38_DISC();
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  return GetDouble2Error();
}
