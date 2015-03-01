/*------------------------------------------------------------------------------
ENERGY2.H


------------------------------------------------------------------------------*/

boolean SaveImpMnt(bool fCurr, uchar  ibMntTo, uchar  ibMntFrom);
boolean LoadImpMnt(uchar  ibMntFrom);

boolean SaveImpHou(bool fCurr, uint  iwHouTo, uint  iwHouFrom);
boolean LoadImpHou(uint  iwHouFrom);
boolean LoadImpHouFree(uint  iwHouFrom);

boolean SaveImpDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom);
boolean LoadImpDay(uchar  ibDayFrom);

boolean SaveImpMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom);
boolean LoadImpMon(uchar  ibMonFrom);

boolean SavePowDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom);
boolean LoadPowDay(uchar  ibDayFrom);

boolean SavePowMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom);
boolean LoadPowMon(uchar  ibMonFrom);

boolean SaveCntMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom);
boolean LoadCntMon(uchar  ibMonFrom);
