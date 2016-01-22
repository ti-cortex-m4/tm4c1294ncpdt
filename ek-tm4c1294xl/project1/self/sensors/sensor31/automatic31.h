/*------------------------------------------------------------------------------
AUTOMATIC31.H


------------------------------------------------------------------------------*/

extern  uchar               mpbCoder[4], ibCoder;



void    InitPushCod(void);
void    PushCharCod(uchar  bT);
void    InitPopCod(void);
uchar   PopCharCod(void);

void    QueryN31(uint  cwIn, uchar  cbOut);
//bool    ChecksumW(void);
serial  InputN31(void);

bool    AutomaticN31(void);

//bool    QueryEngAbsW_Full(uchar  bPercent);
//bool    QueryEngMonW_Full(uchar  bTime, uchar  bPercent);
//bool    QueryEngDayW_Full(uchar  bTime, uchar  bPercent);

time2   ReadTimeCanN31(void);
double2 ReadCntCurrN31(void);
//double2 ReadCntMonCanW(uchar  ibMon);
//
//status  ReadCntMonCanTariffW(uchar  ibMon, uchar  ibTrf);
