/*------------------------------------------------------------------------------
AUTOMATIC31.H


------------------------------------------------------------------------------*/

extern  uchar               mpbCoder[4], ibCoder;



void    InitPushCod(void);
void    PushCharCod(uchar  bT);
void    InitPopCod(void);
uchar   PopCharCod(void);

void    QueryN31(uint  cwIn, uchar  cbOut);
serial  InputN31(void);

bool    AutomaticN31(void);

time2   QueryTimeN31_Full(uchar  bPercent);
double2 ReadTransN31_Full(void);

time2   ReadTimeCanN31(void);
double2 ReadCntCurrN31(void);
