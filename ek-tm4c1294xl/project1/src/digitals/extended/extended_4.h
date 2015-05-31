/*------------------------------------------------------------------------------
EXTENDED_4,H


------------------------------------------------------------------------------*/

#include "../../memory/mem_extended_4.h"



extern  file const              flExt4Flag;
extern  file const              flExt4Months;
extern  file const              flExt4EnblCan;



bool    LoadExt4Values(uchar  ibMon);

void    InitExtended4(void);
void    ResetExtended4(bool  fFull);

void    NextDayExtended4(void);
void    NextMonExtended4(void);

void    MakeExtended4(void);
