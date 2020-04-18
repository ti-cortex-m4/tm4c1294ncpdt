/*------------------------------------------------------------------------------
AUTOMATIC36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
//#include "../../time/delay.h"
//#include "../../serial/ports.h"
//#include "../../devices/devices.h"
//#include "../../sensors/automatic1.h"
//#include "../../digitals/digitals.h"
//#include "device35.h"
//#include "io35.h"
#include "automatic36.h"



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


bool    QueryEngDay35_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngDay35(bTime);

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadEnergy35();
  return(1);
}


bool    QueryEngMon35_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngMon35(bTime);

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadEnergy35();
  return(1);
}



time2   ReadTimeCan36(void)
{
  Clear();

  time2 ti2;

  return GetTime2(ti2.tiValue, true);
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
