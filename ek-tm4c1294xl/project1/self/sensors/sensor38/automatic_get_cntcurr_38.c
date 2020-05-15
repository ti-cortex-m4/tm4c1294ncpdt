/*------------------------------------------------------------------------------
automatic_get_cntcurr_38.c


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
#include "automatic_get_cntcurr_38.h"



double2 QueryCntCurr38_Full(void)
{
  Query38_DISC();
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  Query38_SNRM();
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query38_Open2(bNS, bNR);
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();

  uchar i;
  for (i=0; i<4; i++) {
    bNS++;
    QueryEngAbs36(bNS, bNR, bInvokeId++, i);
    if (Input38() != SER_GOODCHECK) return GetDouble2Error();
    if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();

    uint64_t ddw = ReadEngAbs36();
    mpdwChannelsA[i] = ddw % 0x100000000;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 1000;
    mpboChannelsA[i] = true;

    DelayOff();

    bNR++;
    Query38_RR(bNR);
    if (Input38() != SER_GOODCHECK) return GetDouble2Error();
    if (!ValidateSframe(bNR)) return GetDouble2Error();
    DelayOff();
  }

  Query38_DISC(); // TODO always close
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
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



double2 ReadCntCurr38(void)
{
  Clear();


  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    double2 db2 = QueryCntCurr38_Full();
    if (fKey == true) break;
    if (db2.fValid)
    {
      ShowPercent(50);

      mpdbChannelsC[0] = db2.dbValue;
      mpboChannelsA[0] = true;

      return GetDouble2(db2.dbValue, true);
    }
  }

  Query38_DISC();
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  return GetDouble2Error();
}
