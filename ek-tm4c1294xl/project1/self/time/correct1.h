/*------------------------------------------------------------------------------
CORRECT1,H


------------------------------------------------------------------------------*/

extern  cache const             chCorrect1;



void    InitCorrect1(void);
void    ResetCorrect1(void);

void    NextMonCorrect1(void);

uchar   GetCorrectIndex(event  ev);

void    SetCurrTime_Full(time  ti, event  ev);
bool    CorrectTime_Full(event  ev);
