/*------------------------------------------------------------------------------
AUTOMATIC_K.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_factors.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
//#include "../digitals/digitals_messages.h"
//#include "automatic1.h"
#include "device_k.h"
#include "automatic_k.h"



time2   ReadTimeCanK(void)
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryCloseK();
    QueryTimeK();

    if (BccInput() != SER_GOODCHECK) break;
  }

  if (i == bMINORREPEATS) return GetTime2(tiZero, false);
  ShowPercent(25);

  time ti = ReadTimeK();


  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryCloseK();
    QueryDateK();

    if (BccInput() == SER_GOODCHECK) break;
  }

  if (i == bMINORREPEATS) return GetTime2(tiZero, false);
  ShowPercent(50);

  ti = ReadDateK(ti);


  QueryCloseK();


  tiChannelC = ti2;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;

  return GetTime2(ti2, true);
}
