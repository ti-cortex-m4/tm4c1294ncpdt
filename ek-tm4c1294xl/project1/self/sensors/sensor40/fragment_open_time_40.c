/*------------------------------------------------------------------------------
fragment_open_time_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "dlms.h"
#include "caller40.h"
#include "time40.h"
#include "io40.h"
#include "error40.h"
#include "fragment_open_40.h"
#include "fragment_open_time_40.h"



static time2 Fault(uchar  bError)
{
  return GetTime2Error1(Error40(bError));
}



time2   FragmentOpenTime40(caller40  *pc)
{
  uchar bError = FragmentOpen40(pc);
  if (bError != 0) return GetTime2Error1(120+0);

  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryTime40(*pc);
  if (Input40() != SER_GOODCHECK) return Fault(120+1);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(120+2);
  time tm = ReadTime40();

  (*pc).bNR++;
  RR((*pc).bNR);
  if (Input40() != SER_GOODCHECK) return Fault(120+3);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(120+4);

  return GetTime0(tm);
}
