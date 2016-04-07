/*------------------------------------------------------------------------------
AUTOMATIC32.H


------------------------------------------------------------------------------*/

void    Query32(uint  cwIn, uchar  cbOut);
serial  Input32(void);

bool    Automatic32(void);

bool    QueryOpen32_Full(uchar  bPercent);
time2   QueryTime32_Full(uchar  bPercent);

time2   ReadTimeCan32(void);
double2 ReadCntCurr32(void);
