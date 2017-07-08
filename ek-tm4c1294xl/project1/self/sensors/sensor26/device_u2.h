/*------------------------------------------------------------------------------
DEVICE_U2.H


------------------------------------------------------------------------------*/

void    QueryEnergyDayDatesU(void);
void    QueryEnergyMonDatesU(void);

void    QueryEnergyDayU(uchar  ibLine, uchar  bDay);
void    QueryEnergyMonU(uchar  ibLine, uchar  bMon);

void    ReadEnergyDayDatesU(void);
void    ReadEnergyMonDatesU(void);

uchar   IsDayAddedU(date  dt);
uchar   IsMonAddedU(date  dt);

void    ReadEnergyTariffU(uchar  ibLine, uchar  ibTrf);
