/*------------------------------------------------------------------------------
automatic_get_cntmon_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "device38.h"
#include "io38.h"
#include "dff.h"
#include "bits2.h"
#include "automatic_get_time_38.h"
#include "automatic_get_cntmon_38.h"



bool    ReadEngDay38_Full(uchar  ibDayRel)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    QueryEngDay38(0);

    if (Input38() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (r == MaxRepeats()) return false;

  uchar ibIn = 10;

  uchar i;
  for (i=0; i<4; i++)
  {
    ibIn++;

    uint64_t ddw = 0;
    uchar delta = pucDecodeBitArr((uchar *) &ddw, InBuffPtr(ibIn));
    if (delta == 0xFF) return false;
    ibIn += delta;

    ulong dw = ddw % 0x100000000;
    uchar bStatus = (ddw % 0x100) & 0x03;
    dw >>= 3;

    if (bStatus != 0) {
      Clear();
      sprintf(szLo+1, "сутки -%u, %u ?", ibDayRel, bStatus);
      Delay(1000);
      return false;
    }

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

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    QueryEngMon38(ibMonRel);

    if (Input38() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  uchar ibIn = 10;

  uchar i;
  for (i=0; i<4; i++)
  {
    ibIn++;

    uint64_t ddw = 0;
    uchar delta = pucDecodeBitArr((uchar *) &ddw, InBuffPtr(ibIn));
    if (delta == 0xFF) return false;
    ibIn += delta;

    ulong dw = ddw % 0x100000000;
    uchar bStatus = (ddw % 0x100) & 0x03;
    dw >>= 3;

    if (bStatus != 0) {
      Clear();
      sprintf(szLo+1, "мес€ц -%u, %u ?", ibMonRel, bStatus);
      Delay(1000);
      return false;
    }

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
    if (ReadEngDay38_Full(0) == false) return GetDouble2Error();
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}
