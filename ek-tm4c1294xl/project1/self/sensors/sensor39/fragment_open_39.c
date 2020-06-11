/*------------------------------------------------------------------------------
fragment_open_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "device39.h"
#include "io39.h"
#include "fragment_open_39.h"



uchar   FragmentOpen39(runner39  *pr)
{
  Query38_DISC();
  if (Input39() != SER_GOODCHECK) return 1;
  DelayOff();

  Query38_SNRM();
  if (Input39() != SER_GOODCHECK) return 2;
  DelayOff();

  Query38_Open2((*pr).bNS, (*pr).bNR);
  if (Input39() != SER_GOODCHECK) return 3;
  if (!ValidateIframe((*pr).bNS, (*pr).bNR)) return 4;
  DelayOff();

  (*pr).bNR++;
  Query38_RR((*pr).bNR);
  if (Input39() != SER_GOODCHECK) return 5;
  if (!ValidateSframe((*pr).bNR)) return 6;
  DelayOff();

  return 0;
}
