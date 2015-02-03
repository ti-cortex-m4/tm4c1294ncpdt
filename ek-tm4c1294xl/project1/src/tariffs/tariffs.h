/*------------------------------------------------------------------------------
TARIFFS.H

 Новый вариант задания тарифов
------------------------------------------------------------------------------*/

void    SetBoolEngMonthMode(uchar ibMonth, uchar ibMode, boolean boT);
boolean GetBoolEngMonthMode(uchar ibMonth, uchar ibMode);

void    SetBoolPowMonthMode(uchar ibMonth, uchar ibMode, boolean boT);
boolean GetBoolPowMonthMode(uchar ibMonth, uchar ibMode);

void    SetZoneEngMonthMode(uchar ibMonth, uchar ibMode, zones *pzoT);
zones   *PGetZoneEngMonthMode(uchar ibMonth, uchar ibMode);

void    SetZonePowMonthMode(uchar ibMonth, uchar ibMode, zones *pzoT);
zones   *PGetZonePowMonthMode(uchar ibMonth, uchar ibMode);

void    SetZonesEngMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zones *pzoT);
void    SetZonesPowMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zones *pzoT);

void    MakeTariff(uchar  mpTariff[48]);

void    SetTariffsDefault(void);
void    ResetTariffs(void);

void    MakeAllCurrTariffs(void);
void    MakeAllPrevTariffs(void);

void    ShowPeriodName(uchar  ibPeriod);
uchar   *PGetTariffName(uchar  ibTariff);
