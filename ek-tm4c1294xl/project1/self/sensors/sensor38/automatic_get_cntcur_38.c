/*------------------------------------------------------------------------------
automatic_get_cntcur_38.c


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
#include "automatic_get_cntcur_38.h"



double2 ReadCntCurr38(void)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    QueryEngAbs38();

    if (Input38() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == MaxRepeats()) return GetDouble2Error();

  uchar* pbIn = InBuffPtr(10);

  uchar i;
  for (i=0; i<4; i++)
  {
    *(pbIn++);

    int64_t ddw = 0;
    pbIn = DffDecodePositive(pbIn, &ddw);

    mpdwChannelsA[i] = ddw % 0x100000000;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 10000;
  }


  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}
