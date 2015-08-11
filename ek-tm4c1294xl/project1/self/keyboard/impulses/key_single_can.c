/*------------------------------------------------------------------------------
KEY_SINGLE_CAN.C

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
static char const       szTimeDate[]        = "Время и дата    ",
                        szNone[]            = "      нет    ";

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



static uchar            ibCan;



static void ShowModemReadCntCurrCan(void)
{
  if (GetDigitalDevice(ibCan) == 0)
    ShowFloat(GetCntCurrImp(ibCan));
  else
  {
    LoadCurrDigital(ibCan);
    ibPort = diCurr.ibPort;

    if (LoadConnect(ibCan) == 0) return;
    Clear();

    if (mpboEnblCan[ibCan] == false)
      ShowLo(szBlocked);
    else
    {
      double2 db2 = ReadCntCurrCan(ibCan);
      (db2.fValid) ? ShowDouble(db2.dbValue) : Error();
    }

    SaveConnect();
  }
}


static void ShowModemReadTimeCan(bool  fShowTimeDate)
{
  ShowHi(szTimeDate);

  if (GetDigitalDevice(ibCan) == 0)
    ShowLo(szNone);
  else
  {
    LoadCurrDigital(ibCan);
    ibPort = diCurr.ibPort;

    if (LoadConnect(ibCan) == 0) return;
    Clear();

    if (mpboEnblCan[ibCan] == false)
    {
      sprintf(szHi+14,"%2u",ibCan+1);
      ShowLo(szBlocked);
    }
    else
    {
      time2 ti2 = ReadTimeCan(ibCan);
      if (ti2.fValid)
      {
        sprintf(szHi+14,"%2u",ibCan+1);
        Clear();
        (fShowTimeDate) ? ShowTimeDate(ti2.tiValue) : ShowDeltaTime(ti2.tiValue);
      }
      else Error();
    }

    SaveConnect();
  }
}



static void Show(void)
{
  switch (wProgram)
  {
    case bGET_CNTCURR_10:
      ShowModemReadCntCurrCan(); 
      break;

    case bGET_CNTCURR_110:
      ShowModemReadCntCurrCan(); 
      break;

    case bGET_IMPCANCURRMNT:
      ShowInt(mpwImpMntCan[ ibSoftMnt ][ibCan]);
      break;
  }      

  sprintf(szLo+14,"%2u",ibCan+1);

  switch (wProgram)
  {
    case bGET_READTIMEDATE1:  ShowModemReadTimeCan(true);  break;
    case bGET_READTIMEDATE2:  ShowModemReadTimeCan(false);  break;
  }
}



void    key_GetSingleCan(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Canal();

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

      ibCan = 0;
      ibY = 0;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibCan = GetCharLo(10,11) - 1) < bCANALS)
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
      if (++ibCan >= bCANALS)
        ibCan = 0;

      ibY = 0;
      Show();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibCan > 0) 
        ibCan--;
      else         
        ibCan = bCANALS - 1;

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



void    auto_GetSingleCan(void)
{
  if (enKeyboard == KBD_POSTENTER)
    Show();
}
