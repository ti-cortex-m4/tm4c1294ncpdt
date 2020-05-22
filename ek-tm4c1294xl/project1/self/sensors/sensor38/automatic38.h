/*------------------------------------------------------------------------------
AUTOMATIC36.H


------------------------------------------------------------------------------*/

bool    Automatic36(void);

time2   ReadTimeCan36(void);
time2   ReadTimeCan36_Short(void);

double2 ReadCntCurr36(uchar  bMaxLines);
double2 ReadCntMonCan36(uchar  ibMon, uchar  bMaxLines);
