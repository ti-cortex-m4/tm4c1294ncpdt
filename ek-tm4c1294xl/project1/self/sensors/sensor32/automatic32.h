/*------------------------------------------------------------------------------
AUTOMATIC32.H


------------------------------------------------------------------------------*/

//extern  uchar               mpbCoder[4], ibCoder;
//
//
//
//void    InitPushCod(void);
//void    PushCharCod(uchar  bT);
//void    InitPopCod(void);
//uchar   PopCharCod(void);

void    Query32(uint  cwIn, uchar  cbOut);
serial  Input32(void);

//bool    Automatic31(void);
//
//time2   QueryTime31_Full(uchar  bPercent);
//double2 ReadTrans31_Full(void);

time2   ReadTimeCan32(void);
double2 ReadCntCurr32(void);
