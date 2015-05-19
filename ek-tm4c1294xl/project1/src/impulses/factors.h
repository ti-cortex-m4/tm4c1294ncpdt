/*------------------------------------------------------------------------------
FACTORS,H


------------------------------------------------------------------------------*/

#include "../memory/mem_factors.h"



extern  file const              flTransEng;
extern  file const              flTransCnt;

extern  file const              flPulseHou;
extern  file const              flPulseMnt;

extern  file const              flCount;
extern  file const              flLosse;
extern  file const              flLevelDiv;



void    InitFactors(void);
void    ResetFactors(void);

void    SaveFactors(void);

void    StartFactors(void);
