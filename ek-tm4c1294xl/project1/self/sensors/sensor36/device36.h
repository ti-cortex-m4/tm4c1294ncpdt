/*------------------------------------------------------------------------------
DEVICE36.H


------------------------------------------------------------------------------*/

void    Query36_DISC(void);
void    Query36_SNRM(void);
void    Query36_Open2(uchar  bNS, uchar  bNR);
void    Query36_RR(uchar  bNR);

void    QueryTime36(uchar  bNS, uchar  bNR, uchar  bInvokeId);
time    ReadTime36(void);

void    QueryEngAbs36(uchar  bNS, uchar  bNR, uchar  bInvokeId, uchar  ibLine);
uint64_t ReadEngAbs36(void);

void    QueryEngMon36(uchar  bNS, uchar  bNR, uchar  bInvokeId);
uint64_t ReadEngMon36(void);
