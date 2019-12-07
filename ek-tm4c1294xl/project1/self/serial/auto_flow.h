/*------------------------------------------------------------------------------
auto_flow.h


------------------------------------------------------------------------------*/

#ifndef __AUTO_FLOW
#define __AUTO_FLOW


typedef struct
{
  uchar         bMinuteStart;
  uchar         bMinuteStop;
} auto_flow;


#endif


extern  bool                    fAutoFlowEnbl;
extern  uchar                   mpibAutoFlowHou[48];
extern  auto_flow               stAutoFlow;


extern  cache const             chAutoFlowEnbl;
extern  cache const             chAutoFlowHou;
extern  cache const             chAutoFlow;



void    InitAutoFlow(void);
void    ResetAutoFlow(void);
bool    IsValidAutoFlow(auto_flow  af);

bool    RunAutoFlow(uchar  ibPrt);
