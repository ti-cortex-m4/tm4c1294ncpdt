/*------------------------------------------------------------------------------
TARIFFS.C

 Ïîäïðîãðàììû óïðàâëåíèÿ òàðèôàìè
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../mem_tariffs.h"
#include        "../display.h"
#include        "../delay.h"
#include        "../access.h"
#include        "../rtc.h"
#include        "../timedate.h"
#include        "zones.h"
#include        "oldtariffs.h"
#include        "relaxs.h"
#include        "gaps.h"



// òåêóùèå èíäåêñû ïî ìàññèâàì
uchar                   ibMonth,ibMode;



// çàïèñûâàåò ôàêò çàäàíèÿ ñóòî÷íîãî òàðèôíîãî ãðàôèêà (äëÿ ýíåðãèè)
void    SetBoolEngMonthMode(void)
{
  mpboEngMonthMode[ibMonth][ibMode] = boAlt;
}

/*
// ÷èòàåò ôàêò çàäàíèÿ ñóòî÷íîãî òàðèôíîãî ãðàôèêà (äëÿ ýíåðãèè)
boolean GetBoolEngMonthMode(void)
{
  return( mpboEngMonthMode[ibMonth][ibMode] );
}
*/

// çàïèñûâàåò ôàêò çàäàíèÿ ñóòî÷íîãî òàðèôíîãî ãðàôèêà (äëÿ ìîùíîñòè)
void    SetBoolPowMonthMode(void)
{
  mpboPowMonthMode[ibMonth][ibMode] = boAlt;
}

/*
// ÷èòàåò ôàêò çàäàíèÿ ñóòî÷íîãî òàðèôíîãî ãðàôèêà (äëÿ ìîùíîñòè)
boolean GetBoolPowMonthMode(void)
{
  return( mpboPowMonthMode[ibMonth][ibMode] );
}
*/


// çàïèñûâàåò ñóòî÷íûé òàðèôíûé ãðàôèê (äëÿ ýíåðãèè)
void    SetZoneEngMonthMode(void)
{
  mpzoEngMonthMode[ibMonth][ibMode] = zoAlt;
}


// ÷èòàåò ñóòî÷íûé òàðèôíûé ãðàôèê (äëÿ ýíåðãèè)
zones  *PGetZoneEngMonthMode(void)
{
  return( &mpzoEngMonthMode[ibMonth][ibMode] );
}


// çàïèñûâàåò ñóòî÷íûé òàðèôíûé ãðàôèê (äëÿ ìîùíîñòè)
void    SetZonePowMonthMode(void)
{
  mpzoPowMonthMode[ibMonth][ibMode] = zoAlt;
}


// ÷èòàåò ñóòî÷íûé òàðèôíûé ãðàôèê (äëÿ ìîùíîñòè)
zones  *PGetZonePowMonthMode(void)
{
  return( &mpzoPowMonthMode[ibMonth][ibMode] );
}



// çàïèñûâàåò ñóòî÷íûé òàðèôíûé ãðàôèê íà íåñêîëüêî ìåñÿöåâ (äëÿ ýíåðãèè)
void    SetZonesEngMonthsMode(uchar  ibBeg, uchar  ibEnd)
{
  boAlt = boTrue;
  memcpy(&zoAlt, &zoKey, sizeof(zones));

  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    SetZoneEngMonthMode();
    SetBoolEngMonthMode();
  }
}
// òðåáóåò ïðåäâàðèòåëüíîé óñòàíîâêè ïåðåìåííûõ ibMode,zoKey


// çàïèñûâàåò ñóòî÷íûé òàðèôíûé ãðàôèê íà íåñêîëüêî ìåñÿöåâ (äëÿ ìîùíîñòè)
void    SetZonesPowMonthsMode(uchar  ibBeg, uchar  ibEnd)
{
  boAlt = boTrue;
  memcpy(&zoAlt, &zoKey, sizeof(zones));

  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    SetZonePowMonthMode();
    SetBoolPowMonthMode();
  }
}
// òðåáóåò ïðåäâàðèòåëüíîé óñòàíîâêè ïåðåìåííûõ ibMode,zoKey



void    SetTariffsDefault(void)
{
  if (boPublicCurr == boTrue)
  {
    chOldMode = '_';

    SetKeyZonePow();
    SetCharEngMonths(0,11);

    SetKeyZonePow();
    SetCharPowMonths(0,11);
  }
  else
  {
    chOldMode = '_';

    SetKeyZoneEng();
    SetCharEngMonths(0,11);

    SetKeyZonePow();
    SetCharPowMonths(0,11);
  }
}



