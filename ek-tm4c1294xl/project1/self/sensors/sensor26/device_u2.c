/*------------------------------------------------------------------------------
DEVICE_U2.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../device_k.h"
#include "../device_q.h"
#include "device_u2.h"



void    ReadEnergyTariffU(uchar  ibLine, uchar  ibTrf)
{
double db;

  InitPop(1);

  uchar i;
  for (i=0; i<ibTrf+2; i++)
  {
    db = PopDoubleQ();
  }

  mpdbChannelsC[ibLine] = db;
  mpboChannelsA[ibLine] = true;
}
