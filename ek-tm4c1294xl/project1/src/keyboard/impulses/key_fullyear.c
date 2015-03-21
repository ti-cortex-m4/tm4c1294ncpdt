/*------------------------------------------------------------------------------
KEY_FULLYEAR.C

 ѕросмотр канальных и групповых величин по мес€цам года
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_realtime.h"
#include        "../../memory/mem_digitals.h"
#include        "../../memory/mem_energy.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../realtime/realtime.h"
#include        "../../devices/automatic2.h"
#include        "../../digitals/digitals.h"
#include        "../../digitals/digitals_messages.h"
#include        "../../serial/ports.h"
#include        "../../serial/modems.h"
#include        "../../engine.h"
#include        "../../energy.h"
#include        "../../energy2.h"
#include        "../../time/timedate_display.h"



//                                           0123456789ABCDEF
static char const       szCntCanOnBegin[] = "на начало мес€ца",
                        szCntCanOnEnd[]   = "на конец мес€ца ",
                        szCntCanNoData[]  = "  нет данных !  ",
                        szCntCanBuff[]    = "   из буфера    ",
                        szCntCanType1[]   = "  с дозапросом  "/*,
                        szCntCanType2[]   = " пр€мого опроса "*/;

static char const       *pszEngFull[]    = { szEnergy, szBeta, szFull,   "" },
                        *pszEngTops[]    = { szEnergy, szBeta, szTops,   "" },
                        *pszEngMid[]     = { szEnergy, szBeta, szMid,    "" },
                        *pszEngBottom[]  = { szEnergy, szBeta, szBottom, "" },

                        *pszCntCanYear1[]  = { szCountersB, szBeta, szCntCanOnEnd,   "" },
                        *pszCntCanYear10[] = { szCountersB, szBeta, szCntCanOnBegin, "" },
                        *pszCntCanYear2[]  = { szCountersB, szBeta, szCntCanOnEnd,   szCntCanBuff, szCntCanType1, "" },
                        *pszCntCanYear20[] = { szCountersB, szBeta, szCntCanOnBegin, szCntCanBuff, szCntCanType1, "" }/*,
                        *pszCntCanYear3[]  = { szCountersB, szBeta, szCntCanOnEnd,   szCntCanBuff, szCntCanType2, "" }*/;


uchar   GetMaxItem(item  it);
void    ShowItemName(item  it);



void    ShowGrpFullYearEng(uchar  bMask)
{
  LoadImpMon( ibY );
  ShowReal(GetGrpImp2RealEng(mpimMonCan[ PrevSoftMon() ],ibX,bMask));
}



