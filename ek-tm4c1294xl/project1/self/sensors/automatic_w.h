/*------------------------------------------------------------------------------
AUTOMATIC_W.H


------------------------------------------------------------------------------*/

void    QueryW(uint  cwIn, uchar  cbHeaderMax);
serial  InputW(void);

bool    AutomaticW(void);

bool    QueryEngAbsW_Full(uchar  bPercent);
bool    QueryEngMonW_Full(uchar  bTime, uchar  bPercent);
bool    QueryEngDayW_Full(uchar  bTime, uchar  bPercent);

time2   ReadTimeCanW(void);
double2 ReadCntCurrW(void);
double2 ReadCntMonCanW(uchar  ibMon);
