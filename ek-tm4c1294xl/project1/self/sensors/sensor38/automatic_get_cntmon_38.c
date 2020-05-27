/*------------------------------------------------------------------------------
automatic_get_cntmon_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
// #include "../../time/timedate.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
// #include "../../sensors/automatic1.h"
// #include "../../digitals/digitals.h"
#include "device38.h"
#include "io38.h"
#include "automatic_get_cntmon_38.h"



double2 ReadCntDay38_Full(uchar  ibDayRel)
{
  Clear();

  uchar i;
  for (i=0; i<4; i++)
  {
    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      ShowPercent(50 + i);
      QueryEngDay38(i,ibDayRel);

      if (Input38() == SER_GOODCHECK) break;
      if (fKey == true) return GetDouble2Error();
    }

    if (r == MaxRepeats()) return GetDouble2Error();

    mpdwChannelsA[i] = ReadEngAbs38(11) % 0x100000000;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 10000;
  }


  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}


double2 ReadCntMon38_Full(uchar  ibMonRel)
{
  Clear();

  uchar i;
  for (i=0; i<4; i++)
  {
    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      ShowPercent(50 + i);
      QueryEngMon38(i,ibMonRel);

      if (Input38() == SER_GOODCHECK) break;
      if (fKey == true) return GetDouble2Error();
    }

    if (r == MaxRepeats()) return GetDouble2Error();

    mpdwChannelsA[i] = ReadEngAbs38(11) % 0x100000000;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 10000;
  }


  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



double2 ReadCntMonCan38_(uchar  ibMonAbs)
{
  Clear();

  time2 ti2 = ReadTimeCan38(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMon+1)
  {
    uchar ibMonRel = (bMONTHS+ti.bMonth-1-ibMon) % bMONTHS;
    if (ReadEngMon38_Full(ibMonRel, 75) == 0) return GetDouble2Error();
  }
  else
  {
    if (ReadEngDay38_Full(0, 75) == 0) return GetDouble2Error();
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}
