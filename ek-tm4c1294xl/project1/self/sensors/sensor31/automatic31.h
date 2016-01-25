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

time2   QueryTimeN31_Full(uchar  bPercent);
double2 ReadTransN31_Full(void);

time2   ReadTimeCan31(void);
double2 ReadCntCurr31(void);
