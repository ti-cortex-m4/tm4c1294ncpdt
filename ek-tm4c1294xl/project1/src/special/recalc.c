/*------------------------------------------------------------------------------
RECALC.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_energy_spec.h"
#include "../memory/mem_profile.h"
#include "../realtime/realtime_spec.h"
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../tariffs/tariffs.h"
#include "../energy2.h"
#include "calc.h"
#include "recalc_def.h"
#include "recalc.h"



//                                         0123456789ABCDEF
static char const       szRecalc1[]     = "Очистка данных  ",
                        szRecalc2[]     = "Расчет данных   ";



bool    Recalc(bool  fUseImp, bool  fUsePow)
{
uchar   i;

  ShowHi(szRecalc1); Clear();
  uchar cbPercent = 0;

  boOpenCalc = true;

  if (fUseImp == 1)                                 // обнуление импульсов (энергии)
  {
    memset(&mpimDayCan, 0, sizeof(mpimDayCan));
    memset(&mpimMonCan, 0, sizeof(mpimMonCan));

    for (i=0; i<bDAYS; i++)
    {
      if (SaveImpDay(0,i,0) == 0) return(0);
      ShowPercent(cbPercent++);
    }

    for (i=0; i<bMONTHS; i++)
    {
      if (SaveImpMon(0,i,0) == 0) return(0);
      ShowPercent(cbPercent++);
    }

    ResetDef();
  }

  if (fUsePow == 1)                                 // обнуление максимумов мощности
  {
    memset(&mppoDayGrp, 0, sizeof(mppoDayGrp));
    memset(&mppoMonGrp, 0, sizeof(mppoMonGrp));

    for (i=0; i<bDAYS; i++)
    {
      if (SavePowDay(0,i,0) == 0) return(0);
      ShowPercent(cbPercent++);
    }

    for (i=0; i<bMONTHS; i++)
    {
      if (SavePowMon(0,i,0) == 0) return(0);
      ShowPercent(cbPercent++);
    }
  }


  ShowHi(szRecalc2); Clear();

  ulong dwHouIndex = DateToHouIndex(tiCurr);        // индекс текущего получаса

  OpenCalc();                                       // начинаем обработку


  bHouInc = 0;

  uint iwHou;
  for (iwHou=0; iwHou<wHOURS; iwHou++)
  {
    if (fKey == 1) { fKey = 0; Beep(); }
    if ((iwHou % 0x10) == 0) ShowPercent((ulong)100*iwHou/(wHOURS-1));
    if ((iwHou % 0x10) == 0) NexttimeMnt();

    iwDigHou = (wHOURS + iwHardHou - iwHou - bHouInc) % wHOURS;


    tiAlt = HouIndexToDate(dwHouIndex);
    dwHouIndex--;                                   // индекс обрабатываемого получаса

    CalcTimeDate(fUseImp,fUsePow);


    MakeAllPrevTariffs();

    fLoadMem = 0;
    CalcAllCanals(fUseImp);
    CalcAllGroups(fUsePow);
  }

  CloseCalc(fUseImp,fUsePow);                       // заканчиваем обработку

  return(1);
}


/*
bool    ClearCanals(bool  fStopCan)
{
  ShowHi(szProcess); Clear();

  memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));

  wBuffD = ((wHOURS + iwHardHou - iwAmin) % wHOURS) + 4;

  for (ibDig=ibXmin; ibDig<=ibXmax; ibDig++)
  {
    LoadCurrDigital(ibDig);
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);

      if (CompareCurrPrevLines() == 1)
      {
        mpboReadyCan[ibCan] = boTrue;
        if (fStopCan == 1) mpcwStopCan[ibCan] = wBuffD;
      }
    }
  }


  fLoadHou = 0;

  bHouInc = 0;
  for (iwHou=0; iwHou<wHOURS; iwHou++)
  {
    if (fKey == 1) { fKey = 0; Beep(); }
    if ((iwHou % 0x10) == 0) ShowPercent((ulong)100*iwHou/(wHOURS-1));
    if ((iwHou % 0x10) == 0) NexttimeMnt();

    iwDigHou = (wHOURS + iwHardHou - iwHou - bHouInc) % wHOURS;


    if (iwDigHou == iwAmax) fLoadHou = 1;

    if (fLoadHou == 1)
    {
      LoadImpHouSpec(iwDigHou,1);                   // обработка по получасам

      for (ibCan=0; ibCan<bCANALS; ibCan++)         // обработка по каналам
      {
        // если канал не используется: пропустить
        //if (mpboUsedNodes[ibCan] == boFalse) continue;

        if (mpboReadyCan[ibCan] == boTrue)
        {
          if (fStopCan == 1) wBuffD = 0xFFFF; else wBuffD = 0;
          SetCanInt(mpwImpHouCanSpec, ibCan, wBuffD);
        }
      }

      SaveImpHouSpec(1,iwDigHou);
    }

    if (iwDigHou == iwAmin) fLoadHou = 0;
  }

  return( Recalc(1,1) );
}
*/
