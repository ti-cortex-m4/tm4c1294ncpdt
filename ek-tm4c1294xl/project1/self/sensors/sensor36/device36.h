/*------------------------------------------------------------------------------
DEVICE36.H


------------------------------------------------------------------------------*/

void    QueryTime36(void);
time    ReadTime36(void);

void    QueryDate36(void);
time    ReadDate36(time  ti);

void    QueryEngAbs36(uchar  ibLine);
void    QueryEngDay36(uchar  ibLine, time  ti);
void    QueryEngMon36(uchar  ibLine, time  ti);
void    ReadEng36(uchar  ibLine);
void    ReadEngTariff36(uchar  ibLine, uchar  ibTrf);

void    QueryClose36(void);
