/*------------------------------------------------------------------------------
DSBL_ANSWER!H


------------------------------------------------------------------------------*/

extern  cache const             chDsblAnswer;



void    InitDsblAnswer(void);
void    ResetDsblAnswer(void);

void    EnableAnswer(void);
void    DisableAnswer(void);
bool    IsAnswerDisabled(void);

void    OutEnableAnswer(void);
void    OutDsblAnswer(void);
