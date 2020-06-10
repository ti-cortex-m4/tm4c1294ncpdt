/*------------------------------------------------------------------------------
fragment_open_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "device38.h"
#include "io38.h"
#include "monitor38.h"
#include "fragment_open_38.h"



uchar   FragmentOpen38(runner38  *runner)
{
  Query38_DISC();
  if (Input38() != SER_GOODCHECK) return 1;
  DelayOff();

  Query38_SNRM();
  if (Input38() != SER_GOODCHECK) return 2;
  DelayOff();

  Query38_Open2((*runner).bNS, (*runner).bNS);
  if (Input38() != SER_GOODCHECK) return 3;
  if (!ValidateIframe((*runner).bNS, (*runner).bNS)) return 4;
  DelayOff();

  (*runner).bNS++;
  Query38_RR((*runner).bNS);
  if (Input38() != SER_GOODCHECK) return 5;
  if (!ValidateSframe((*runner).bNS)) return 6;
  DelayOff();

  return 0;
}
