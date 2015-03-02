/*------------------------------------------------------------------------------
KEY_SINGLE2.C

 Просмотр канальных и групповых величин (новый вариант)
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_realtime.h"
#include        "../../memory/mem_energy.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../realtime/realtime.h"
#include        "../../energy.h"
#include        "../../energy2.h"
#include        "../../energy4.h"



static char const      *pszEngCanCurrMin[]     = { szPower, szOnCanals, szMiddle, szCurrMnt,  "" },

                       *pszPowCanPrevHou[]     = { szPower, szOnCanals, szMiddle, szPrevHou, "" },
                       *pszPowCanCurrHou[]     = { szPower, szOnCanals, szMiddle, szCurrHou, "" },

                       *pszEngCanDayPrevABCD[] = { szEnergy, szOnCanals, szDayPrev, szFull,   "" },
                       *pszEngCanDayPrevCD[]   = { szEnergy, szOnCanals, szDayPrev, szTops,   "" },
                       *pszEngCanDayPrevB[]    = { szEnergy, szOnCanals, szDayPrev, szMid,    "" },
                       *pszEngCanDayPrevA[]    = { szEnergy, szOnCanals, szDayPrev, szBottom, "" },

                       *pszEngCanDayCurrABCD[] = { szEnergy, szOnCanals, szDayCurr, szFull,   "" },
                       *pszEngCanDayCurrCD[]   = { szEnergy, szOnCanals, szDayCurr, szTops,   "" },
                       *pszEngCanDayCurrB[]    = { szEnergy, szOnCanals, szDayCurr, szMid,    "" },
                       *pszEngCanDayCurrA[]    = { szEnergy, szOnCanals, szDayCurr, szBottom, "" },

                       *pszEngCanMonPrevABCD[] = { szEnergy, szOnCanals, szMonPrev, szFull,   "" },
                       *pszEngCanMonPrevCD[]   = { szEnergy, szOnCanals, szMonPrev, szTops,   "" },
                       *pszEngCanMonPrevB[]    = { szEnergy, szOnCanals, szMonPrev, szMid,    "" },
                       *pszEngCanMonPrevA[]    = { szEnergy, szOnCanals, szMonPrev, szBottom, "" },

                       *pszEngCanMonCurrABCD[] = { szEnergy, szOnCanals, szMonCurr, szFull,   "" },
                       *pszEngCanMonCurrCD[]   = { szEnergy, szOnCanals, szMonCurr, szTops,   "" },
                       *pszEngCanMonCurrB[]    = { szEnergy, szOnCanals, szMonCurr, szMid,    "" },
                       *pszEngCanMonCurrA[]    = { szEnergy, szOnCanals, szMonCurr, szBottom, "" };



void    ShowCanDayPrevEng(uchar  bMask)
{
  LoadImpDay( PrevHardDay() );
  ShowReal(GetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibX,bMask));
}


void    ShowCanDayCurrEng(uchar  bMask)
{
  LoadImpDay( ibHardDay );
  ShowReal(GetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibX,bMask));
}


void    ShowCanMonPrevEng(uchar  bMask)
{
  LoadImpMon( PrevHardMon() );
  ShowReal(GetCanImp2RealEng(mpimMonCan[ PrevSoftMon() ],ibX,bMask));
}


void    ShowCanMonCurrEng(uchar  bMask)
{
  LoadImpMon( ibHardMon );
  ShowReal(GetCanImp2RealEng(mpimMonCan[ PrevSoftMon() ],ibX,bMask));
}



void    ShowSingle2(void)
{
  switch (bProgram)
  {
    case bGET_POWCANCURRMNT:
    	LoadImpMnt( PrevHardMnt() );
      ShowReal(GetCanMntInt2Real(mpwImpMntCan[ PrevSoftMnt() ],ibX,20));
      break;

    case bGET_POWCANPREVHOU:      
      LoadImpHou( PrevHardHou() );
      ShowReal(GetCanHouInt2Real(mpwImpHouCan[ PrevSoftHou() ],ibX,2));
      break;

    case bGET_POWCANCURRHOU:
      ShowReal(GetPowCanHouCurr(ibX,2));
      break;

    case bGET_ENGCANDAYPREV_ABCD:  ShowCanDayPrevEng(0x0F);  break;
    case bGET_ENGCANDAYPREV_CD:    ShowCanDayPrevEng(0x0C);  break;
    case bGET_ENGCANDAYPREV_B:     ShowCanDayPrevEng(0x02);  break;
    case bGET_ENGCANDAYPREV_A:     ShowCanDayPrevEng(0x01);  break;

    case bGET_ENGCANDAYCURR_ABCD:  ShowCanDayCurrEng(0x0F);  break;
    case bGET_ENGCANDAYCURR_CD:    ShowCanDayCurrEng(0x0C);  break;
    case bGET_ENGCANDAYCURR_B:     ShowCanDayCurrEng(0x02);  break;
    case bGET_ENGCANDAYCURR_A:     ShowCanDayCurrEng(0x01);  break;

    case bGET_ENGCANMONPREV_ABCD:  ShowCanMonPrevEng(0x0F);  break;
    case bGET_ENGCANMONPREV_CD:    ShowCanMonPrevEng(0x0C);  break;
    case bGET_ENGCANMONPREV_B:     ShowCanMonPrevEng(0x02);  break;
    case bGET_ENGCANMONPREV_A:     ShowCanMonPrevEng(0x01);  break;

    case bGET_ENGCANMONCURR_ABCD:  ShowCanMonCurrEng(0x0F);  break;
    case bGET_ENGCANMONCURR_CD:    ShowCanMonCurrEng(0x0C);  break;
    case bGET_ENGCANMONCURR_B:     ShowCanMonCurrEng(0x02);  break;
    case bGET_ENGCANMONCURR_A:     ShowCanMonCurrEng(0x01);  break; 
  }      

  sprintf(szLo+14,"%2u",ibX+1);
}



void    key_GetSingle2(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Canal();

      switch (bProgram)
      {
        case bGET_POWCANCURRMNT:       LoadSlide(pszEngCanCurrMin);      break;

        case bGET_POWCANPREVHOU:       LoadSlide(pszPowCanPrevHou);      break;
        case bGET_POWCANCURRHOU:       LoadSlide(pszPowCanCurrHou);      break;

        case bGET_ENGCANDAYPREV_ABCD:  LoadSlide(pszEngCanDayPrevABCD);  break;
        case bGET_ENGCANDAYPREV_CD:    LoadSlide(pszEngCanDayPrevCD);    break;
        case bGET_ENGCANDAYPREV_B:     LoadSlide(pszEngCanDayPrevB);     break;
        case bGET_ENGCANDAYPREV_A:     LoadSlide(pszEngCanDayPrevA);     break;

        case bGET_ENGCANDAYCURR_ABCD:  LoadSlide(pszEngCanDayCurrABCD);  break;
        case bGET_ENGCANDAYCURR_CD:    LoadSlide(pszEngCanDayCurrCD);    break;
        case bGET_ENGCANDAYCURR_B:     LoadSlide(pszEngCanDayCurrB);     break;
        case bGET_ENGCANDAYCURR_A:     LoadSlide(pszEngCanDayCurrA);     break;

        case bGET_ENGCANMONPREV_ABCD:  LoadSlide(pszEngCanMonPrevABCD);  break;
        case bGET_ENGCANMONPREV_CD:    LoadSlide(pszEngCanMonPrevCD);    break;
        case bGET_ENGCANMONPREV_B:     LoadSlide(pszEngCanMonPrevB);     break;
        case bGET_ENGCANMONPREV_A:     LoadSlide(pszEngCanMonPrevA);     break;

        case bGET_ENGCANMONCURR_ABCD:  LoadSlide(pszEngCanMonCurrABCD);  break;
        case bGET_ENGCANMONCURR_CD:    LoadSlide(pszEngCanMonCurrCD);    break;
        case bGET_ENGCANMONCURR_B:     LoadSlide(pszEngCanMonCurrB);     break;
        case bGET_ENGCANMONCURR_A:     LoadSlide(pszEngCanMonCurrA);     break; 
      }      
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ibX = 0;
      ShowSingle2();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        ShowSingle2();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;

      ShowSingle2();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibX > 0) ibX--; else ibX = bCANALS-1;

      ShowSingle2();
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



void    auto_GetSingle2(void)
{
  if (enKeyboard == KBD_POSTENTER)
    ShowSingle2();
}







