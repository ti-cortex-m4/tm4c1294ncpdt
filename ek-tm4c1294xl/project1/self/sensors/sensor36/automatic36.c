/*------------------------------------------------------------------------------
AUTOMATIC36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
//#include "../../time/delay.h"
#include "../../serial/ports.h"
//#include "../../devices/devices.h"
//#include "../../sensors/automatic1.h"
//#include "../../digitals/digitals.h"
#include "device36.h"
//#include "io35.h"
#include "automatic36.h"


/*
time2   QueryTime36_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryTime35();

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (i == MaxRepeats()) return GetTime2Error();
  ShowPercent(bPercent);

  return GetTime2(ReadTime35(), true);
}
*/


time2   ReadTimeCan36(void)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    //QueryCloseK();
    QueryTime36();

    if (BccInput() == SER_GOODCHECK) break;
  }

  if (r == MaxRepeats()) return GetTime2Error();
  ShowPercent(25);

  time ti = ReadTime36();


  for (r=0; r<MaxRepeats(); r++)
  {
    //QueryCloseK();
    QueryDate36();

    if (BccInput() == SER_GOODCHECK) break;
  }

  if (r == MaxRepeats()) return GetTime2Error();
  ShowPercent(50);

  ti = ReadDate36(ti);


  QueryCloseK();


  tiChannelC = ti;

  uchar i;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;

  return GetTime2(ti, true);
}

/*
time2   ReadTimeCan35_Short(void)
{
  DelayOff();
  QueryTime35();

  if (Input35() != SER_GOODCHECK) return GetTime2Error();


  return GetTime2(ReadTime35(), true);
}
*/
