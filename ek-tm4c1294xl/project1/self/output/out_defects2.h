/*------------------------------------------------------------------------------
OUT_DEFECTS2.H


------------------------------------------------------------------------------*/

ulong   GetGrpCurrDef(impulse  *mpimT, uchar  ibGrp);
ulong   GetDayGrpMaxDef(uchar  ibGrp);
ulong   GetMonGrpMaxDef(uchar  ibGrp);

void    OutImpCanHou48Def(void);
void    OutPowGrpHou48Def(void);

void    OutDayCanDefAll(void);
void    OutMonCanDefAll(void);
void    OutDayGrpDefAll(void);
void    OutMonGrpDefAll(void);

void    OutDayCanDef(void);
void    OutMonCanDef(void);
void    OutDayGrpDef(void);
void    OutMonGrpDef(void);

