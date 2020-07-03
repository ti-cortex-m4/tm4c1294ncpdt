/*------------------------------------------------------------------------------
fragment_open_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "dlms.h"
#include "caller39.h"
#include "io39.h"
#include "error39.h"
#include "fragment_open_39.h"



uchar   FragmentOpen39(caller39  *pc)
{
  DISC();
  if (Input39() != SER_GOODCHECK) return Error39(115+0);

  SNRM();
  if (Input39() != SER_GOODCHECK) return Error39(115+1);

  AARQ((*pc).bNS, (*pc).bNR);
  if (Input39() != SER_GOODCHECK) return Error39(115+2);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Error39(115+3);

  (*pc).bNR++;
  RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return Error39(115+4);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Error39(115+5);

  return 0;
}
