/*------------------------------------------------------------------------------
ZONES.C

 Подпрограммы управления суточными тарифными графиками
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../keyboard.h"
#include        "../display/display.h"



//                                       0123456789ABCDEF  
static char const       szNoZones[]   = " зоны не заданы ";


br3ak const            brZero = { 0, 0, 0 };

zone const             zoDefaultPow = {
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

zone const             zoDefaultEng = {
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



// читает количество изломов в тарифном графике zoAlt
uchar   GetZoneAltSize(void)
{
  return( zoAlt.bSize );
}


// записывает количество изломов в тарифном графике zoAlt
void    SetZoneAltSize(uchar  bSize)
{
  zoAlt.bSize = bSize;
}



// читает излом brAlt из тарифного графика zoAlt
void    GetZoneAltBreak(uchar  ibBreak)
{
  brAlt = zoAlt.mpbrBreaks[ibBreak];
}


// записывает излом brAlt в тарифный график zoAlt
void    SetZoneAltBreak(uchar  ibBreak)
{
  zoAlt.mpbrBreaks[ibBreak] = brAlt;
}



// читает количество изломов в тарифном графике zoKey
uchar   GetZoneKeySize(void)
{
  return( zoKey.bSize );
}


// записывает количество изломов в тарифном графике zoKey
void    SetZoneKeySize(uchar  bSize)
{
  zoKey.bSize = bSize;
}



// читает излом brKey из тарифного графика zoKey
void    GetZoneKeyBreak(uchar  ibBreak)
{
  brKey = zoKey.mpbrBreaks[ibBreak];
}


// записывает излом brKey в тарифный график zoKey
void    SetZoneKeyBreak(uchar  ibBreak)
{
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



// сбрасывает настройки по умолчанию для переменных zoAlt,zoKey
void    ResetZones(void)
{
static uchar const  mpbZone[3*bBREAKS] =
{  6,  0,  0,
   8,  0,  1,
  10,  0,  2,
  18,  0,  1,
  20,  0,  3,
  21, 30,  1 };

  ibY = 0;
  for (ibX=0; ibX<bBREAKS; ibX++)
  {    
    brAlt.bHour    = mpbZone[ibY++];
    brAlt.bMinute  = mpbZone[ibY++];
    brAlt.ibTariff = mpbZone[ibY++];

    SetZoneAltBreak(ibX);
  }

  SetZoneAltSize(bBREAKS);

  memcpy(&zoKey, &zoAlt, sizeof(zone));
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



#ifndef MODBUS

// проверяет правильность суточного тарифного графика
bool    TrueZone(void)
{
  return true;
}

#endif
