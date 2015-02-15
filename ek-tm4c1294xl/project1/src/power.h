/*------------------------------------------------------------------------------
POWER.H


------------------------------------------------------------------------------*/

void    SetGrpMaxPow(power  *mppoT, uchar  ibGroup, uchar  ibTariff);

real    *PGetGrpMaxPowReal(power  *mppoT, uchar  ibGroup, uchar  ibTariff);
time    *PGetGrpMaxPowTime(power  *mppoT, uchar  ibGroup, uchar  ibTariff);

uchar   GetGrpMaxPowIndex(power  *mppoT, uchar  ibGroup);

//void    MakeMaxPowAlt(power  *mppoT);
void    MakeMaxPowSpec(power  *mppoT);

void    MakeAllMaxPowNow(void);


