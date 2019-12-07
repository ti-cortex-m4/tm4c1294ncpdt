/*------------------------------------------------------------------------------
auto_flow.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "auto_flow.h"




bool                    fAutoFlowEnbl;
uchar                   mpibAutoFlowHou[48];
auto_flow               stAutoFlow;



cache const             chAutoFlowEnbl = {AUTO_FLOW_ENBL, &fAutoFlowEnbl, sizeof(bool)};
cache const             chAutoFlowHou = {AUTO_FLOW_HOU, &mpibAutoFlowHou, sizeof(mpibAutoFlowHou)};
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
