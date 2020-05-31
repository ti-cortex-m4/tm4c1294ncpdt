/*------------------------------------------------------------------------------
device38.h


------------------------------------------------------------------------------*/

#include "include38.h"




void    PushAddress38(void);

void    QueryTime38(void);
time    LongToTime38(ulong  dw);
time    ReadTime38(void);

void    QueryEngAbs38(void);
uint64_t ReadEng38(uchar  ibInBuff);

void    QueryEngDay38(uchar  ibDayRel);
void    QueryEngMon38(uchar  ibMonRel);

