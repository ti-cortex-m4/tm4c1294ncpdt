/*------------------------------------------------------------------------------
EXTENDED_6.H


------------------------------------------------------------------------------*/

#include        "../memory/mem_extended_6.h"



extern  file const              flExt6Flag;



void    InitExtended6(void);
void    ResetExtended6(void);

void    NextDayExtended6(void);
void    NextMonExtended6(void);
void    CloseExtended6(void);

void    MakeExtended6(uchar  ibCan, real  re);

//void    OutExtended6(void);
//void    ShowCntMonCan6(uchar  ibCan, uchar  ibMon);

//bool    CheckDirectCnt1(uchar  ibCan);
//bool    CheckDirectCnt2(uchar  ibCan, uchar  ibMon);
//void    ShowDirectCnt(uchar  ibCan);
//void    LoadDirectCntReal(uchar  ibCan);
//void    LoadDirectCntTime(uchar  ibCan);
