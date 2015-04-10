/*------------------------------------------------------------------------------
EXTENDED_4T.H


------------------------------------------------------------------------------*/

#include        "../memory/mem_extended_4t.h"



extern  file const              flExt4TFlag;
extern  file const              flExt4TMonths;



void    InitExtended4T(void); 
void    ResetExtended4T(void);

void    ResetExtended4T1(void); 
void    ResetExtended4T2(uchar  ibMon, uchar  ibCan);

void    NextMonExtended4T(void); 

void    MakeExtended4T(void);

void    OutExtended40T(void);
void    OutExtended401T(void);
