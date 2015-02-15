/*------------------------------------------------------------------------------
POWER.H


------------------------------------------------------------------------------*/

void    SetGrpMaxPow(power  *mppoT, uchar  ibGrp, uchar  ibTar, maximum  *pma);
real    GetGrpMaxPowReal(power  *mppoT, uchar  ibGrp, uchar  ibTar);
time    GetGrpMaxPowTime(power  *mppoT, uchar  ibGrp, uchar  ibTar);

uchar   GetGrpMaxPowIndex(power  *mppoT, uchar  ibGroup);

void    MakeMaxPow(power  *mppoT);
void    MakeMaxPowSpec(power  *mppoT, uchar  ibGrp, time  *ptiT);
void    MakeMaxPowAll(void);
