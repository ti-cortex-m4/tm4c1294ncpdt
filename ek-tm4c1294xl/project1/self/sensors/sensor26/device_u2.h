/*------------------------------------------------------------------------------
DEVICE_U2.H


------------------------------------------------------------------------------*/

void    QueryEnergyDayDatesU(void);
void    QueryEnergyMonDatesU(void);

void    ReadEnergyDayDatesU(void);
void    ReadEnergyMonDatesU(void);

uchar   IsDayAddedU(date  dt);
uchar   IsMonAddedU(date  dt);

void    ReadEnergyTariffU(uchar  ibLine, uchar  ibTrf);
