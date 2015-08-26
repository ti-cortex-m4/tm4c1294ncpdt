/*------------------------------------------------------------------------------
CORRECT3.H


------------------------------------------------------------------------------*/

#include "../memory/mem_correct3.h"



extern  cache const             chCorrect3Flag;
extern  cache const             chCorrect3Max;



void    InitCorrect3(void);
void    ResetCorrect3(void);

bool    Correct3Disabled(void);
void    Correct3(event  ev);
void    OutCorrect3(void);
