/*------------------------------------------------------------------------------
DSBL_ANSWER.H


------------------------------------------------------------------------------*/

extern  cache const             chDsblAnswer;



void    InitDisableAnswer(void);
void    ResetDisableAnswer(void);

void    EnableAnswer(void);
void    DisableAnswer(void);
bool    AnswerDisabled(void);

void    OutDsblAnswer(void);
