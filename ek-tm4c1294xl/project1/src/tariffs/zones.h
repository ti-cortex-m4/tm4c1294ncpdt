/*------------------------------------------------------------------------------
ZONES.H

 Подпрограммы управления суточными тарифными графиками
------------------------------------------------------------------------------*/

#include        "../main.h"



extern  br3ak const             brZero;

extern  zone const              zoDefaultPow;
extern  zone const              zoDefaultEng;

extern  file const              flZone;


void    InitZones(void);
void    ResetZones(void);

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

void    ShowZoneAltBreak(uchar  ibBreak);
void    ShowZoneKeyBreak(uchar  ibBreak);

boolean TrueZone(zone  *pzo);
