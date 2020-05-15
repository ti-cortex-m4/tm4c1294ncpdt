/*------------------------------------------------------------------------------
automatic_get_cntcurr_36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "device36.h"
#include "io36.h"
#include "monitor36.h"
#include "automatic_get_cntcurr_36.h"



double2 QueryCntCurr38_Full(void)
{
  Query36_DISC();
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  Query36_SNRM();
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query36_Open2(bNS, bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();

  uchar i;
  for (i=0; i<4; i++) {
    bNS++;
    QueryEngAbs36(bNS, bNR, bInvokeId++, i);
    if (Input36() != SER_GOODCHECK) return GetDouble2Error();
    if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();

    uint64_t ddw = ReadEngAbs36();
    mpdwChannelsA[i] = ddw % 0x100000000;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 1000;
    mpboChannelsA[i] = true;

    DelayOff();

    bNR++;
    Query38_RR(bNR);
    if (Input36() != SER_GOODCHECK) return GetDouble2Error();
    if (!ValidateSframe(bNR)) return GetDouble2Error();
    DelayOff();
  }

  Query36_DISC(); // TODO always close
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
/*
  Clear();

  if (QueryConfig36_Full(50) == 0) return GetDouble2Error();

  if (QueryEngMon36_Full(0, 75) == 0) return GetDouble2Error();

  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / GetDivider36();
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
*/
}



time2   ReadCntCurr38(void)
{
  Clear();


  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    time2 ti2 = QueryCntCurr38_Full();
    if (fKey == true) break;
    if (ti2.fValid)
    {
      ShowPercent(50);

      tiChannelC = ti2.tiValue;
      mpboChannelsA[0] = true;

      return GetTime2(ti2.tiValue, true);
    }
  }

  Query36_DISC();
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  DelayOff();

  return GetTime2Error();
}