void    ShowFullYear(void)   
{
  switch (bProgram)
  {
    case bGET_ENGGRPYEAR_ABCD:  ShowGrpFullYearEng(0x0F);  break;
    case bGET_ENGGRPYEAR_CD:    ShowGrpFullYearEng(0x0C);  break;
    case bGET_ENGGRPYEAR_B:     ShowGrpFullYearEng(0x02);  break;
    case bGET_ENGGRPYEAR_A:     ShowGrpFullYearEng(0x01);  break;

    case bGET_CNTCANYEAR1:     
      if (GetDigitalDevice(ibX) == 0)
        (ReadCntMonCan(ibY,ibX) == 1) ? ShowReal(reBuffA) : Error();
//      else if (CheckDirectCnt2(ibX,ibY)) {
//        ShowDirectCnt(ibX);
//      }
      else
      {
        LoadCurrDigital(ibX);
        ibPort = diCurr.ibPort;

        if (LoadConnect(ibX) == 0) break;
        Clear();

        LoadSlide(pszCntCanYear1);

        if (mpboEnblCan[ibX] == FALSE)
          ShowLo(szBlocking); 
        else 
        {
//          if (GetDigitalDevice(ibX) != 6)
            (ReadCntMonCan(ibY,ibX) == 1) ? ShowReal(reBuffA) : Error();
//          else
//            (ReadCntMonCanFCurr(ibY,ibX) == 1) ? ShowCntMonCanF2() : Error();
        }

        SaveConnect();
      }
      break;

    case bGET_CNTCANYEAR10:     
      ibZ = (12+ibY-1)%12;
      if (ibY == tiCurr.bMonth)
        ShowLo(szCntCanNoData);
      else if (GetDigitalDevice(ibX) == 0)
        (ReadCntMonCan(ibZ,ibX) == 1) ? ShowReal(reBuffA) : Error();
//      else if (CheckDirectCnt2(ibX,ibY)) {
//        ShowDirectCnt(ibX);
//      }
      else
      {
        LoadCurrDigital(ibX);
        ibPort = diCurr.ibPort;

        if (LoadConnect(ibX) == 0) break;
        Clear();

        LoadSlide(pszCntCanYear10);

        if (mpboEnblCan[ibX] == FALSE)
          ShowLo(szBlocking); 
        else 
        {
//          if (GetDigitalDevice(ibX) != 6)
            (ReadCntMonCan(ibZ,ibX) == 1) ? ShowReal(reBuffA) : Error();
//          else
//            (ReadCntMonCanFCurr(ibZ,ibX) == 1) ? ShowCntMonCanF2() : Error();
        }

        SaveConnect();
      }
      break;

    case bGET_CNTCANYEAR2:  
//      ShowExtended4(ibX,ibY);
      break;

    case bGET_CNTCANYEAR20:     
      ibZ = (12+ibY-1)%12;
      if (ibY == tiCurr.bMonth)
        ShowLo(szCntCanNoData);
//      else
//        ShowExtended4(ibX,ibY);
      break;
  }

  sprintf(szLo+14,"%2u",ibX+1);
}



void    key_GetFullYear(item  it)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;

      Month();
      strcpy(szBeta, szOn12Months); 

      InitConnectKey();
      ibZ = 0;

      switch (bProgram)
      {
        case bGET_ENGGRPYEAR_ABCD:  LoadSlide(pszEngFull);    break;
        case bGET_ENGGRPYEAR_CD:    LoadSlide(pszEngTops);    break;
        case bGET_ENGGRPYEAR_B:     LoadSlide(pszEngMid);     break;
        case bGET_ENGGRPYEAR_A:     LoadSlide(pszEngBottom);  break;

        case bGET_CNTCANYEAR1:      LoadSlide(pszCntCanYear1);  break;
        case bGET_CNTCANYEAR10:     LoadSlide(pszCntCanYear10); break;
        case bGET_CNTCANYEAR2:      LoadSlide(pszCntCanYear2);  break;
        case bGET_CNTCANYEAR20:     LoadSlide(pszCntCanYear20); break;
      }
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_INPUT2;
      ShowItemName(it);

      ibY = ibHardMon;

      LoadBetaMonth(ibY);
      ShowSlide(szBeta);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibY = GetCharLo(10,11)-1) < 12)
      {
        enKeyboard = KBD_INPUT2;
        ShowItemName(it);

        LoadBetaMonth(ibY);
        ShowSlide(szBeta);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT2)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowFullYear();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibX = GetCharLo(10,11)-1) < GetMaxItem(it))
      {
        enKeyboard = KBD_POSTENTER;

        ShowFullYear();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      ibZ = 0;
      if (++ibX >= GetMaxItem(it)) ibX = 0;

      ShowFullYear();
    }
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(10,11);
    }
    else 
    if ((enKeyboard == KBD_POSTENTER) && (bKey == 0))
    {
      ibZ = (ibZ + 1) % 2; 
      ShowFullYear();
    }
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)  
    {
      ibZ = 0;
      if (ibY > 0) ibY--; else ibY = 12-1;

      LoadBetaMonth(ibY);
      ShowFullYear();
      ShowSlide(szBeta);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)  
    {
      ibZ = 0;
      if (ibX > 0) ibX--; else ibX = GetMaxItem(it)-1;

      ShowFullYear();
    }
  }
}


/*
void    auto_GetFullyear(void)
{
  if (enKeyboard == KBD_POSTENTER)
    ShowFullyear();
}
*/








