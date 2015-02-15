/*------------------------------------------------------------------------------
ENERGY.H


------------------------------------------------------------------------------*/

uint    *PGetCanInt(uint  *mpwT, uchar  ibCanal);
void    SetCanInt(uint  *mpwT, uchar  ibCanal, uint  wT);

ulong   *PGetCanLong(ulong  *mpdwT, uchar  ibCanal);
void    SetCanLong(ulong  *mpdwT, uchar  ibCanal);

real    *PGetCanReal(real  *mpreT, uchar  ibCanal);
void    SetCanReal(real  *mpreT, uchar  ibCanal);

ulong   *PGetCanImp(impulse  *mpimT, uchar  ibCanal, uchar  ibTariff);
ulong   *PGetCanImpAll(impulse  *mpimT, uchar  ibCanal);

real    *PGetGrpHouInt2Real(uint  *mpwT, uchar  ibGroup, uchar  bMul);

void    MakeCounters(void);
real    *PGetCounterOld(uchar  ibCanal);

void    MakeImpulse(void);
void    MakeImpulseSpec(time  *ptiOldDay, time  *ptiOldMon);
