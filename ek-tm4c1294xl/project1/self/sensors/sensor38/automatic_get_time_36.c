/*------------------------------------------------------------------------------
automatic_get_time_36.c


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
#include "automatic36.h"



time2   QueryTime38_Full(void)
{
  Query36_DISC();
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  DelayOff();

  Query36_SNRM();
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query36_Open2(bNS, bNR);
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateIframe(bNS, bNR)) return GetTime2Error();
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateSframe(bNR)) return GetTime2Error();
  DelayOff();

  bNS++;
  bInvokeId++;
  QueryTime38(bNS, bNR, bInvokeId);
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateIframe(bNS, bNR)) return GetTime2Error();
  time ti = ReadTime36();
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateSframe(bNR)) return GetTime2Error();
  DelayOff();

  Query36_DISC(); // TODO always close
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  DelayOff();

/*
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryTime36();

    if (Input36() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (i == MaxRepeats()) return GetTime2Error();
  ShowPercent(bPercent);
*/
  return GetTime2(ti, true);
}


time2   ReadTimeCan38(void)
{
  Clear();


  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    time2 ti2 = QueryTime38_Full();

    if (ti2.fValid) break;
    if (fKey == true) return GetTime2Error();
  }

  if (r == MaxRepeats()) return GetTime2Error();
  ShowPercent(50);


  tiChannelC = ti2.tiValue;
  mpboChannelsA[0] = true;

  return GetTime2(ti2.tiValue, true);
}



time2   ReadTimeCan36_Short(void)
{
  Clear();


  time2 ti2 = QueryTime38_Full();
  if (ti2.fValid == false) return GetTime2Error();


  tiChannelC = ti2.tiValue;
  mpboChannelsA[0] = true;

  return GetTime2(ti2.tiValue, true);
}


