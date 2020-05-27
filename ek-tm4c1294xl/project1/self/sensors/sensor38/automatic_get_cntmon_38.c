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
 #include "../../digitals/digitals.h"
#include "device38.h"
#include "io38.h"
#include "automatic_get_time_38.h"
#include "automatic_get_cntmon_38.h"



bool    ReadEngDay38_Full(void)
{
  Clear();

  uchar i;
  for (i=0; i<1/*4*/; i++)
  {
    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      ShowPercent(50 + i);
      QueryEngDay38(0, i);

      if (Input38() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == MaxRepeats()) return false;


    uint64_t ddw = ReadEngStatus38(11);
    ulong dw = ddw % 0x100000000;
    uchar bStatus = (ddw % 0x100) & 0x03;
    dw >>= 3;

    mpdwChannelsA[i] = dw;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 10000;
  }


  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return true;
}



bool    ReadEngMon38_Full(uchar  ibMonRel)
{
  Clear();

  uchar i;
  for (i=0; i<1/*4*/; i++)
  {
    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      ShowPercent(50 + i);
      QueryEngMon38(ibMonRel, i);

      if (Input38() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == MaxRepeats()) return false;


    uint64_t ddw = ReadEngStatus38(11);
    ulong dw = ddw % 0x100000000;
    uchar bStatus = (ddw % 0x100) & 0x03;
    dw >>= 3;

    mpdwChannelsA[i] = dw;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 10000;
  }


  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return true;
}



double2 ReadCntMonCan38(uchar  ibMonAbs)
{
//  MonitorString("\n ibMonAbs="); MonitorCharDec(ibMonAbs);
  Clear();

  time2 ti2 = ReadTimeCan38();
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMonAbs+1)
  {
    uchar ibMonRel = (bMONTHS+ti.bMonth-2-ibMonAbs) % bMONTHS;
    if (ReadEngMon38_Full(ibMonRel) == false) return GetDouble2Error();
  }
  else
  {
    if (ReadEngDay38_Full() == false) return GetDouble2Error();
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}
