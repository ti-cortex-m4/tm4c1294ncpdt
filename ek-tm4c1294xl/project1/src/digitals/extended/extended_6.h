/*------------------------------------------------------------------------------
EXTENDED_6.H


------------------------------------------------------------------------------*/

#include "../../memory/mem_extended_6.h"



extern  file const              flExt6Flag;



bool    LoadCntMonCan6(uchar  ibMonFrom);

void    InitExtended6(void);
void    ResetExtended6(bool  fFull);

void    NextDayExtended6(void);
void    NextMonExtended6(void);

void    MakeExtended6(uchar  ibCan, double  db);

bool    SupportedExtended6(uchar  ibCan);
bool    SupportedExtended6_CurrMon(uchar  ibCan, uchar  ibMon);
