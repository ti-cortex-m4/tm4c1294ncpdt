/*------------------------------------------------------------------------------
ENERGY.H


------------------------------------------------------------------------------*/

uint    GetCanInt(uint  *mpwT, uchar  ibCan);
void    SetCanInt(uint  *mpwT, uchar  ibCan, uint  wT);

ulong   GetCanLong(ulong  *mpdwT, uchar  ibCan);
void    SetCanLong(ulong  *mpdwT, uchar  ibCan, ulong  *pdwT);

real    GetCanReal(real  *mpreT, uchar  ibCan);
void    SetCanReal(real  *mpreT, uchar  ibCan, real  *preT);

ulong   *PGetCanImp(impulse  *mpimT, uchar  ibCanal, uchar  ibTariff);
ulong   *PGetCanImpAll(impulse  *mpimT, uchar  ibCanal);

real    *PGetGrpHouInt2Real(uint  *mpwT, uchar  ibGroup, uchar  bMul);

void    MakeCounters(void);
real    *PGetCounterOld(uchar  ibCanal);

void    MakeImpulse(void);
void    MakeImpulseSpec(time  *ptiOldDay, time  *ptiOldMon);
