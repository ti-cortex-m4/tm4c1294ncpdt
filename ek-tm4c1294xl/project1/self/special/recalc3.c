/*------------------------------------------------------------------------------
recalc3.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../display/panel.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_energy_spec.h"
#include "../kernel/arrays_buff.h"
#include "../realtime/realtime_spec.h"
#include "../tariffs/tariffs.h"
#include "../impulses/energy_spec.h"
#include "../impulses/max_power.h"
#include "../time/calendar.h"
#include "calc.h"
#include "recalc.h"
#include "recalc3.h"



//                                         0123456789ABCDEF
static char const       szRecalc3[]     = "   расчет...    ";



void    OpenCalc_MaxPowCurrDay(void)
{
  boOpenCalc = true;
  SaveCache(&chOpenCalc);

  memset(&mppoDayGrpSpec, 0, sizeof(power)*bGROUPS);
}


void    CloseCalc_MaxPowCurrDay(void)
{
  memcpy(mppoDayGrp[ ibSoftDay ], mppoDayGrpSpec, sizeof(power)*bGROUPS);

  boOpenCalc = false;
  SaveCache(&chOpenCalc);
}


void    CalcAllGroups_MaxPowCurrDay(time  ti)
{
  if (fLoadMem == 0)
  { 
    fLoadMem = 1;
    LoadImpHouSpec(iwDigHou,0);
  }

  uchar g;
  for (g=0; g<bGROUPS; g++)
  {
    if (mpfUsedGroups[g] == false) continue;

    MakeMaxPowSpec( mppoDayGrpSpec, g, ti );
  }
}


void    Recalc_MaxPowCurrDay(void)
{ 
  ShowLo(szRecalc3);
  OpenCalc_MaxPowCurrDay();


  ulong dwHouIndex = DateToHouIndex(tiCurr);        // индекс текущего получаса

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


    time ti = HouIndexToDate(dwHouIndex);
    dwHouIndex--;                                   // индекс обрабатываемого получаса


    MakeAllPrevTariffs(ti);

    fLoadMem = 0;
    CalcAllGroups_MaxPowCurrDay(ti);
  }


  CloseCalc_MaxPowCurrDay();

  SavePowDayBuff();
}
