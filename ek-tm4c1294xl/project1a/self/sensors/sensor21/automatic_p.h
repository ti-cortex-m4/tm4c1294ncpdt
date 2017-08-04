/*------------------------------------------------------------------------------
AUTOMATIC_P.C


------------------------------------------------------------------------------*/

extern  uchar                   ibMonthP;




bool    OpenOpenP_Full(void);
bool    QueryOpenSerialP_Full(uchar  ibCan);

bool    QueryEnergyP_Full(uchar  bPart);

double2 ReadCntMonCanP(uchar  ibCan, uchar  ibMonth);
status  ReadCntMonCanTariffP(uchar  ibMonth, uchar  ibTariff);

ulong2  QuerySerialP_Full(uchar  ibCan);
