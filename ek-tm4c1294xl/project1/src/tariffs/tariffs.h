/*------------------------------------------------------------------------------
TARIFFS.H

 Новый вариант задания тарифов
------------------------------------------------------------------------------*/

extern  file const              flPublicTariffs;
extern  file const              flTariffsMode;

extern  file const              flPeriodTariffPow;
extern  file const              flPeriodTariffEng;

boolean SaveZonesPow(uchar  ibMonth, uchar  ibMode);
boolean LoadZonesPow(uchar  ibMonth, uchar  ibMode);

boolean SaveZonesEng(uchar  ibMonth, uchar  ibMode);
boolean LoadZonesEng(uchar  ibMonth, uchar  ibMode);

void    InitTariffs(void);
void    ResetTariffs(void);

void    SetZoneEngMonthMode(uchar ibMonth, uchar ibMode, zones *pzoT);
zones   *PGetZoneEngMonthMode(uchar ibMonth, uchar ibMode);

void    SetZonePowMonthMode(uchar ibMonth, uchar ibMode, zones *pzoT);
zones   *PGetZonePowMonthMode(uchar ibMonth, uchar ibMode);

void    SetZonesEngMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zones *pzoT);
void    SetZonesPowMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zones *pzoT);

void    MakeTariff(uchar  mpTariff[48]);

void    DefaultTariffs(void);

void    MakeAllCurrTariffs(void);
void    MakeAllPrevTariffs(void);
