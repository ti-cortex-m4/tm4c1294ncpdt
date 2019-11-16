/*------------------------------------------------------------------------------
AUTOMATIC35.H


------------------------------------------------------------------------------*/

bool    Automatic35(void);

//bool    QueryConfigS_Full(uchar  bPercent);
//time2   QueryTimeS_Full(uchar  bPercent);

time2   ReadTimeCan35(void);
double2 ReadCntCurr35(void);
double2 ReadCntMonCan35(uchar  ibMon);
