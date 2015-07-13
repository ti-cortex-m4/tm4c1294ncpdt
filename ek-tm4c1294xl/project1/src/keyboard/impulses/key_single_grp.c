/*------------------------------------------------------------------------------
KEY_SINGLE_GRP.C

 Просмотр канальных и групповых величин (старый вариант)
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_energy.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "../../realtime/realtime.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_messages.h"
#include "../../serial/ports.h"
#include "../../serial/modems.h"
#include "../../kernel/array_mnt.h"
#include "../../energy.h"
#include "../../energy2.h"
#include "../../energy4.h"
#include "../../impulses/max_power.h"
#include "../../sensors/automatic2.h"
#include "../../time/timedate.h"
#include "../../time/timedate_display.h"


//                                             0123456789ABCDEF
static char const       szTimeDate[]        = "Время и дата    ";

static char const      *pszEngCurrMin[]     = { szPower, szMiddle, szCurrMnt,  "" },
                       *pszCountersB[]      = { szCounters, szForDigital, "" },

                       *pszPowPrevHou[]     = { szPower, szMiddle, szPrevHou, "" },
                       *pszPowCurrHou[]     = { szPower, szMiddle, szCurrHou, "" },

                       *pszPowDayPrevABCD[] = { szPower, szMaximum, szDayPrev, szFull,    "" },
                       *pszPowDayPrevC[]    = { szPower, szMaximum, szDayPrev, szMorning, "" },
                       *pszPowDayPrevD[]    = { szPower, szMaximum, szDayPrev, szEvening, "" },

                       *pszPowDayCurrABCD[] = { szPower, szMaximum, szDayCurr, szFull,    "" },
                       *pszPowDayCurrC[]    = { szPower, szMaximum, szDayCurr, szMorning, "" },
                       *pszPowDayCurrD[]    = { szPower, szMaximum, szDayCurr, szEvening, "" },

                       *pszPowMonPrevABCD[] = { szPower, szMaximum, szMonPrev, szFull,    "" },
                       *pszPowMonPrevC[]    = { szPower, szMaximum, szMonPrev, szMorning, "" },
                       *pszPowMonPrevD[]    = { szPower, szMaximum, szMonPrev, szEvening, "" },

                       *pszPowMonCurrABCD[] = { szPower, szMaximum, szMonCurr, szFull,    "" },
                       *pszPowMonCurrC[]    = { szPower, szMaximum, szMonCurr, szMorning, "" },
                       *pszPowMonCurrD[]    = { szPower, szMaximum, szMonCurr, szEvening, "" },

                       *pszEngDayPrevABCD[] = { szEnergy, szDayPrev, szFull,   "" },
                       *pszEngDayPrevCD[]   = { szEnergy, szDayPrev, szTops,   "" },
                       *pszEngDayPrevB[]    = { szEnergy, szDayPrev, szMid,    "" },
                       *pszEngDayPrevA[]    = { szEnergy, szDayPrev, szBottom, "" },

                       *pszEngDayCurrABCD[] = { szEnergy, szDayCurr, szFull,   "" },
                       *pszEngDayCurrCD[]   = { szEnergy, szDayCurr, szTops,   "" },
                       *pszEngDayCurrB[]    = { szEnergy, szDayCurr, szMid,    "" },
                       *pszEngDayCurrA[]    = { szEnergy, szDayCurr, szBottom, "" },

                       *pszEngMonPrevABCD[] = { szEnergy, szMonPrev, szFull,   "" },
                       *pszEngMonPrevCD[]   = { szEnergy, szMonPrev, szTops,   "" },
                       *pszEngMonPrevB[]    = { szEnergy, szMonPrev, szMid,    "" },
                       *pszEngMonPrevA[]    = { szEnergy, szMonPrev, szBottom, "" },

                       *pszEngMonCurrABCD[] = { szEnergy, szMonCurr, szFull,   "" },
                       *pszEngMonCurrCD[]   = { szEnergy, szMonCurr, szTops,   "" },
                       *pszEngMonCurrB[]    = { szEnergy, szMonCurr, szMid,    "" },
                       *pszEngMonCurrA[]    = { szEnergy, szMonCurr, szBottom, "" };



static uchar            ibGrp, ibY, ibTrf;



static void ShowGrpDayMaxPow(void)
{
time  ti;

  ti = GetGrpMaxPowTime(mppoDayGrp[ PrevSoftDay() ],ibGrp,ibTrf);

  switch (ibY)
  {
    case 0:  ShowFloat(GetGrpMaxPowReal(mppoDayGrp[ PrevSoftDay() ],ibGrp,ibTrf));  break;
    case 1:  ShowTime(ti);  break;
    case 2:  ShowDate(ti);  break;
  }
}


static void ShowGrpMonMaxPow(void)
{
time  ti;

  ti = GetGrpMaxPowTime(mppoMonGrp[ PrevSoftMon() ],ibGrp,ibTrf);

  switch (ibY)
  {
    case 0:  ShowFloat(GetGrpMaxPowReal(mppoMonGrp[ PrevSoftMon() ],ibGrp,ibTrf));  break;
    case 1:  ShowTime(ti);  break;
    case 2:  ShowDate(ti);  break;
  }
}



static void ShowGrpDayPrevEng(uchar  bMask)
{
  LoadImpDay( PrevHardDay() );
  ShowDouble(GetGrpImp2DoubleEng(mpimDayCan[ PrevSoftDay() ],ibGrp,bMask));
}


static void ShowGrpDayCurrEng(uchar  bMask)
{
  LoadImpDay( ibHardDay );
  ShowDouble(GetGrpImp2DoubleEng(mpimDayCan[ PrevSoftDay() ],ibGrp,bMask));
}


static void ShowGrpMonPrevEng(uchar  bMask)
{
  LoadImpMon( PrevHardMon() );
  ShowDouble(GetGrpImp2DoubleEng(mpimMonCan[ PrevSoftMon() ],ibGrp,bMask));
}


static void ShowGrpMonCurrEng(uchar  bMask)
{
  LoadImpMon( ibHardMon );
  ShowDouble(GetGrpImp2DoubleEng(mpimMonCan[ PrevSoftMon() ],ibGrp,bMask));
}



static void Show(void)
{
  switch (wProgram)
  {
    case bGET_POWGRPCURRMNT:
      LoadImpMnt( PrevHardMnt() );
      ShowFloat(GetGrpMntInt2Real(mpwImpMntCan[ PrevSoftMnt() ],ibGrp,20));
      break;

    case bGET_IMPCANCURRMNT:
      ShowInt(mpwImpMntCan[ ibSoftMnt ][ibGrp]);
      break;

    case bGET_POWGRPPREVHOU:      
      LoadImpHou( PrevHardHou() );
      ShowFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ],ibGrp,2));
      break;

    case bGET_POWGRPCURRHOU:
      ShowFloat(GetPowGrpHouCurr(ibGrp,2));
      break;

    case bGET_POWGRPDAYPREV_ABCD:  
      LoadPowDay( PrevHardDay() );
      ibTrf = GetGrpMaxPowIndex(mppoDayGrp[ PrevSoftDay() ],ibGrp);
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPDAYPREV_C:     
      LoadPowDay( PrevHardDay() );   
      ibTrf = 2;        
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPDAYPREV_D:     
      LoadPowDay( PrevHardDay() );
      ibTrf = 3;  
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPDAYCURR_ABCD:
      LoadPowDay(ibHardDay);
      ibTrf = GetGrpMaxPowIndex(mppoDayGrp[ PrevSoftDay() ],ibGrp);
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPDAYCURR_C:     
      LoadPowDay(ibHardDay);
      ibTrf = 2;
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPDAYCURR_D:     
      LoadPowDay(ibHardDay);
      ibTrf = 3;
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPMONPREV_ABCD: 
      LoadPowMon( PrevHardMon() ); 
      ibTrf = GetGrpMaxPowIndex(mppoMonGrp[ PrevSoftMon() ],ibGrp);  
      ShowGrpMonMaxPow();
      break;

    case bGET_POWGRPMONPREV_C:     
      LoadPowMon( PrevHardMon() ); 
      ibTrf = 2;
      ShowGrpMonMaxPow();
      break;

    case bGET_POWGRPMONPREV_D:     
      LoadPowMon( PrevHardMon() ); 
      ibTrf = 3;
      ShowGrpMonMaxPow();
      break;

    case bGET_POWGRPMONCURR_ABCD: 
      LoadPowMon(ibHardMon);  
      ibTrf = GetGrpMaxPowIndex(mppoMonGrp[ PrevSoftMon() ],ibGrp);  
      ShowGrpMonMaxPow();
      break;

    case bGET_POWGRPMONCURR_C:   
      LoadPowMon(ibHardMon);
      ibTrf = 2;
      ShowGrpMonMaxPow();
      break;

    case bGET_POWGRPMONCURR_D: 
      LoadPowMon(ibHardMon);
      ibTrf = 3;
      ShowGrpMonMaxPow();
      break;

    case bGET_ENGGRPDAYPREV_ABCD:  ShowGrpDayPrevEng(0x0F);  break;
    case bGET_ENGGRPDAYPREV_CD:    ShowGrpDayPrevEng(0x0C);  break;
    case bGET_ENGGRPDAYPREV_B:     ShowGrpDayPrevEng(0x02);  break;
    case bGET_ENGGRPDAYPREV_A:     ShowGrpDayPrevEng(0x01);  break;

    case bGET_ENGGRPDAYCURR_ABCD:  ShowGrpDayCurrEng(0x0F);  break;
    case bGET_ENGGRPDAYCURR_CD:    ShowGrpDayCurrEng(0x0C);  break;
    case bGET_ENGGRPDAYCURR_B:     ShowGrpDayCurrEng(0x02);  break;
    case bGET_ENGGRPDAYCURR_A:     ShowGrpDayCurrEng(0x01);  break;

    case bGET_ENGGRPMONPREV_ABCD:  ShowGrpMonPrevEng(0x0F);  break;
    case bGET_ENGGRPMONPREV_CD:    ShowGrpMonPrevEng(0x0C);  break;
    case bGET_ENGGRPMONPREV_B:     ShowGrpMonPrevEng(0x02);  break;
    case bGET_ENGGRPMONPREV_A:     ShowGrpMonPrevEng(0x01);  break;

    case bGET_ENGGRPMONCURR_ABCD:  ShowGrpMonCurrEng(0x0F);  break;
    case bGET_ENGGRPMONCURR_CD:    ShowGrpMonCurrEng(0x0C);  break;
    case bGET_ENGGRPMONCURR_B:     ShowGrpMonCurrEng(0x02);  break;
    case bGET_ENGGRPMONCURR_A:     ShowGrpMonCurrEng(0x01);  break; 
  }      

  sprintf(szLo+14,"%2u",ibGrp+1);
}



void    key_GetSingleGrp(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Group();

      InitConnectKey();

      switch (wProgram)
      {
        case bGET_IMPCANCURRMNT:       ShowHi(szImpulseA);            break;
        case bGET_POWGRPCURRMNT:       LoadSlide(pszEngCurrMin);      break;

        case bGET_CNTCURR_10:          ShowHi(szCounters);            break;
        case bGET_CNTCURR_110:         LoadSlide(pszCountersB);       break;

        case bGET_READTIMEDATE1:     
        case bGET_READTIMEDATE2:       ShowHi(szTimeDate);            break;

        case bGET_POWGRPPREVHOU:       LoadSlide(pszPowPrevHou);      break;
        case bGET_POWGRPCURRHOU:       LoadSlide(pszPowCurrHou);      break;

        case bGET_POWGRPDAYPREV_ABCD:  LoadSlide(pszPowDayPrevABCD);  break;
        case bGET_POWGRPDAYPREV_C:     LoadSlide(pszPowDayPrevC);     break;
        case bGET_POWGRPDAYPREV_D:     LoadSlide(pszPowDayPrevD);     break;

        case bGET_POWGRPDAYCURR_ABCD:  LoadSlide(pszPowDayCurrABCD);  break;
        case bGET_POWGRPDAYCURR_C:     LoadSlide(pszPowDayCurrC);     break;
        case bGET_POWGRPDAYCURR_D:     LoadSlide(pszPowDayCurrD);     break;

        case bGET_POWGRPMONPREV_ABCD:  LoadSlide(pszPowMonPrevABCD);  break;
        case bGET_POWGRPMONPREV_C:     LoadSlide(pszPowMonPrevC);     break;
        case bGET_POWGRPMONPREV_D:     LoadSlide(pszPowMonPrevD);     break;
   
        case bGET_POWGRPMONCURR_ABCD:  LoadSlide(pszPowMonCurrABCD);  break;
        case bGET_POWGRPMONCURR_C:     LoadSlide(pszPowMonCurrC);     break;
        case bGET_POWGRPMONCURR_D:     LoadSlide(pszPowMonCurrD);     break;

        case bGET_ENGGRPDAYPREV_ABCD:  LoadSlide(pszEngDayPrevABCD);  break;
        case bGET_ENGGRPDAYPREV_CD:    LoadSlide(pszEngDayPrevCD);    break;
        case bGET_ENGGRPDAYPREV_B:     LoadSlide(pszEngDayPrevB);     break;
        case bGET_ENGGRPDAYPREV_A:     LoadSlide(pszEngDayPrevA);     break;

        case bGET_ENGGRPDAYCURR_ABCD:  LoadSlide(pszEngDayCurrABCD);  break;
        case bGET_ENGGRPDAYCURR_CD:    LoadSlide(pszEngDayCurrCD);    break;
        case bGET_ENGGRPDAYCURR_B:     LoadSlide(pszEngDayCurrB);     break;
        case bGET_ENGGRPDAYCURR_A:     LoadSlide(pszEngDayCurrA);     break;

        case bGET_ENGGRPMONPREV_ABCD:  LoadSlide(pszEngMonPrevABCD);  break;
        case bGET_ENGGRPMONPREV_CD:    LoadSlide(pszEngMonPrevCD);    break;
        case bGET_ENGGRPMONPREV_B:     LoadSlide(pszEngMonPrevB);     break;
        case bGET_ENGGRPMONPREV_A:     LoadSlide(pszEngMonPrevA);     break;

        case bGET_ENGGRPMONCURR_ABCD:  LoadSlide(pszEngMonCurrABCD);  break;
        case bGET_ENGGRPMONCURR_CD:    LoadSlide(pszEngMonCurrCD);    break;
        case bGET_ENGGRPMONCURR_B:     LoadSlide(pszEngMonCurrB);     break;
        case bGET_ENGGRPMONCURR_A:     LoadSlide(pszEngMonCurrA);     break; 
      }      
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ibGrp = 0;
      ibY = 0;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibGrp = GetCharLo(10,11) - 1) < bGROUPS)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        ibY = 0;
        Show();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibGrp >= bGROUPS)
        ibGrp = 0;

      ibY = 0;
      Show();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibY >= 3) 
        ibY = 0;

      Show();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibGrp > 0) 
        ibGrp--;
      else         
        ibGrp = bGROUPS - 1;

      ibY = 0;
      Show();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}



void    auto_GetSingleGrp(void)
{
  if (enKeyboard == KBD_POSTENTER)
    Show();
}
