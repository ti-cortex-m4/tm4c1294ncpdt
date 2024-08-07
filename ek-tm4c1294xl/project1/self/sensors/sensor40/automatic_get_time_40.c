/*------------------------------------------------------------------------------
automatic_get_time_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "dlms.h"
#include "time40.h"
#include "io40.h"
#include "caller40.h"
#include "error40.h"
#include "fragment_open_time_40.h"
#include "automatic_get_time_40.h"



static time2 Fault(uchar  bError)
{
  return GetTime2Error1(Error40(bError));
}



time2   ReadTimeCan39_Internal(void)
{
  caller40 c = InitCaller40();

  time2 tm2 = FragmentOpenTime40(&c);
  if (!tm2.fValid) return Fault(50+0);

  DISC();
  if (Input40() != SER_GOODCHECK) return Fault(50+1);

  return GetTime0(tm2.tiValue);
}



time2   ReadTimeCan40(void)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    time2 tm2 = ReadTimeCan39_Internal();
    if (fKey == true) break;
    if (tm2.fValid)
    {
      tiChannelC = tm2.tiValue;

      uchar i;
      for (i=0; i<4; i++)
        mpboChannelsA[i] = true;

      return GetTime0(tm2.tiValue);
    }
  }

  DISC();
  if (Input40() != SER_GOODCHECK) return Fault(50+2);

  return Fault(50+3);
}



time2   ReadTimeCan40_Short(void)
{
  Clear();

  time2 tm2 = ReadTimeCan39_Internal();
  if (tm2.fValid)
  {
    return GetTime0(tm2.tiValue);
  }

  DISC();
  if (Input40() != SER_GOODCHECK) return Fault(50+4);

  return Fault(50+5);
}
