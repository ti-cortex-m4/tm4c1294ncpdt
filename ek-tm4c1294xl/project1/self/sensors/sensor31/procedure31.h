/*------------------------------------------------------------------------------
PROCEDURE31.H


------------------------------------------------------------------------------*/

extern  time                    mtiProcedure31Dig[bCANALS];



void    StartProcedure31(void);

uchar   GetProcedure31Idx(time  ti);

void    AddProcedure31(time  ti, uchar  ibDig, uchar  i, double  db);
void    SubProcedure31(time  ti, uchar  ibDig, uchar  i);

void    ClearChannels31(void);
bool    MakeSpecial31(time  ti, uchar  bMaxLine);
