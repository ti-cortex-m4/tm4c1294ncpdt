/*------------------------------------------------------------------------------
AUTOMATIC_P.C


------------------------------------------------------------------------------*/

extern  uchar                   ibMonthP;




bool    OpenOpenP_Full(void);
bool    QueryOpenSerialP_Full(uchar  c);

bool    QueryEnergyP_Full(uchar  bPart);

double2 ReadCntMonCanP(uchar  ibMonth);
status  ReadCntMonCanTariffP(uchar  ibMonth, uchar  ibTariff);

ulong2  QuerySerialP_Full(uchar  c);
