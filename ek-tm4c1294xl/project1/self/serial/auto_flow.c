/*------------------------------------------------------------------------------
auto_flow.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "auto_flow.h"



cache const             chTransitHou = {TRANSIT_HOU, &mpibAutoFlowHou, sizeof(mpibAutoFlowHou)};

auto_flow               stAutoFlow;
cache const             chAutoFlow = {AUTO_FLOW, &stAutoFlow, sizeof(stAutoFlow)};



void    InitAutoFlow(void)
{

    LoadCache(&chTransitHou);
  LoadCache(&chAutoFlow);
}



void    ResetAutoFlow(void)
{
  for (h=0; h<48; h++)
      mpibAutoFlowHou[h] = false;

  SaveCache(&chTransitHou);


  stAutoFlow.fEnabled     = false;
  stAutoFlow.bMinuteStart = 3;
  stAutoFlow.bMinuteStop  = 27;

  SaveCache(&chAutoFlow);
}
