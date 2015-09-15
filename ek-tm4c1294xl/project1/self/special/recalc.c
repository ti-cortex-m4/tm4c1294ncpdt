/*------------------------------------------------------------------------------
RECALC.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_energy_spec.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_settings.h"
#include "../realtime/realtime_spec.h"
#include "../tariffs/tariffs.h"
#include "../impulses/energy_spec.h"
#include "../digitals/digitals.h"
#include "../flash/records.h"
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../energy2.h"
#include "calc.h"
#include "special.h"
#include "recalc_def.h"
#include "recalc.h"



//                                         0123456789ABCDEF
static char const       szRecalc1[]     = "Очистка данных  ",
                        szRecalc2[]     = "Расчет данных   ",
                        szOpenCalc1[]   = "   Выключение   ",
                        szOpenCalc2[]   = "во время расчета",
                        szProcess[]     = "Обработка       ";


cache const             chOpenCalc = {OPEN_CALC, &boOpenCalc, sizeof(bool)};



void    InitRecalc(void)
{
  LoadCache(&chOpenCalc);

  if (boOpenCalc == true)
  {
    if (enGlobal == GLB_WORK)
    {
      AddSysRecord(EVE_OPENCALC1);
      Recalc(1,1);
      AddSysRecord(EVE_OPENCALC2);

      boOpenCalc = false;
      SaveCache(&chOpenCalc);

      ShowHi(szOpenCalc1);
      ShowLo(szOpenCalc2);
    }
  }
}



bool    Recalc(bool  fUseImp, bool  fUsePow)
{
uchar   i;

  ShowHi(szRecalc1); Clear();
  uchar cbPercent = 0;

  boOpenCalc = true;
  SaveCache(&chOpenCalc);

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


  bHhrInc = 0;

  uint iwHhr;
  for (iwHhr=0; iwHhr<wHOURS; iwHhr++)
  {
    if (fKey == 1) { fKey = 0; Beep(); }
    if ((iwHhr % 0x10) == 0) ShowPercent((ulong)100*iwHhr/(wHOURS-1));
    if ((iwHhr % 0x10) == 0) NexttimeMnt();

    iwDigHou = (wHOURS + iwHardHou - iwHhr - bHhrInc) % wHOURS;


    time ti = HouIndexToDate(dwHouIndex);
    dwHouIndex--;                                   // индекс обрабатываемого получаса

    CalcTimeDate(fUseImp, fUsePow, ti);


    MakeAllPrevTariffs(ti);

    fLoadMem = 0;
    CalcAllCanals(fUseImp, ti);
    CalcAllGroups(fUsePow, ti);
  }

  CloseCalc(fUseImp,fUsePow);                       // заканчиваем обработку

  CloseSpecialBuff();

  return(1);
}



bool    ClearCanals(uchar  ibDigMin, uchar  ibDigMax, uint  wHhrMin, uint  wHhrMax, bool  fStopCan)
{
  ShowHi(szProcess); Clear();

  memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));

  uint wStop = ((wHOURS + iwHardHou - wHhrMin) % wHOURS) + 4;

  uchar ibDig;
  for (ibDig=ibDigMin; ibDig<=ibDigMax; ibDig++)
  {
    LoadCurrDigital(ibDig);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);

      if (CompareCurrPrevLines(ibDig, c) == 1)
      {
        mpboReadyCan[c] = true;
        if (fStopCan == true) mpcwStopCan[c] = wStop;
      }
    }
  }


  fLoadHou = 0;

  bHhrInc = 0;

  uint iwHhr;
  for (iwHhr=0; iwHhr<wHOURS; iwHhr++)
  {
    if (fKey == 1) { fKey = 0; Beep(); }
    if ((iwHhr % 0x10) == 0) ShowPercent((ulong)100*iwHhr/(wHOURS-1));
    if ((iwHhr % 0x10) == 0) NexttimeMnt();

    iwDigHou = (wHOURS + iwHardHou - iwHhr - bHhrInc) % wHOURS;


    if (iwDigHou == wHhrMax) fLoadHou = 1;

    if (fLoadHou == 1)
    {
      LoadImpHouSpec(iwDigHou,1);

      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        if (mpboReadyCan[c] == true)
        {
          mpwImpHouCanSpec[c] = ((fStopCan == true) ? 0xFFFF : 0);
        }
      }

      SaveImpHouSpec(1,iwDigHou);
    }

    if (iwDigHou == wHhrMin) fLoadHou = 0;
  }

  return Recalc(1,1);
}

