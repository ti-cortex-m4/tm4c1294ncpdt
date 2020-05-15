/*------------------------------------------------------------------------------
DEVICE36.H


------------------------------------------------------------------------------*/

#include "include38.h"



void    Query38_DISC(void);
void    Query38_SNRM(void);
void    Query38_Open2(uchar  bNS, uchar  bNR);
void    Query38_RR(uchar  bNR);

void    QueryTime38(uchar  bNS, uchar  bNR, uchar  bInvokeId);
time    ReadTime36(void);

void    QueryEngAbs36(uchar  bNS, uchar  bNR, uchar  bInvokeId, uchar  ibLine);
uint64_t ReadEngAbs36(void);

void    QueryEngMon36(uchar  bNS, uchar  bNR, uchar  bInvokeId, uchar  bMonth, uchar  bYear);
uint64_t ReadEngMon36(void);
