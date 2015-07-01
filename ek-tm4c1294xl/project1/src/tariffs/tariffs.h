/*------------------------------------------------------------------------------
TARIFFS.H

 Новый вариант задания тарифов
------------------------------------------------------------------------------*/

extern  file const              flPublicTariffs;
extern  file const              flPublicTariffsPrevMon;
extern  file const              flTariffsMode;

extern  file const              flPeriodTariffPow;
extern  file const              flPeriodTariffEng;

bool SaveZonesPow(uchar  ibMonth, uchar  ibMode);
bool LoadZonesPow(uchar  ibMonth, uchar  ibMode);

bool SaveZonesEng(uchar  ibMonth, uchar  ibMode);
bool LoadZonesEng(uchar  ibMonth, uchar  ibMode);

void    InitTariffs(void);
void    ResetTariffs(void);

void    NextMonTariffs(void);

void    SetZoneEngMonthMode(uchar ibMonth, uchar ibMode, zone *pzo);
zone   *PGetZoneEngMonthMode(uchar ibMonth, uchar ibMode);

void    SetZonePowMonthMode(uchar ibMonth, uchar ibMode, zone *pzo);
zone   *PGetZonePowMonthMode(uchar ibMonth, uchar ibMode);

void    SetZonesEngMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zone *pzo);
void    SetZonesPowMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zone *pzo);

void    MakeTariff(uchar  mpTariff[48]);

void    DefaultTariffs(void);

void    MakeAllCurrTariffs(time  ti);
void    MakeAllPrevTariffs(time  ti);
