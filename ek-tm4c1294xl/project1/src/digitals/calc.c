/*------------------------------------------------------------------------------
CALC.C


------------------------------------------------------------------------------*/

#include        "../main.h"




void    OpenCalc(void)
{
  tiOldDay = tiZero;                                // начинаем обработку
  tiOldMon = tiZero;

  fLoadDay = 0;
  fLoadMon = 0;

  boOpenCalc = boTrue;
}



void    CalcTimeDate(bool  fUseImp, bool  fUsePow)
{
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
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    {
      if (iwDigHou == iwHardHou)
        wBuffD = 0xFFFF;
      else
      {
        wBuffD = mpwChannels[ diPrev.ibLine ];

        if (IsDouble(ibCan) && (*PGetCanInt(mpwImpHouCanSpec, ibCan) != 0xFFFF))
        {
          wBuffD += *PGetCanInt(mpwImpHouCanSpec, ibCan); 
          mpbWinterCan[ibCan]++;

          if (fLoadDay == 1) MakeImpSpec_Winter( mpimDayCanSpec );
          if (fLoadMon == 1) MakeImpSpec_Winter( mpimMonCanSpec );
        }
      }

      SetCanInt(mpwImpHouCanSpec, ibCan, wBuffD); 
      mpwImpHouCanDef[ibCan] = wBuffD; 

      mpboReadyCan[ibCan] = boTrue;
      mpcwCalcDig[ibCan]++;

      if (fLoadDay == 1) MakeImpSpec( mpimDayCanSpec );    
      if (fLoadMon == 1) MakeImpSpec( mpimMonCanSpec );    

      if (fLoadDay == 1) MakeDefSpec( mpdeDayCan );
      if (fLoadMon == 1) MakeDefSpec( mpdeMonCan );
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

    for (ibCan=0; ibCan<bCANALS; ibCan++)           // обработка по каналам
    { 
      // если канал не используется: пропустить
      //if (mpboUsedNodes[ibCan] == boFalse) continue;
     
      if (fLoadDay == 1) MakeImpSpec( mpimDayCanSpec );    
      if (fLoadMon == 1) MakeImpSpec( mpimMonCanSpec );    

      if (fLoadDay == 1) MakeDefSpec( mpdeDayCan );
      if (fLoadMon == 1) MakeDefSpec( mpdeMonCan );
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

    for (ibGrp=0; ibGrp<bGROUPS; ibGrp++)           // обработка по группам
    {
      if (mpboUsedGroups[ibGrp] == boFalse) continue;

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

  boOpenCalc = boFalse;
}

