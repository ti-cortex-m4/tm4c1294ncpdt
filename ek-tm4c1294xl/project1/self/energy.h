/*------------------------------------------------------------------------------
ENERGY!H


------------------------------------------------------------------------------*/

ulong   *PGetCanImp(impulse  *mpimT, uchar  ibCan, uchar  ibTariff);
ulong   *PGetCanImpAll(impulse  *mpimT, uchar  ibCan);

float   GetGrpMntInt2Real(uint  *mpwT, uchar  ibGrp, uchar  bMultiplier);
float   GetCanMntInt2Real(uint  *mpwT, uchar  ibCan, uchar  bMultiplier);

float   GetGrpHouInt2Real(uint  *mpwT, uchar  ibGrp, uchar  bMultiplier);
float   GetCanHouInt2Real(uint  *mpwT, uchar  ibCan, uchar  bMultiplier);

float   GetGrpImp2FloatEng(impulse  *mpimT, uchar  ibGrp, uchar  bMask);
double  GetGrpImp2DoubleEng(impulse  *mpimT, uchar  ibGrp, uchar  bMask);
float   GetCanImp2FloatEng(impulse  *mpimT, uchar  ibCan, uchar  bMask);
double  GetCanImp2DoubleEng(impulse  *mpimT, uchar  ibCan, uchar  bMask);

void    MakeImpSpec(impulse  *mpimT, uchar  ibCan, time  ti);
void    MakeImpSpec_Winter(impulse  *mpimT, uchar  ibCan, time  ti);

void    AddCanImpEng(impulse  *mpimT, uchar  ibCanal, uchar  wImp);

void    MakeCntMonCan(void);
double  GetCntCurrImp(uchar  ibCan);

void    MakeImpulse(void);
void    MakeImpulseSpec(void);
