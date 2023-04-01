/*------------------------------------------------------------------------------
automatic_get_time_41.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/timedate.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "../sensor38/device38.h"
#include "../sensor38/time38.h"
#include "../sensor38/io38.h"
#include "include41.h"
#include "automatic_get_time_41.h"



time2   ReadTimeCan41(void)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    QueryTime38();
    if (Input38() == SER_GOODCHECK) break;
  }

  if (r == MaxRepeats()) return GetTime2Error();
  ShowPercent(25);

  time ti = ReadTime38();


  tiChannelC = ti;

  uchar i;
  for (i=0; i<MAX_LINE_41; i++)
    mpboChannelsA[i] = true;

  return GetTime2(ti, true);
}



time2   ReadTimeCan41_Short(void)
{
  QueryTime38();
  if (Input38() != SER_GOODCHECK) return GetTime2Error();
  time ti = ReadTime38();

  return GetTime2(ti, true);
}
