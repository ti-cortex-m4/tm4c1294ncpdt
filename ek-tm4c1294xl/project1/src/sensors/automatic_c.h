/*------------------------------------------------------------------------------
AUTOMATIC_C.H


------------------------------------------------------------------------------*/

bool    QueryEnergyDayC_Full2(uchar  bTime, uchar  bPercent);
bool    QueryEnergyMonC_Full2(uchar  bTime, uchar  bPercent);
bool    QueryEnergyAbsC_Full2(uchar  bPercent);
bool    QueryTimeC_Full(void);
bool    QueryCounterMonTariffC_Full(uchar  ibMonth, uchar  bTariff);

status4 ReadCntMonCanTariffC(uchar  ibMonth, uchar  ibTariff);
