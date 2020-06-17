/*------------------------------------------------------------------------------
fragment_open_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "device39.h"
#include "io39.h"
#include "fragment_open_39.h"



uchar   FragmentOpen39(caller39  *pc)
{
  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return 1;

  Query39_SNRM();
  if (Input39() != SER_GOODCHECK) return 2;

  Query39_AARQ((*pc).bNS, (*pc).bNR);
  if (Input39() != SER_GOODCHECK) return 3;
  if (!ValidateIframe((*pc).bNS, (*pc).bNR)) return 4;

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return 5;
  if (!ValidateSframe((*pc).bNR)) return 6;

  return 0;
}
