/*------------------------------------------------------------------------------
fragment_open_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "dlms.h"
#include "caller40.h"
#include "io39.h"
#include "error40.h"
#include "fragment_open_39.h"



uchar   FragmentOpen39(caller40  *pc)
{
  DISC();
  if (Input39() != SER_GOODCHECK) return Error40(110+0);

  SNRM();
  if (Input39() != SER_GOODCHECK) return Error40(110+1);

  AARQ((*pc).bNS, (*pc).bNR);
  if (Input39() != SER_GOODCHECK) return Error40(110+2);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Error40(110+3);

  if (!AARE_CheckPass()) Error40(110+4);

  (*pc).bNR++;
  RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return Error40(110+5);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Error40(110+6);

  return 0;
}
