/*------------------------------------------------------------------------------
EXTENDED_0.H


------------------------------------------------------------------------------*/

extern  cache const             chExt0Flag;
extern  cache const             chExt0Limit;
extern  cache const             chExt0Counter;



void    InitExtended0(void); 
void    ResetExtended0(bool  fFull);

bool    MakeExtended0(void);

void    OutExtended0(void);
