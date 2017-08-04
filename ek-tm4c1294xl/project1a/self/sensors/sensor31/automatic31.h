/*------------------------------------------------------------------------------
AUTOMATIC31.H


------------------------------------------------------------------------------*/

extern  uchar               mpbCoder[4], ibCoder;



void    InitPushCod(void);
void    PushCharCod(uchar  bT);
void    InitPopCod(void);
uchar   PopCharCod(void);

void    Query31(uint  cwIn, uchar  cbOut);
serial  Input31(void);

bool    Automatic31(void);

bool    QueryOpen31_Full(uchar  bPercent);
time2   QueryTime31_Full(uchar  bPercent);
double2 ReadTrans31_Full(void);

time2   ReadTimeCan31(void);
double2 ReadCntCurr31(void);
