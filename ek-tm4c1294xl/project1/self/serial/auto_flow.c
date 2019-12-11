/*------------------------------------------------------------------------------
auto_flow.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../keyboard/keyboard.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../realtime/realtime.h"
#include "flow.h"
#include "auto_flow.h"




bool                    fAutoFlowEnbl;
uchar                   mpibAutoFlowHou[48];
auto_flow               stAutoFlow;



cache const             chAutoFlowEnbl = {AUTO_FLOW_ENBL, &fAutoFlowEnbl, sizeof(bool)};
cache const             chAutoFlowHou = {AUTO_FLOW_HOU, &mpibAutoFlowHou, sizeof(mpibAutoFlowHou)};
cache const             chAutoFlow = {AUTO_FLOW, &stAutoFlow, sizeof(stAutoFlow)};



void    InitAutoFlow(void)
{
  LoadCacheBool(&chAutoFlowEnbl, false);

  LoadCache(&chAutoFlowHou);

  LoadCache(&chAutoFlow);
}



void    ResetAutoFlow(void)
{
  SaveCacheBool(&chAutoFlowEnbl, false);


  uchar i;
  for (i=0; i<48; i++)
    mpibAutoFlowHou[i] = false;

  SaveCache(&chAutoFlowHou);


  stAutoFlow.bMinuteStart = 1;
  stAutoFlow.bMinuteStop  = 29;
  SaveCache(&chAutoFlow);
}



bool    IsValidAutoFlow(auto_flow  af)
{
  if (af.bMinuteStart >= 30)
    return false;

  if (af.bMinuteStop >= 30)
    return false;

  if (af.bMinuteStart >= af.bMinuteStop)
    return false;

  return true;
}



bool    IsAutoFlowTo3(void)
{
  return fAutoFlowEnbl && (mpibAutoFlowHou[GetCurrHouIndex()] == 3-1);
}


bool    IsAutoFlowTo4(void)
{
  return fAutoFlowEnbl && (mpibAutoFlowHou[GetCurrHouIndex()] == 4-1);
}
