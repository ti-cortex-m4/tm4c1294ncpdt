/*------------------------------------------------------------------------------
device38.h


------------------------------------------------------------------------------*/

#include "include38.h"



void    PushAddress38(void);

void    QueryEngAbs38(void);
void    QueryEngDay38(uchar  ibDayRel);
void    QueryEngMon38(uchar  ibMonRel);

void    QueryNumber38(void);
ulong   ReadNumber38(void);

bool    GoodStatus38(uchar  bStatus);
