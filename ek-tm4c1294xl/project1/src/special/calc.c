/*------------------------------------------------------------------------------
CALC.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_groups.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_energy_spec.h"
#include        "../impulses/max_power.h"
#include        "../impulses/energy_spec.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_run.h"
#include        "../special/recalc_def.h"
#include        "../time/timedate.h"
#include        "../energy.h"
#include        "calc.h"



bool                    fLoadHou, fLoadDay, fLoadMon,
                        fLoadMem, fSaveDay, fSaveMon;



void    OpenCalc(void)
{
  tiOldDay = tiZero;                                // начинаем обработку
  tiOldMon = tiZero;

  fLoadDay = 0;
  fLoadMon = 0;

  boOpenCalc = TRUE;
}



void    CalcTimeDate(bool  fUseImp, bool  fUsePow)
{
static time tiDig;

  if ((tiOldDay.bYear  != tiAlt.bYear)  ||          // обработка по дням
      (tiOldDay.bMonth != tiAlt.bMonth) ||
      (tiOldDay.bDay   != tiAlt.bDay)) 
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
      tiDig = mpdeDay[ibDay].tiNow;                   
      if ((tiAlt.bYear  == tiDig.bYear)  &&            
          (tiAlt.bMonth == tiDig.bMonth) &&
          (tiAlt.bDay   == tiDig.bDay)) break;
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


  if ((tiOldMon.bYear  != tiAlt.bYear)  ||          // обработка по месяцам
      (tiOldMon.bMonth != tiAlt.bMonth))
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
      tiDig = mpdeMon[ibMon].tiNow;                   
      if ((tiAlt.bYear  == tiDig.bYear)  &&            
          (tiAlt.bMonth == tiDig.bMonth)) break;
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



void    CalcDigCanals(void)
{
  LoadImpHouSpec(iwDigHou,1);                       // обработка по получасам

  LoadCurrDigital(ibDig);                           // обработка по каналам

  uchar ibCan;
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1)
    {
      uint w;
      if (iwDigHou == iwHardHou)
        w = 0xFFFF;
      else
      {
        w = mpwChannels[ diPrev.ibLine ];

        if (IsWinterDouble(ibCan) && (GetCanInt(mpwImpHouCanSpec, ibCan) != 0xFFFF))
        {
          w += GetCanInt(mpwImpHouCanSpec, ibCan);
          mpbWinterCan[ibCan]++;

          if (fLoadDay == 1) MakeImpSpec_Winter( mpimDayCanSpec );
          if (fLoadMon == 1) MakeImpSpec_Winter( mpimMonCanSpec );
        }
      }

      SetCanInt(mpwImpHouCanSpec, ibCan, w);
      mpwImpHouCanDef[ibCan] = w;

      mpboReadyCan[ibCan] = TRUE;
      mpcwCalcDig[ibCan]++;

      if (fLoadDay == 1) MakeImpSpec( mpimDayCanSpec );    
      if (fLoadMon == 1) MakeImpSpec( mpimMonCanSpec );    

      if (fLoadDay == 1) MakeDefSpec( mpdeDayCan, ibCan );
      if (fLoadMon == 1) MakeDefSpec( mpdeMonCan, ibCan );
    }
  }

  SaveImpHouSpec(1,iwDigHou);                       // обработка по получасам
}



void    CalcAllCanals(bool  fUseImp)
{
  if (fUseImp == 1)
  {
    if (fLoadMem == 0)
    { 
      fLoadMem = 1;
      LoadImpHouSpec(iwDigHou,0);                   // обработка по получасам
    }

    uchar ibCan;
    for (ibCan=0; ibCan<bCANALS; ibCan++)           // обработка по каналам
    { 
      // если канал не используется: пропустить
      //if (mpboUsedNodes[ibCan] == FALSE) continue;
     
      if (fLoadDay == 1) MakeImpSpec( mpimDayCanSpec );    
      if (fLoadMon == 1) MakeImpSpec( mpimMonCanSpec );    

      if (fLoadDay == 1) MakeDefSpec( mpdeDayCan, ibCan );
      if (fLoadMon == 1) MakeDefSpec( mpdeMonCan, ibCan );
    }
  }
}



void    CalcAllGroups(bool  fUsePow)
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
      if (mpboUsedGroups[ibGrp] == FALSE) continue;

      if (fLoadDay == 1) MakeMaxPowSpec( mppoDayGrpSpec );
      if (fLoadMon == 1) MakeMaxPowSpec( mppoMonGrpSpec );
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

  boOpenCalc = FALSE;
}

