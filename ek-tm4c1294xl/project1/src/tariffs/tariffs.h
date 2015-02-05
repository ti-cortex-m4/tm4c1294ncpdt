/*------------------------------------------------------------------------------
TARIFFS.H

 Новый вариант задания тарифов
------------------------------------------------------------------------------*/

void    InitTariffs(void);
void    ResetTariffs(void);

void    SetZoneEngMonthMode(uchar ibMonth, uchar ibMode, zones *pzoT);
zones   *PGetZoneEngMonthMode(uchar ibMonth, uchar ibMode);

void    SetZonePowMonthMode(uchar ibMonth, uchar ibMode, zones *pzoT);
zones   *PGetZonePowMonthMode(uchar ibMonth, uchar ibMode);

void    SetZonesEngMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zones *pzoT);
void    SetZonesPowMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zones *pzoT);

void    MakeTariff(uchar  mpTariff[48]);

void    SetTariffsDefault(void);

void    MakeAllCurrTariffs(void);
void    MakeAllPrevTariffs(void);
