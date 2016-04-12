/*------------------------------------------------------------------------------
PROCEDURE31.H


------------------------------------------------------------------------------*/

extern  time                    mtiProcedure31Dig[bCANALS];



void    MonitorBuff(uchar  ibDig, uchar  ibCan);

void    InitProcedure31(void);
void    ClearProcedure31(bool  fClearValue, bool  fClearTime);

uchar   GetProcedure31Idx(time  ti);

void    AddProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  db);
void    SubProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  dbPulse);
