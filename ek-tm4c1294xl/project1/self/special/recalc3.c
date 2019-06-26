/*------------------------------------------------------------------------------
CALC3.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "engine.h"
#include        "beep.h"
#include        "keyboard.h"
#include        "nexttime.h"
#include        "special.h"
#include        "tariffs.h"
#include        "power.h"
#include        "timedate.h"
#include        "essential.h"



//                                         0123456789ABCDEF
message         code    szCalc3         = "   расчет...    ";



void    OpenCalc_MaxPowCurrDay(void)
{
  boOpenCalc = boTrue;

  memset(&mppoDayGrpSpec, 0, sizeof(power)*bGROUPS);
}


void    CloseCalc_MaxPowCurrDay(void)
{
  memcpy(mppoDayGrp[ ibSoftDay ], mppoDayGrpSpec, sizeof(power)*bGROUPS);

  boOpenCalc = boFalse;
}


void    CalcAllGroups_MaxPowCurrDay(void)
{
  if (fLoadMem == 0)
  { 
    fLoadMem = 1;
    LoadImpHouSpec(iwDigHou,0);
  }

  for (ibGrp=0; ibGrp<bGROUPS; ibGrp++)
  {
    if (mpboUsedGroups[ibGrp] == boFalse) continue;

    MakeMaxPowSpec( mppoDayGrpSpec );
  }
}


void    Recalc_MaxPowCurrDay(void)
{ 
  ShowLo(szCalc3);
  OpenCalc_MaxPowCurrDay();


  tiAlt = tiCurr;
  dwHouIndex = DateToHouIndex();

  bHouInc = 0;
  for (iwHou=0; iwHou<=GetHouIndex(); iwHou++) 
  {
//    if (fKey == 1) { fKey = 0; Beep(); }
//    if ((iwHou % 0x10) == 0) ShowPercent((ulong)100*iwHou/(wHOURS-1));    
    if ((iwHou % 0x10) == 0) NexttimeMnt();
  
    iwDigHou = (wHOURS + iwHardHou - iwHou - bHouInc) % wHOURS;


    HouIndexToDate(dwHouIndex);
    dwHouIndex--;


    MakeAllPrevTariffs();

    fLoadMem = 0;
    CalcAllGroups_MaxPowCurrDay();
  }


  CloseCalc_MaxPowCurrDay();
}
