/*------------------------------------------------------------------------------
fragment_open_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "dlms.h"
#include "caller40.h"
#include "io40.h"
#include "error40.h"
#include "dlms_aare.h"
#include "fragment_open_40.h"



uchar   FragmentOpen40(caller40  *pc)
{
  DISC();
  if (Input40() != SER_GOODCHECK) return Error40(110+0);

  SNRM();
  if (Input40() != SER_GOODCHECK) return Error40(110+1);

  AARQ((*pc).bNS, (*pc).bNR);
  if (Input40() != SER_GOODCHECK) return Error40(110+2);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Error40(110+3);

  if (!AARE_CheckPass()) Error40(110+4);

  (*pc).bNR++;
  RR((*pc).bNR);
  if (Input40() != SER_GOODCHECK) return Error40(110+5);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Error40(110+6);

  return 0;
}
