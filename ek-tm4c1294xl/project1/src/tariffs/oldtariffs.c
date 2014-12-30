/*------------------------------------------------------------------------------
OLDTARIFFS.Ñ

 Ïîäïðîãðàììû óïðàâëåíèÿ òàðèôàìè (ñòàðûé âàðèàíò)
------------------------------------------------------------------------------*/

#include        <string.h>
#include        <stdio.h>
#include        "../main.h"
#include        "../mem_tariffs.h"
#include        "../access.h"
#include        "tariffs.h"
#include        "zones.h"



bool                    fEnergy;



// çàìåíÿåò âî âñåõ èçëîìàõ ïåðåìåííîé zoAlt îäèí òàðèô íà äðóãîé
void    ReplaceZone(uchar  ibOld, uchar  ibNew)
{
uchar  i;

  for (i=0; i<GetZoneAltSize(); i++)
  {
    GetZoneAltBreak(i);
    if (brAlt.ibTariff = ibOld)
    {
      brAlt.ibTariff = ibNew;
      SetZoneAltBreak(i);
    }
  }
}



// çàïèñûâàåò â ðåæèì ibAltMode èçìåí¸ííûé ñóòî÷íûé òàðèôíûé ãðàôèê èç ðåæèìà 0 (áóäíè)
void    ReplaceMode(uchar  ibOld, uchar  ibNew)
{
  if (fEnergy == 0)
  {
    // ÷èòàåì ñóòî÷íûé òàðèôíûé ãðàôèê èç ðåæèìà 0 (áóäíè)
    ibMode = 0;
    zoAlt = *PGetZonePowMonthMode();

    // çàìåíÿåì îäèí òàðèô íà äðóãîé
    ReplaceZone(ibOld,ibNew);                      

    // ïîäãîòàâëèâàåì çàïèñü â ðåæèì ibAltMode
    ibMode = ibAltMode;
    boAlt = boTrue;

    // çàïèñûâàåì èçìåí¸ííûé ñóòî÷íûé òàðèôíûé ãðàôèê
    SetZonePowMonthMode();     
    SetBoolPowMonthMode();
  }
  else
  {
    // ÷èòàåì ñóòî÷íûé òàðèôíûé ãðàôèê èç ðåæèìà 0 (áóäíè)
    ibMode = 0;
    zoAlt = *PGetZoneEngMonthMode();

    // çàìåíÿåì îäèí òàðèô íà äðóãîé
    ReplaceZone(ibOld,ibNew);

    // ïîäãîòàâëèâàåì çàïèñü â ðåæèì ibAltMode
    ibMode = ibAltMode;
    boAlt = boTrue;

    // çàïèñûâàåì èçìåí¸ííûé ñóòî÷íûé òàðèôíûé ãðàôèê
    SetZoneEngMonthMode();
    SetBoolEngMonthMode();
  }
}
// òðåáóåò ïðåäâàðèòåëüíîé óñòàíîâêè ïåðåìåííûõ ibMonth,ibAltMode



