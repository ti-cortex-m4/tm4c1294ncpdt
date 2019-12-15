/*------------------------------------------------------------------------------
auto_flow.h


------------------------------------------------------------------------------*/


extern  char const              szByAutoFlow[];


extern  bool                    fAutoFlowEnbl;
extern  uchar                   mpibAutoFlowHou[48];


extern  cache const             chAutoFlowEnbl;
extern  cache const             chAutoFlowHou;



void    InitAutoFlow(void);
void    ResetAutoFlow(void);

bool    IsAutoFlowTime(void);
bool    IsAutoFlowTo3(void);
bool    IsAutoFlowTo4(void);
