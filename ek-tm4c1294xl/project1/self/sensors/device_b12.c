/*------------------------------------------------------------------------------
DEVICE_B12.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_current.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_factors.h"
#include "../devices/devices.h"
#include "device_b.h"
#include "device_b12.h"



void    ReadCurrentB12(void)
{
uchar   i;
real    reBuffA;

  ReadEnergyB();
  reBuffA = mpdbLevel[ibDig];

  for (i=0; i<4; i++)
  {
    mpdwBaseDig[i] = mpdwChannelsA[i] * reBuffA;
  }

  // TODO MakeCurrent2();
}
