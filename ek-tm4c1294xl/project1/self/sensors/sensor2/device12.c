/*------------------------------------------------------------------------------
DEVICE12!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_factors.h"
#include "../../devices/devices.h"
#include "../../digitals/current/current2.h"
#include "device2.h"
#include "device12.h"



void    ReadCurrentB12(void)
{
  ReadEnergyB();
  double db = mpdbLevel[ibDig];

  uchar i;
  for (i=0; i<4; i++)
  {
    mpdwBaseDig[i] = mpdwChannelsA[i] * db;
  }

  MakeCurrent2();
}
