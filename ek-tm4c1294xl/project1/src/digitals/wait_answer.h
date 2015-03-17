/*------------------------------------------------------------------------------
WAIT_ANSWER.H


------------------------------------------------------------------------------*/

extern  uchar                   cbWaitAnswer;



void    WaitAnswer_1Hz(void);
void    InitWaitAnswer(void);
void    ShowWaitAnswer(bool  fShow);
bool    GetWaitAnswer(void);
