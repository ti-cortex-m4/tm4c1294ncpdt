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
  if (Input39() != SER_GOODCHECK) return 180;

  Query39_SNRM();
  if (Input39() != SER_GOODCHECK) return 181;

  Query39_AARQ((*pc).bNS, (*pc).bNR);
  if (Input39() != SER_GOODCHECK) return 182;
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return 183;

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return 184;
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return 185;

  return 0;
}
