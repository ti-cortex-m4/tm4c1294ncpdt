/*------------------------------------------------------------------------------
fragment_open_time_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "device39.h"
#include "caller39.h"
#include "time39.h"
#include "io39.h"
#include "error39.h"
#include "fragment_open_39.h"
#include "fragment_open_time_39.h"



static time2 Fault(uchar  bError)
{
  return GetTime2Error1(Error39(bError));
}



time2   FragmentOpenTime39(caller39  *pc)
{
  uchar bError = FragmentOpen39(pc);
  if (bError != 0) return GetTime2Error1(190+0);

  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryTime39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId);
  if (Input39() != SER_GOODCHECK) return Fault(190+1);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(190+2);
  time tm = ReadTime39();

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return Fault(190+3);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(190+4);

  return GetTime0(tm);
}
