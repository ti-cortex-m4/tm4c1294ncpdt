/*------------------------------------------------------------------------------
fragment_open_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "device38.h"
#include "io39.h"
#include "monitor38.h"
#include "fragment_open_38.h"



uchar   FragmentOpen38(runner39  *runner)
{
  Query38_DISC();
  if (Input39() != SER_GOODCHECK) return 1;
  DelayOff();

  Query38_SNRM();
  if (Input39() != SER_GOODCHECK) return 2;
  DelayOff();

  Query38_Open2((*runner).bNS, (*runner).bNR);
  if (Input39() != SER_GOODCHECK) return 3;
  if (!ValidateIframe((*runner).bNS, (*runner).bNR)) return 4;
  DelayOff();

  (*runner).bNR++;
  Query38_RR((*runner).bNR);
  if (Input39() != SER_GOODCHECK) return 5;
  if (!ValidateSframe((*runner).bNR)) return 6;
  DelayOff();

  return 0;
}
