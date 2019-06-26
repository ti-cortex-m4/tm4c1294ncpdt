/*------------------------------------------------------------------------------
recalc3.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
//#include "../display/panel.h"
//#include "../memory/mem_energy.h"
#include "../memory/mem_energy_spec.h"
//#include "../memory/mem_profile.h"
//#include "../memory/mem_settings.h"
//#include "../realtime/realtime_spec.h"
#include "../tariffs/tariffs.h"
//#include "../impulses/energy_spec.h"
//#include "../digitals/digitals.h"
//#include "../digitals/profile/profile_frac.h"
//#include "../digitals/profile/profile_frac8.h"
//#include "../flash/records.h"
//#include "../time/timedate.h"
//#include "../time/calendar.h"
//#include "../energy2.h"
//#include "calc.h"
//#include "special.h"
//#include "recalc_def.h"
#include "recalc3.h"



//                                         0123456789ABCDEF
static char const       szRecalc[]      = "   расчет...    ";



void    OpenCalc_MaxPowCurrDay(void)
{
  boOpenCalc = true;

  memset(&mppoDayGrpSpec, 0, sizeof(power)*bGROUPS);
}


void    CloseCalc_MaxPowCurrDay(void)
{
  memcpy(mppoDayGrp[ ibSoftDay ], mppoDayGrpSpec, sizeof(power)*bGROUPS);

  boOpenCalc = false;
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

  bHhrInc = 0;

  uint iwHhr;
  for (iwHhr=0; iwHhr<wHOURS; iwHhr++)
  {
    if (fKey == true) { fKey = 0; Beep(); }
    if ((iwHhr % 0x10) == 0) ShowPercent((ulong)100*iwHhr/(wHOURS-1));
    if ((iwHhr % 0x10) == 0) NexttimeMnt();
#ifdef NO_DISPLAY
    RunPanel_CleaningHhr(iwHhr);
#endif

    iwDigHou = (wHOURS + iwHardHou - iwHhr - bHhrInc) % wHOURS;
  
    iwDigHou = (wHOURS + iwHardHou - iwHou - bHouInc) % wHOURS;


    HouIndexToDate(dwHouIndex);
    dwHouIndex--;


    MakeAllPrevTariffs();

    fLoadMem = 0;
    CalcAllGroups_MaxPowCurrDay();
  }


  CloseCalc_MaxPowCurrDay();
}
