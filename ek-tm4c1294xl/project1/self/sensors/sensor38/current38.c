/*------------------------------------------------------------------------------
current38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "../../digitals/current/current_run.h"
#include "current38.h"



uchar                   ibLine38;



void    ReadEngAbsCurrent38(void)
{
  // InitPop(1);

  // mpdbChannelsC[ibLine38] = PopDoubleQ();
}


void    ReadCurrent38(void)
{
  uchar i;
  for (i=0; i<4; i++)
  {
    mpdwBaseDig[i] = mpdbChannelsC[i] * mpdbPulseMnt[ibDig];
  }

  MakeCurrent();
}