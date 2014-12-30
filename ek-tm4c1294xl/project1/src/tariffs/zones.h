/*------------------------------------------------------------------------------
ZONES.H

 Ïîäïðîãðàììû óïðàâëåíèÿ ñóòî÷íûìè òàðèôíûìè ãðàôèêàìè
------------------------------------------------------------------------------*/

#include        "../main.h"



extern  breaks                  brZero;



uchar   GetZoneAltSize(void);
void    SetZoneAltSize(uchar  bSize);

void    GetZoneAltBreak(uchar  ibBreak);
void    SetZoneAltBreak(uchar  ibBreak);

uchar   GetZoneKeySize(void);
void    SetZoneKeySize(uchar  bSize);

void    GetZoneKeyBreak(uchar  ibBreak);
void    SetZoneKeyBreak(uchar  ibBreak);

uchar   GetBreakAltIndex(uchar  ibBreak);
uchar   GetBreakKeyIndex(uchar  ibBreak);

void    ResetZones(void);

void    ShowZoneAltBreak(uchar  ibBreak);
void    ShowZoneKeyBreak(uchar  ibBreak);

bool    TrueZone(void);

void    SetKeyZonePow(void);
void    SetKeyZoneEng(void);
