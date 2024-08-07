/*------------------------------------------------------------------------------
AUTOMATIC_V.H


------------------------------------------------------------------------------*/

void    QueryV(uchar  cbIn, uchar  cbOut);
serial  InputV(void);

bool    QueryEngAbsV_Full(uchar  bPercent);
bool    QueryEngMonV_Full(uchar  bMonth, uchar  bYear, uchar  bPercent);
bool    QueryEngDayV_Full(uchar  bDay, uchar  bMonth, uchar  bYear, uchar  bPercent);

time2   ReadTimeCanV(void);
double2 ReadCntCurrV(void);
double2 ReadCntMonCanV(uchar  ibMon);
