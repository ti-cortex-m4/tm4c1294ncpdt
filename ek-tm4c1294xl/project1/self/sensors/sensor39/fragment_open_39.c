/*------------------------------------------------------------------------------
fragment_open_39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "device39.h"
#include "caller39.h"
#include "io39.h"
#include "error39.h"
#include "fragment_open_39.h"



uchar   FragmentOpen39(caller39  *pc)
{
  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return Error39(180);

  Query39_SNRM();
  if (Input39() != SER_GOODCHECK) return Error39(181);

  Query39_AARQ((*pc).bNS, (*pc).bNR);
  if (Input39() != SER_GOODCHECK) return Error39(182);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Error39(183);

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return Error39(184);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Error39(185);

  return 0;
}
