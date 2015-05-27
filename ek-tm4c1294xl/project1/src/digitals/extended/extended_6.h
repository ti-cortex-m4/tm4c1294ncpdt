/*------------------------------------------------------------------------------
EXTENDED_6.H


------------------------------------------------------------------------------*/

#include "../../memory/mem_extended_6.h"



extern  file const              flExt6Flag;


boolean LoadCntMonCan6(uchar  ibMonFrom);

void    InitExtended6(void);
void    ResetExtended6(void);

void    NextDayExtended6(void);
void    NextMonExtended6(void);
void    CloseExtended6(void);

void    MakeExtended6(uchar  ibCan, real  re);

bool    CheckDirectCnt1(uchar  ibCan);
bool    CheckDirectCnt2(uchar  ibCan, uchar  ibMon);
