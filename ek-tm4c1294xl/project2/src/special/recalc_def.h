/*------------------------------------------------------------------------------
RECALC_DEF.H


------------------------------------------------------------------------------*/

boolean SaveDefDay(uchar  ibDayTo);
boolean LoadDefDay(uchar  ibDayFrom);

boolean SaveDefMon(uchar  ibMonTo);
boolean LoadDefMon(uchar  ibMonFrom);

void    InitDef(void);
void    ResetDef(void);

void    NextDayDef(void);
void    NextMonDef(void);

void    MakeDefSpec(impulse  *mpimT, uchar  ibCan, time  ti);
