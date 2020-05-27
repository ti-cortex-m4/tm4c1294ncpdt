/*------------------------------------------------------------------------------
device38.h


------------------------------------------------------------------------------*/

void    QueryTime38(void);
time    ReadTime38(void);

void    QueryEngAbs38(uchar  ibLine);
uint64_t ReadEngAbs38(uchar  ibInBuff);

void    QueryEngDay38(uchar  ibDayRel, uchar  ibLine);
void    QueryEngMon38(uchar  ibMonRel, uchar  ibLine);
uint64_t ReadEngStatus38(uchar  ibInBuff);

