/*------------------------------------------------------------------------------
PROCEDURE31.H


------------------------------------------------------------------------------*/

extern  time                    mtiProcedureDig[bCANALS];



void    ClearProcedure31(void);
bool    IsCleanProcedure31(uchar  ibDig);
void    AddProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  db);
void    SubProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  dbPulse);
uchar   GetTimeIdx(time  ti);
