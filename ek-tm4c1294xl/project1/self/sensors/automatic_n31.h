/*------------------------------------------------------------------------------
AUTOMATIC_N31.H


------------------------------------------------------------------------------*/

extern  uchar               mpbCoder[4], ibCoder;



void    QueryN31(uint  cwIn, uchar  cbOut);
//bool    ChecksumW(void);
serial  InputN31(void);

//bool    AutomaticW(void);
//
//bool    QueryEngAbsW_Full(uchar  bPercent);
//bool    QueryEngMonW_Full(uchar  bTime, uchar  bPercent);
//bool    QueryEngDayW_Full(uchar  bTime, uchar  bPercent);

time2   ReadTimeCanN31(void);
//double2 ReadCntCurrW(void);
//double2 ReadCntMonCanW(uchar  ibMon);
//
//status  ReadCntMonCanTariffW(uchar  ibMon, uchar  ibTrf);
