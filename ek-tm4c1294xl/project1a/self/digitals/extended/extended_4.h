/*------------------------------------------------------------------------------
EXTENDED_4,H


------------------------------------------------------------------------------*/

#include "../../memory/mem_extended_4.h"



extern  cache const             chExt4Flag;
extern  cache const             chExt4Months;
extern  file const              flExt4EnblCan;



bool    LoadExt4Values(uchar  ibMon);

void    InitExtended4(void);
void    ResetExtended4(bool  fFull);

void    NextDayExtended4(void);
void    NextMonExtended4(void);

void    MakeExtended4(void);
