/*------------------------------------------------------------------------------
AUTOMATIC_W.H


------------------------------------------------------------------------------*/

void    QueryW(uint  cwIn, uchar  cbOut, uchar  cbHeaderMax);
serial  InputW(void);

//bool    QueryEngAbsW_Full(uchar  bPercent);
//bool    QueryEngMonW_Full(uchar  bMonth, uchar  bYear, uchar  bPercent);
//bool    QueryEngDayW_Full(uchar  bDay, uchar  bMonth, uchar  bYear, uchar  bPercent);

time2   ReadTimeCanW(void);
double2 ReadCntCurrW(void);
double2 ReadCntMonCanW(uchar  ibMonth);
