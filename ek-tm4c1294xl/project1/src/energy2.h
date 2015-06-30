/*------------------------------------------------------------------------------
ENERGY2.H


------------------------------------------------------------------------------*/

bool SaveImpHou(bool fCurr, uint  iwHouTo, uint  iwHouFrom);
bool LoadImpHou(uint  iwHouFrom);
bool LoadImpHouFree(uint  iwHouFrom);

bool SaveImpDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom);
bool LoadImpDay(uchar  ibDayFrom);

bool SaveImpMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom);
bool LoadImpMon(uchar  ibMonFrom);

bool SavePowDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom);
bool LoadPowDay(uchar  ibDayFrom);

bool SavePowMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom);
bool LoadPowMon(uchar  ibMonFrom);

bool SaveCntMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom);
bool LoadCntMon(uchar  ibMonFrom);
