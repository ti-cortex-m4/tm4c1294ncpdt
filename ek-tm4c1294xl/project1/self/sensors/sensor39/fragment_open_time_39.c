/*------------------------------------------------------------------------------
fragment_open_time_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "device39.h"
#include "time39.h"
#include "io39.h"
#include "fragment_open_39.h"
#include "fragment_open_time_39.h"



time2   FragmentOpenTime39(caller39  *pc)
{
  if (FragmentOpen39(pc) != 0) return GetTime2Error1(191);

  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryTime39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId);
  if (Input39() != SER_GOODCHECK) return GetTime2Error1(192);
  if (!ValidateFrame((*pc).bNS, (*pc).bNR)) return GetTime2Error1(193);
  time tm = ReadTime39();

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return GetTime2Error1(194);
  if (!ValidateFrame((*pc).bNS, (*pc).bNR)) return GetTime2Error1(195);

  return GetTime0(tm);
}
