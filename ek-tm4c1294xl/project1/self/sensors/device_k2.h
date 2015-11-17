/*------------------------------------------------------------------------------
DEVICE_K2.H


------------------------------------------------------------------------------*/

void    QueryEnergyDayDatesK(void);
void    QueryEnergyMonDatesK(void);

void    QueryEnergyDayK(uchar  ibLine, uchar  bDay);
void    QueryEnergyMonK(uchar  ibLine, uchar  bMon);

void    ReadEnergyDayDatesK(void);
void    ReadEnergyMonDatesK(void);

uchar   IsDayAddedK(void);
uchar   IsMonAddedK(void);

void    ReadEnergyTariffK(uchar  ibLine, ibTariff);
