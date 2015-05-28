/*------------------------------------------------------------------------------
RECALC_DEF.H


------------------------------------------------------------------------------*/

bool SaveDefDay(uchar  ibDayTo);
bool LoadDefDay(uchar  ibDayFrom);

bool SaveDefMon(uchar  ibMonTo);
bool LoadDefMon(uchar  ibMonFrom);

void    InitDef(void);
void    ResetDef(void);

void    NextDayDef(void);
void    NextMonDef(void);

void    MakeDefSpec(impulse  *mpimT, uchar  ibCan, time  ti);
