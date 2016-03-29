/*------------------------------------------------------------------------------
AUTOMATIC33.H


------------------------------------------------------------------------------*/

void    Query33(uint  cwIn, uchar  cbOut);
serial  Input33(void);

bool    Automatic33(void);

bool    QueryOpen33_Full(uchar  bPercent);
time2   QueryTime33_Full(uchar  bPercent);

time2   ReadTimeCan33(void);
double2 ReadCntCurr33(void);
