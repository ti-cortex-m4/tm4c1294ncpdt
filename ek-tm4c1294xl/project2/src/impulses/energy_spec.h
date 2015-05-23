/*------------------------------------------------------------------------------
ENERGY_SPEC.H


------------------------------------------------------------------------------*/



bool      SaveImpHouSpec(bool  fCurr, uint  iwHouTo);
bool      LoadImpHouSpec(uint  iwHouFrom, bool  fFree);

bool      SaveImpDaySpec(bool  fCurr, uchar  ibDayTo);
bool      LoadImpDaySpec(uchar  ibDayFrom);

bool      SaveImpMonSpec(bool  fCurr, uchar  ibMonTo);
bool      LoadImpMonSpec(uchar  ibMonFrom);

bool      SavePowDaySpec(bool  fCurr, uchar  ibDayTo);
bool     LoadPowDaySpec(uchar  ibDayFrom);

bool      SavePowMonSpec(bool  fCurr, uchar  ibMonTo);
bool      LoadPowMonSpec(uchar  ibMonFrom);
