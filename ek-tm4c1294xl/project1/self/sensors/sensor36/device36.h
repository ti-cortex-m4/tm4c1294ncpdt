/*------------------------------------------------------------------------------
DEVICE36.H


------------------------------------------------------------------------------*/

void    QueryClose36(void);

void    QueryOpen36(void);
void    ReadOpen36(void);

void    QueryOption36(void);

void    QueryTime36(void);
time    ReadTime36(void);

void    QueryDate36(void);
time    ReadDate36(time  ti);

void    QueryEngAbs36(uchar  ibLine);
void    QueryEngDay36(uchar  ibLine, time  ti);
void    QueryEngMon36(uchar  ibLine, time  ti);

void    ReadEng36(uchar  ibLine);
void    ReadEng36_SkipLine(uchar  ibLine);
void    ReadEngTariff36(uchar  ibLine, uchar  ibTrf);

void    QueryEngCurrent36(uchar  ibLine);
void    ReadCurrent36(uchar  bMaxLine);
