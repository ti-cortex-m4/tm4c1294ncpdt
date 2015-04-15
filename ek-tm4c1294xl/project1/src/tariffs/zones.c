/*------------------------------------------------------------------------------
ZONES.C

 Подпрограммы управления суточными тарифными графиками
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../keyboard/keyboard.h"
#include        "../display/display.h"
#include        "../flash/files.h"



//                                       0123456789ABCDEF  
static char const       szNoZones[]   = " зоны не заданы ";


br3ak const             brZero = { 0, 0, 0 };

zone const              zoDefaultPow = {
		bSize: 6,
		mpbrBreaks: {
		 	{6,  0,  0},
		 	{8,  0,  1},
		 	{11, 0,  2},
		  {17, 0,  1},
		  {20, 0,  3},
		  {23, 0,  1}
		}
};

zone const              zoDefaultEng = {
		bSize: 5,
		mpbrBreaks: {
			{6,  0,  0},
			{8,  0,  1},
			{11, 0,  2},
			{23, 0,  1},
			{24, 0,  0},
			{0,  0,  0}
		}
};

zone const              zoDefault = {
		bSize: 6,
		mpbrBreaks: {
			{6,  0,  0},
			{8,  0,  1},
			{10, 0,  2},
			{18, 0,  1},
			{20, 0,  3},
			{21, 30, 1}
		}
};

file const              flZone = {DAY_ZONE, &zoKey, sizeof(zone)};



void    InitZones(void)
{
  LoadFile(&flZone);
}



void    ResetZones(void)
{
	zoKey = zoDefault;
  SaveFile(&flZone);
}



uchar   GetZoneAltSize(void) {
  return( zoAlt.bSize );
}


void    SetZoneAltSize(uchar  bSize) {
  zoAlt.bSize = bSize;
}



void    GetZoneAltBreak(uchar  ibBreak) {
  brAlt = zoAlt.mpbrBreaks[ibBreak];
}


void    SetZoneAltBreak(uchar  ibBreak) {
  zoAlt.mpbrBreaks[ibBreak] = brAlt;
}



uchar   GetZoneKeySize(void) {
  return( zoKey.bSize );
}


void    SetZoneKeySize(uchar  bSize) {
  zoKey.bSize = bSize;
}



void    GetZoneKeyBreak(uchar  ibBreak) {
  brKey = zoKey.mpbrBreaks[ibBreak];
}


void    SetZoneKeyBreak(uchar  ibBreak) {
  zoKey.mpbrBreaks[ibBreak] = brKey;
}



// вычисляет индекс получаса для излома тарифного графика zoAlt
uchar   GetBreakAltIndex(uchar  ibBreak)
{
  GetZoneAltBreak(ibBreak);
  return( brAlt.bHour*2 + brAlt.bMinute/30 );
}


// вычисляет индекс получаса для излома тарифного графика zoKey
uchar   GetBreakKeyIndex(uchar  ibBreak)
{
  GetZoneKeyBreak(ibBreak);
  return( brKey.bHour*2 + brKey.bMinute/30 );
}



// показывает излом тарифного графика zoAlt
void    ShowZoneAltBreak(uchar  ibBreak)
{
  if (GetZoneAltSize() > 0)
  {
    GetZoneAltBreak(ibBreak);

    sprintf(szLo,"  %2u.%02u - %1u  %1u/%1u",
                 brAlt.bHour, 
                 brAlt.bMinute,
                 brAlt.ibTariff+1,
                 ibBreak+1, 
                 GetZoneAltSize());
  }
  else ShowLo(szNoZones);
}


// показывает излом тарифного графика zoKey
void    ShowZoneKeyBreak(uchar  ibBreak)
{
  if (GetZoneKeySize() > 0)
  {
    GetZoneKeyBreak(ibBreak);

    sprintf(szLo,"  %2u.%02u - %1u  %1u/%1u",
                 brKey.bHour, 
                 brKey.bMinute,
                 brKey.ibTariff+1,
                 ibBreak+1, 
                 GetZoneKeySize());
  }
  else ShowLo(szNoZones);
}



boolean TrueZone(zone  *pzo)
{
  return TRUE;
}
