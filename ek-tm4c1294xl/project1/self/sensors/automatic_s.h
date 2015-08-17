/*------------------------------------------------------------------------------
AUTOMATIC_S.C


------------------------------------------------------------------------------*/

void    QueryS_IO(uchar  cbIn, uchar  cbOut);
serial  InputS(void);

bit     QueryConfigS_Full(uchar  bPercent);

bit     ReadTimeDateS(void);
bit     ReadSensorS(void);
bit     ReadCntMonCanS(uchar  ibMonth);
