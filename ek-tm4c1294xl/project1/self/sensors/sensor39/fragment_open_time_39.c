/*------------------------------------------------------------------------------
fragment_open_time_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "device39.h"
#include "io39.h"
#include "fragment_open_time_39.h"



uchar   FragmentOpenTime39(caller39  *pc)
{
  if (FragmentOpen39(&r) != 0) return 191;

  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryTime39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId);
  if (Input39() != SER_GOODCHECK) return 7;
  if (!ValidateIframe((*pc).bNS, (*pc).bNR)) return 8;
  tiValue39 = ReadTime39();
  dwValue39 = DateToHouIndex(tiValue39);

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return 9;
  if (!ValidateSframe((*pc).bNR)) return 10;

  return 0;
}
