/*------------------------------------------------------------------------------
FACTORS,H


------------------------------------------------------------------------------*/

#include "../memory/mem_factors.h"



extern  cache const             chTransEng;
extern  cache const             chTransCnt;

extern  cache const             chPulseHou;
extern  cache const             chPulseMnt;

extern  cache const             chCount;
extern  cache const             chLosse;
extern  cache const             chLevel;



void    InitFactors(void);
void    ResetFactors(void);

void    SaveFactors(void);

void    StartFactors(void);
