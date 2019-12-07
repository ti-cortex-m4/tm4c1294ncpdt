/*------------------------------------------------------------------------------
auto_flow.h


------------------------------------------------------------------------------*/

#ifndef __AUTO_FLOW
#define __AUTO_FLOW


typedef struct
{
  bool          fEnabled;
  uchar         bMinuteStart;
  uchar         bMinuteStop;
} auto_flow;


#endif



extern  auto_flow               stAutoFlow;
extern  cache const             chAutoFlow;



void    InitAutoTransit(void);
void    ResetAutoFlow(void);
