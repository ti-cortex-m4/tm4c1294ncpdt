/*------------------------------------------------------------------------------
AUTOMATIC36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
//#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
//#include "../../sensors/automatic1.h"
#include "../../digitals/digitals.h"
#include "device36.h"
#include "io36.h"
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

    if (Input36() == SER_GOODCHECK) break;
  }

  if (r == MaxRepeats()) return GetTime2Error();
  ShowPercent(25);

  time ti = ReadTime36();


  for (r=0; r<MaxRepeats(); r++)
  {
    //QueryCloseK();
    QueryDate36();

    if (Input36() == SER_GOODCHECK) break;
  }

  if (r == MaxRepeats()) return GetTime2Error();
  ShowPercent(50);

  ti = ReadDate36(ti);


  QueryClose36();


  tiChannelC = ti;

  uchar i;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;

  return GetTime2(ti, true);
}


time2   ReadTimeCan36_Short(void)
{
  //QueryCloseK();
  QueryTime36();

  if (Input36() != SER_GOODCHECK) return GetTime2Error();

  time ti = ReadTime36();


  //QueryCloseK();
  QueryDate36();

  if (Input36() != SER_GOODCHECK) return GetTime2Error();

  ti = ReadDate36(ti);


  QueryClose36();

  return GetTime2(ti, true);
}



double2 ReadCntCurr36(uchar  bMaxLines)
{
  Clear();

  uchar i;
  for (i=0; i<bMaxLines; i++)
  {
    if (SkipLine(ibDig, i) == true) { mpdbChannelsC[i] = 0; continue; }

    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      ShowPercent(50 + i);
      //QueryCloseU();
      QueryEngAbs36(i);

      if (Input36() == SER_GOODCHECK) break;
      if (fKey == true) return GetDouble2Error();
    }

    if (r == MaxRepeats()) return GetDouble2Error();
    ReadEng36(i);
  }

  QueryClose36();


  for (i=0; i<bMaxLines; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}
