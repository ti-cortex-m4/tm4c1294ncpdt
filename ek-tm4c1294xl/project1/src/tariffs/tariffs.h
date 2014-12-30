/*------------------------------------------------------------------------------
TARIFFS.H

 Ïîäïðîãðàììû óïðàâëåíèÿ òàðèôàìè
------------------------------------------------------------------------------*/

#include        "../main.h"



extern  uchar                   ibMonth,ibMode;



void    SetBoolEngMonthMode(void);
boolean GetBoolEngMonthMode(void);

void    SetBoolPowMonthMode(void);
boolean GetBoolPowMonthMode(void);

void    SetZoneEngMonthMode(void);
zones   *PGetZoneEngMonthMode(void);

void    SetZonePowMonthMode(void);
zones   *PGetZonePowMonthMode(void);

void    SetZonesEngMonthsMode(uchar  ibBeg, uchar  ibEnd);
void    SetZonesPowMonthsMode(uchar  ibBeg, uchar  ibEnd);

void    MakeTariff(uchar  mpTariff[48]);

void    SetTariffsDefault(void);
void    ResetTariffs(void);

void    MakeAllCurrTariffs(void);
void    MakeAllPrevTariffs(void);

void    ShowPeriodName(uchar  ibPeriod);
uchar   *PGetTariffName(uchar  ibTariff);
