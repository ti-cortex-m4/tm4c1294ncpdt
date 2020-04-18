/*------------------------------------------------------------------------------
AUTOMATIC_S.C


------------------------------------------------------------------------------*/

void    QueryS(uchar  cbIn, uchar  cbOut);
serial  InputS(void);

bool    QueryConfigS_Full(uchar  bPercent);
time2   QueryTimeS_Full(uchar  bPercent);

time2   ReadTimeCanS(void);
double2 ReadCntCurrS(void);
double2 ReadCntMonCanS(uchar  ibMon);
