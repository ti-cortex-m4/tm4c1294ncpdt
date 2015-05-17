/*------------------------------------------------------------------------------
EXTENDED_4T.H


------------------------------------------------------------------------------*/

#include "../memory/mem_extended_4t.h"



extern  file const              flExt4TFlag;
extern  file const              flExt4TMonths;



boolean LoadExt4TValues(uchar  ibMon);

void    InitExtended4T(void); 
void    ResetExtended4T(void);

void    ResetExtended4T1(void); 
void    ResetExtended4T2(uchar  ibCanMin, uchar  ibCanMax, uchar  ibMonMin, uchar  ibMonMax);

void    NextMonExtended4T(void); 

void    MakeExtended4T(void);

void    OutExtended4T(void);