// ñáðîñ íàñòðîåê ïî óìîë÷àíèþ
void    ResetTariffs(void)
{
  // ñîâìåù¸ííûå òàðèôíûå ãðàôèêè äëÿ ìùíîñòè è ýíåðãèè
  boPublicCurr = boFalse;

  // ñòàðûé âàðèàíò îáðàáîòêè òàðèôîâ
  boOldTariffs = boTrue;

  // ïðàâèëî îáðàáîòêè òàðèôîâ â âûõîäíûå äíè (ñòàðûé âàðèàíò)
  bOldMode = 0;

  boAlt = boFalse;
  for (ibMonth=0; ibMonth<12+4+1; ibMonth++)
  {
    for (ibMode=0; ibMode<bMODES; ibMode++)
    {
      SetBoolEngMonthMode(); 
      SetBoolPowMonthMode(); 
    }
  }

  memset(&mpchEngMonth, '\0', sizeof(mpchEngMonth)); 
  memset(&mpchPowMonth, '\0', sizeof(mpchPowMonth)); 

  SetTariffsDefault();
}



// ðàññ÷èòûâàåò ìàññèâ èíäåêñîâ òàðèôîâ äëÿ êàæäîãî ïîëó÷àñà òåêóùèõ ñóòîê
void    MakeTariff(uchar  mpTariff[48])
{
uchar   i,j;

  GetZoneAltBreak(0);
  for (j=0; j<48; j++)
    mpTariff[j] = brAlt.ibTariff;

  j = 0;
  for (i=0; i<bBREAKS; i++)
  {
    while (j < GetBreakAltIndex(i))
    {
      GetZoneAltBreak(i);
      mpTariff[j++] = brAlt.ibTariff;
    }
  }
}
// òðåáóåò ïðåäâàðèòåëüíîé óñòàíîâêè ïåðåìåííûõ zoAlt



// âîçâðàùàåò òèï òåêóùèõ ñóòîê îòíîñèòåëüíîñ ïðèñêà ïðàçäíèêîâ
uchar   RelaxIndex(void)
{
uchar i;

  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);
    if ((tiRelax.bDay   == tiAlt.bDay) &&
        (tiRelax.bMonth == tiAlt.bMonth)) 
      return tiRelax.bSecond;   
  }

  return 0;
}
// òðåáóåò ïðåäâàðèòåëüíîé óñòàíîâêè ïåðåìåííûõ tiAlt



// ðàññ÷èòûâàåò ìàññèâ èíäåêñîâ òàðèôîâ äëÿ êàæäîãî ïîëó÷àñà òåêóùèõ ñóòîê (äëÿ ìîùíîñòè è ýíåðãèè)
void    MakeAllCurrTariffs(void)
{
uchar  i,j;

  tiAlt = *PGetCurrTimeDate();

  if (boGapsFlag == boFalse) 
  {
    ibMonth = tiAlt.bMonth - 1;
  }
  else
  {
    MakeGaps();
    ibMonth = mpbGaps[GetDayIndex_Alt()];
  } 

  ibMode  = GetModeAlt();               

  zoAlt = *PGetZoneEngMonthMode();
  MakeTariff(mpibEngCurrTariff);

  zoAlt = *PGetZonePowMonthMode();
  MakeTariff(mpibPowCurrTariff);

  if (boRelaxsFlag == boTrue)
  {
    j = RelaxIndex();
    i = Weekday();
    if ((j != 2) && ((i == 5) || (i == 6) || (j == 1)))
    {
      i = ibRelaxsTariff; 
      if (i >= bTARIFFS) i = 0;
      // memset(&mpibEngCurrTariff, i, sizeof(mpibEngCurrTariff));
      memset(&mpibPowCurrTariff, i, sizeof(mpibPowCurrTariff));
    }
  }
}


void    MakeAllPrevTariffs(void)
{
uchar  i,j;

  ibMonth = tiAlt.bMonth - 1;                   

  if (boGapsFlag == boFalse) 
  {
    ibMonth = tiAlt.bMonth - 1;
  }
  else
  {
    MakeGaps();
    ibMonth = mpbGaps[GetDayIndex_Alt()];
  } 

  ibMode  = GetModeAlt();               

  zoAlt = *PGetZoneEngMonthMode();
  MakeTariff(mpibEngPrevTariff);

  zoAlt = *PGetZonePowMonthMode();
  MakeTariff(mpibPowPrevTariff);

  if (boRelaxsFlag == boTrue)
  {
    j = RelaxIndex();
    i = Weekday();
    if ((j != 2) && ((i == 5) || (i == 6) || (j == 1)))
    {
      i = ibRelaxsTariff; 
      if (i >= bTARIFFS) i = 0;
      // memset(&mpibEngPrevTariff, i, sizeof(mpibEngPrevTariff));
      memset(&mpibPowPrevTariff, i, sizeof(mpibPowPrevTariff));
    }
  }
}
// òðåáóåò ïðåäâàðèòåëüíîé óñòàíîâêè ïåðåìåííîé tiAlt
