/*------------------------------------------------------------------------------
MAX_POWER.H


------------------------------------------------------------------------------*/

void    SetGrpMaxPow(power  *mppoT, uchar  ibGrp, uchar  ibTar, value  *pva);
real    GetGrpMaxPowReal(power  *mppoT, uchar  ibGrp, uchar  ibTar);
time    GetGrpMaxPowTime(power  *mppoT, uchar  ibGrp, uchar  ibTar);

uchar   GetGrpMaxPowIndex(power  *mppoT, uchar  ibGrp);

void    MakeMaxPow(power  *mppoT);
void    MakeMaxPowSpec(power  *mppoT, uchar  ibGrp, time  ti);
void    MakeMaxPowAll(void);
