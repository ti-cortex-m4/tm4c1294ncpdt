/*------------------------------------------------------------------------------
EXTENDED_4T,H


------------------------------------------------------------------------------*/

#include "../../memory/mem_extended_4t.h"



extern  cache const             chExt4TFlag;
extern  cache const             chExt4TMonths;



bool LoadExt4TValues(uchar  ibMon);

void    InitExtended4T(void); 
void    ResetExtended4T(bool  fFull);

void    ResetExtended4T_Full(void); 
void    ResetExtended4T_Custom(uchar  ibCanMin, uchar  ibCanMax, uchar  ibMonMin, uchar  ibMonMax);

void    NextMonExtended4T(void); 

void    MakeExtended4T(void);
