/*------------------------------------------------------------------------------
current38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../display/messages.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "../../digitals/current/current_run.h"
#include "dff.h"
#include "current38.h"



void    ReadCurrent38(void)
{
  uchar ibIn = 10;

  uchar i;
  for (i=0; i<4; i++)
  {
    ibIn++;

    uint64_t ddw = 0;
    uchar delta = pucDecodeBitArr((uchar *) &ddw, InBuffPtr(ibIn));
    if (delta == 0xFF) { Error(); DelayInf(); return; }
    ibIn += delta;

    mpdbChannelsC[i] = (double)(ddw % 0x100000000) / 10000;
    mpdwBaseDig[i] = mpdbChannelsC[i] * mpdbPulseMnt[ibDig];
  }

  MakeCurrent();
}
