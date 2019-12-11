/*------------------------------------------------------------------------------
auto_flow.h


------------------------------------------------------------------------------*/

extern  bool                    fAutoFlowEnbl;
extern  uchar                   mpibAutoFlowHou[48];


extern  cache const             chAutoFlowEnbl;
extern  cache const             chAutoFlowHou;



void    InitAutoFlow(void);
void    ResetAutoFlow(void);

bool    IsAutoFlowTo3(void);
bool    IsAutoFlowTo4(void);
