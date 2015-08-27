/*------------------------------------------------------------------------------
CORRECT2.H


------------------------------------------------------------------------------*/

#include "../memory/mem_correct2.h"



extern  cache const             chCorrect2Flag;
extern  cache const             chCorrect2Status15;



void    InitCorrect2(void);
void    ResetCorrect2(void);

bool    Correct2Disabled(void);
bool    Correct2Allowed(void);
void    Correct2(event  ev);
void    OutCorrect21(void);