// ïîääåðæêà ñòàðîãî âàðèàíòà îáðàòîòêè òàðèôîâ â íåðàáî÷èå äíè
void    MakeOldMode(void)
{
  switch (bOldMode)
  {     
    case 0:         
      ibAltMode = 1;    // äëÿ ñóááîò
      ReplaceMode(0,0); // îäèíàêîâûå òàðèôû â ðàáî÷èå è íåðàáî÷èå äíè
      ReplaceMode(1,1);
      ReplaceMode(2,2);
      ReplaceMode(3,3);

      ibAltMode = 2;    // äëÿ âûõîäíûõ äíåé
      ReplaceMode(0,0); // îäèíàêîâûå òàðèôû â ðàáî÷èå è íåðàáî÷èå äíè
      ReplaceMode(1,1);
      ReplaceMode(2,2);
      ReplaceMode(3,3);
      break;
    
    case 1:
    case 3:          
      ibAltMode = 1;    // äëÿ ñóááîò
      ReplaceMode(0,1); // â ñóáîòíèå è âûõîäíûå äíè ïî äíåâíîìó òàðèôó
      ReplaceMode(1,1);
      ReplaceMode(2,1);
      ReplaceMode(3,1);

      ibAltMode = 2;    // äëÿ âûõîäíûõ äíåé
      ReplaceMode(0,1); // â ñóáîòíèå è âûõîäíûå äíè ïî äíåâíîìó òàðèôó
      ReplaceMode(1,1);
      ReplaceMode(2,1);
      ReplaceMode(3,1);
      break;
    
    case 2:          
      ibAltMode = 1;    // äëÿ ñóááîò
      ReplaceMode(0,0); // â ñóáîòíèå è âûõîäíûå äíè ïî íî÷íîìó òàðèôó
      ReplaceMode(1,0);
      ReplaceMode(2,0);
      ReplaceMode(3,0);

      ibAltMode = 2;    // äëÿ âûõîäíûõ äíåé
      ReplaceMode(0,0); // â ñóáîòíèå è âûõîäíûå äíè ïî íî÷íîìó òàðèôó
      ReplaceMode(1,0);
      ReplaceMode(2,0);
      ReplaceMode(3,0);
      break;

    case 4:          
      ibAltMode = 1;    // äëÿ ñóááîò
      ReplaceMode(0,0);       
      ReplaceMode(1,0); // äíåâíîé òàðèô çàìåíÿåòñÿ íà íî÷íîé òàðèô
      ReplaceMode(2,1); // óòðåííèé è âå÷åðíèé òàðèôû çàìåíÿþòñÿ íà äíåâíîé òàðèô
      ReplaceMode(3,1);

      ibAltMode = 2;    // äëÿ âûõîäíûõ äíåé
      ReplaceMode(0,0);       
      ReplaceMode(1,0); // äíåâíîé òàðèô çàìåíÿåòñÿ íà íî÷íîé òàðèô
      ReplaceMode(2,1); // óòðåííèé è âå÷åðíèé òàðèôû çàìåíÿþòñÿ íà äíåâíîé òàðèô
      ReplaceMode(3,1);
      break;

    case 5:          
      ibAltMode = 1;    // äëÿ ñóááîò
      ReplaceMode(0,0);       
      ReplaceMode(1,1);       
      ReplaceMode(2,1); // óòðåííèé è âå÷åðíèé òàðèôû çàìåíÿþòñÿ íà äíåâíîé òàðèô
      ReplaceMode(3,1);

      ibAltMode = 2;    // äëÿ âûõîäíûõ äíåé
      ReplaceMode(0,0);       
      ReplaceMode(1,0); // äíåâíîé òàðèô çàìåíÿåòñÿ íà íî÷íîé òàðèô
      ReplaceMode(2,1); // óòðåííèé è âå÷åðíèé òàðèôû çàìåíÿþòñÿ íà äíåâíîé òàðèô
      ReplaceMode(3,1);
      break;
  }
}
// òðåáóåò ïðåäâàðèòåëüíîé óñòàíîâêè ïåðåìåííûõ ibMonth,fEnergy



// èçìåíåíèå ñòàðîãî âàðèàíòà îáðàòîòêè òàðèôîâ â íåðàáî÷èå äíè
void    MakeAllOldModes(uchar  bT)
{
  bOldMode = bT;

  for (ibMonth=0; ibMonth<12; ibMonth++)
  {
    fEnergy = 1; MakeOldMode();
    fEnergy = 0; MakeOldMode();
  }
}



// çàïèñü ñóòî÷íîãî òàðèôíîãî ãðàôèêà íà íåñêîëüêî ìåñÿöåâ (äëÿ ýíåðãèè)
void    SetCharEngMonths(uchar  ibBeg, uchar  ibEnd)
{
  ibMode = 0;
  SetZonesEngMonthsMode(ibBeg,ibEnd);

  fEnergy = 1;
  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    MakeOldMode();
    mpchEngMonth[ibMonth] = chOldMode;
  }
}
// òðåáóåò ïðåäâàðèòåëüíîé óñòàíîâêè ïåðåìåííûõ zoKey,chOldMode


// çàïèñü ñóòî÷íîãî òàðèôíîãî ãðàôèêà íà íåñêîëüêî ìåñÿöåâ (äëÿ ìîùíîñòè)
void    SetCharPowMonths(uchar  ibBeg, uchar  ibEnd)
{
  ibMode = 0;
  SetZonesPowMonthsMode(ibBeg,ibEnd);

  fEnergy = 0;
  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    MakeOldMode();
    mpchPowMonth[ibMonth] = chOldMode;
  }
}
// òðåáóåò ïðåäâàðèòåëüíîé óñòàíîâêè ïåðåìåííûõ zoKey,chOldMode
