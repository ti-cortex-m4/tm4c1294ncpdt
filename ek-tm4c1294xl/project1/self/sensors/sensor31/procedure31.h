/*------------------------------------------------------------------------------
PROCEDURE31.H


------------------------------------------------------------------------------*/

extern  time                    mtiProcedure31Dig[bCANALS];



void    ClearProcedure31(void);

bool    IsCleanProcedure31(uchar  ibDig);
uchar   GetProcedure31Idx(time  ti);

void    AddProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  db);
void    SubProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  dbPulse);
