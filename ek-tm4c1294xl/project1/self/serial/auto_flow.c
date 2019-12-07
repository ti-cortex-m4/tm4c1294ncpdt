/*------------------------------------------------------------------------------
auto_flow.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "auto_flow.h"



auto_flow               stAutoFlow;
cache const             chAutoFlow = {AUTO_FLOW, &stAutoFlow, sizeof(stAutoFlow)};



void    InitAutoFlow(void)
{
  LoadCache(&chAutoFlow);
}



void    ResetAutoFlow(void)
{
  stAutoFlow.fEnabled     = false;
  stAutoFlow.bMinuteStart = 3;
  stAutoFlow.bMinuteStop  = 27;

  SaveCache(&chAutoFlow);
}
