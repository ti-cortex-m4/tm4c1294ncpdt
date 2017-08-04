/*------------------------------------------------------------------------------
TARIFFS!H

 Новый вариант задания тарифов
------------------------------------------------------------------------------*/

extern  cache const             chPublicTrf;
extern  cache const             chPublicTrfPrevMon;
extern  cache const             chOldTrfMode;

extern  cache const             chPeriodTrfPow;
extern  cache const             chPeriodTrfEng;

bool SaveZonesPow(uchar  ibMonth, uchar  ibMode);
bool LoadZonesPow(uchar  ibMonth, uchar  ibMode);

bool SaveZonesEng(uchar  ibMonth, uchar  ibMode);
bool LoadZonesEng(uchar  ibMonth, uchar  ibMode);

void    InitTariffs_Custom(void);
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

void    MakeAllCurrTariffs(void);
void    MakeAllPrevTariffs(time  ti);
