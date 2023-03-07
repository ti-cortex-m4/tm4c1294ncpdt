/*------------------------------------------------------------------------------
current38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "../../digitals/current/current_run.h"
#include "../sensor38/dff.h"
#include "current41.h"



void    ReadCurrent41(void)
{
  uchar* pbIn = InBuffPtr(16);

  uchar i;
  for (i=0; i<4; i++)
  {
    *(pbIn++);

    int64_t ddw = 0;
    pbIn = DffDecodePositive(pbIn, &ddw);

    mpdbChannelsC[i] = (double)(ddw % 0x100000000) / 10000;
    mpdwBaseDig[i] = mpdbChannelsC[i] * mpdbPulseMnt[ibDig];
  }

  MakeCurrent();
}
