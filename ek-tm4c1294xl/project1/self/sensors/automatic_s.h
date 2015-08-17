/*------------------------------------------------------------------------------
AUTOMATIC_S.C


------------------------------------------------------------------------------*/

void    QueryS_IO(uchar  cbIn, uchar  cbOut);
serial  InputS(void);

bool    QueryConfigS_Full(uchar  bPercent);

time2   ReadTimeCanS(void);
double2 ReadCntCurrS(void);
double2 ReadCntMonCanS(uchar  ibMonth);
