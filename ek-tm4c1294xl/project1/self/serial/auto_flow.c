/*------------------------------------------------------------------------------
auto_transit.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "auto_transit.h"



auto_transit            stAutoTransit;
cache const             chAutoTransit = {AUTO_TRANSIT, &stAutoTransit, sizeof(stAutoTransit)};



void    InitAutoFlow(void)
{
  LoadCache(&chAutoTransit);
}



void    ResetAutoFlow(void)
{
  stAutoTransit.fEnabled     = false;
  stAutoTransit.bMinuteStart = 3;
  stAutoTransit.bMinuteStop  = 27;

  SaveCache(&chAutoTransit);
}
