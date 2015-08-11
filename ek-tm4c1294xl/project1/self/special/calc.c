/*------------------------------------------------------------------------------
CALC.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_groups.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_energy_spec.h"
#include "../impulses/max_power.h"
#include "../impulses/energy_spec.h"
#include "../digitals/digitals.h"
#include "../devices/devices.h"
#include "../special/recalc_def.h"
#include "../time/timedate.h"
#include "../nvram/cache.h"
#include "../energy.h"
#include "special.h"
#include "recalc.h"
#include "calc.h"



bool                    fLoadHou, fLoadDay, fLoadMon,
                        fLoadMem, fSaveDay, fSaveMon;



void    OpenCalc(void)
{
  tiOldDay = tiZero;                                // начинаем обработку
  tiOldMon = tiZero;

  fLoadDay = 0;
  fLoadMon = 0;

  boOpenCalc = true;
  SaveCache(&chOpenCalc);
}



void    CalcTimeDate(bool  fUseImp, bool  fUsePow, time  ti)
{
static time tiDig;

  if ((tiOldDay.bYear  != ti.bYear)  ||          // обработка по дням
      (tiOldDay.bMonth != ti.bMonth) ||
      (tiOldDay.bDay   != ti.bDay))
  {
    if (fLoadDay == 1)                                 
    {
      fLoadDay = 0;                            
      if (fUseImp == 1) SaveImpDaySpec(1,ibOldDay);
      if (fUsePow == 1) SavePowDaySpec(1,ibOldDay);
      if (fUseImp == 1) SaveDefDay(ibOldDay);
    }

    uchar ibDay;
    for (ibDay=0; ibDay<bDAYS; ibDay++)
    {
      tiDig = mpdeDay[ibDay];
      if ((ti.bYear  == tiDig.bYear)  &&
          (ti.bMonth == tiDig.bMonth) &&
          (ti.bDay   == tiDig.bDay)) break;
    }
  
    if (ibDay < bDAYS)
    {
      tiOldDay = tiDig;
      ibOldDay = ibDay;

      fLoadDay = 1;
      if (fUseImp == 1) LoadImpDaySpec(ibDay);                        
      if (fUsePow == 1) LoadPowDaySpec(ibDay);                        
      if (fUseImp == 1) LoadDefDay(ibDay);
    }
  }


  if ((tiOldMon.bYear  != ti.bYear)  ||          // обработка по месяцам
      (tiOldMon.bMonth != ti.bMonth))
  {
    if (fLoadMon == 1)
    {
      fLoadMon = 0;
      if (fUseImp == 1) SaveImpMonSpec(1,ibOldMon);
      if (fUsePow == 1) SavePowMonSpec(1,ibOldMon);
      if (fUseImp == 1) SaveDefMon(ibOldMon);
    }

    uchar ibMon;
    for (ibMon=0; ibMon<bMONTHS; ibMon++)
    {
      tiDig = mpdeMon[ibMon];
      if ((ti.bYear  == tiDig.bYear)  &&
          (ti.bMonth == tiDig.bMonth)) break;
    }
  
    if (ibMon < bMONTHS)
    {
      tiOldMon = tiDig;
      ibOldMon = ibMon;

      fLoadMon = 1;
      if (fUseImp == 1) LoadImpMonSpec(ibMon);                        
      if (fUsePow == 1) LoadPowMonSpec(ibMon);                        
      if (fUseImp == 1) LoadDefMon(ibMon);
    }
  }
}



void    CalcDigCanals(time  ti)
{
  LoadImpHouSpec(iwDigHou,1);                       // обработка по получасам

  LoadCurrDigital(ibDig);                           // обработка по каналам

  uchar c;
  for (c=0; c<bCANALS; c++)                           
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) == true)
    {
      uint w;
      if (iwDigHou == iwHardHou)
        w = 0xFFFF;
      else
      {
        w = mpwChannels[ diPrev.ibLine ];

        if (IsWinterDouble(c, ti) && (mpwImpHouCanSpec[c] != 0xFFFF))
        {
          w += mpwImpHouCanSpec[c];
          mpbWinterCan[c]++;

          if (fLoadDay == 1) MakeImpSpec_Winter( mpimDayCanSpec, c, ti );
          if (fLoadMon == 1) MakeImpSpec_Winter( mpimMonCanSpec, c, ti );
        }
      }

      mpwImpHouCanSpec[c] = w;
      mpwImpHouCanDef[c] = w;

      mpboReadyCan[c] = true;
      mpcwCalcDig[c]++;

      if (fLoadDay == 1) MakeImpSpec( mpimDayCanSpec, c, ti );
      if (fLoadMon == 1) MakeImpSpec( mpimMonCanSpec, c, ti );

      if (fLoadDay == 1) MakeDefSpec( mpdeDayCan, c, ti );
      if (fLoadMon == 1) MakeDefSpec( mpdeMonCan, c, ti );
    }
  }

  SaveImpHouSpec(1,iwDigHou);                       // обработка по получасам
}



void    CalcAllCanals(bool  fUseImp, time  ti)
{
  if (fUseImp == 1)
  {
    if (fLoadMem == 0)
    { 
      fLoadMem = 1;
      LoadImpHouSpec(iwDigHou,0);                   // обработка по получасам
    }

    uchar c;
    for (c=0; c<bCANALS; c++)           // обработка по каналам
    { 
      // если канал не используется: пропустить
      //if (mpboUsedNodes[ibCan] == false) continue;
     
      if (fLoadDay == 1) MakeImpSpec( mpimDayCanSpec, c, ti );
      if (fLoadMon == 1) MakeImpSpec( mpimMonCanSpec, c, ti );

      if (fLoadDay == 1) MakeDefSpec( mpdeDayCan, c, ti );
      if (fLoadMon == 1) MakeDefSpec( mpdeMonCan, c, ti );
    }
  }
}



void    CalcAllGroups(bool  fUsePow, time  ti)
{
  if (fUsePow == 1)
  {
    if (fLoadMem == 0)
    { 
      fLoadMem = 1;
      LoadImpHouSpec(iwDigHou,0);                   // обработка по получасам
    }

    uchar ibGrp;
    for (ibGrp=0; ibGrp<bGROUPS; ibGrp++)           // обработка по группам
    {
      if (mpfUsedGroups[ibGrp] == false) continue;

      if (fLoadDay == 1) MakeMaxPowSpec( mppoDayGrpSpec, ibGrp, ti );
      if (fLoadMon == 1) MakeMaxPowSpec( mppoMonGrpSpec, ibGrp, ti );
    }
  }
}



void    CloseCalc(bool  fUseImp, bool  fUsePow)
{
  if (fLoadDay == 1)                                // заканчиваем обработку
  {
    fLoadDay = 0;
    if (fUseImp == 1) SaveImpDaySpec(1,ibOldDay);
    if (fUsePow == 1) SavePowDaySpec(1,ibOldDay);
    if (fUseImp == 1) SaveDefDay(ibOldDay);
  }

  if (fLoadMon == 1)
  {
    fLoadMon = 0;
    if (fUseImp == 1) SaveImpMonSpec(1,ibOldMon);
    if (fUsePow == 1) SavePowMonSpec(1,ibOldMon);
    if (fUseImp == 1) SaveDefMon(ibOldMon);
  }

  boOpenCalc = false;
  SaveCache(&chOpenCalc);
}

