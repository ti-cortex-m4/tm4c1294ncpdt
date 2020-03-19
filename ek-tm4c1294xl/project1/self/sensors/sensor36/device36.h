/*------------------------------------------------------------------------------
DEVICE36.H


------------------------------------------------------------------------------*/

void    Query36_DISC(void);
void    Query36_SNRM(void);
void    Query36_Open2(uchar  bNS, uchar  bNR);
void    Query36_RR(uchar  bNR);
void    Query36_GetTime(uchar  bNS, uchar  bNR);
//void    Query36_Open5(uchar  bNR);

void    QueryTime36(void);
time    ReadTime36(void);
