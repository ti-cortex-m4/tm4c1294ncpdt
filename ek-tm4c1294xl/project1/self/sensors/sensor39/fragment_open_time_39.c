/*------------------------------------------------------------------------------
fragment_open_time_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "device39.h"
#include "time39.h"
#include "io39.h"
#include "error39.h"
#include "fragment_open_39.h"
#include "fragment_open_time_39.h"



time2   FragmentOpenTime39(caller39  *pc)
{
  uchar bError = FragmentOpen39(pc);
  if (bError != 0) return GetTime2Error1(bError);

  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryTime39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId);
  if (Input39() != SER_GOODCHECK) return GetTime2Error1(Error39(190));
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return GetTime2Error1(Error39(191));
  time tm = ReadTime39();

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return GetTime2Error1(Error39(192));
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return GetTime2Error1(Error39(193));

  return GetTime0(tm);
}
