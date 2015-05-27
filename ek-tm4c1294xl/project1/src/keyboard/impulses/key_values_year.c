/*------------------------------------------------------------------------------
KEY_VALUES_YEAR.C

 ѕросмотр канальных и групповых величин по мес€цам года
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_energy.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "../../realtime/realtime.h"
#include "../../sensors/automatic2.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_messages.h"
#include "../../serial/ports.h"
#include "../../digitals/extended/extended_4.h"
#include "../../digitals/extended/extended_4_in.h"
#include "../../digitals/extended/extended_4_show.h"
#include "../../digitals/extended/extended_6.h"
#include "../../serial/modems.h"
#include "../../engine.h"
#include "../../energy.h"
#include "../../energy2.h"
#include "../../time/timedate_display.h"



//                                           0123456789ABCDEF
static char const       szCntCanOnBegin[] = "на начало мес€ца",
                        szCntCanOnEnd[]   = "на конец мес€ца ",
                        szCntCanNoData[]  = "  нет данных !  ",
                        szCntCanBuff[]    = "   из буфера    ",
                        szCntCanType1[]   = "  с дозапросом  ",
                        szCntCanType2[]   = " пр€мого опроса ",
                        szBadMode[]       = "*  нет данных   ";

static char const       *pszEngFull[]    = { szEnergy, szBeta, szFull,   "" },
                        *pszEngTops[]    = { szEnergy, szBeta, szTops,   "" },
                        *pszEngMid[]     = { szEnergy, szBeta, szMid,    "" },
                        *pszEngBottom[]  = { szEnergy, szBeta, szBottom, "" },

                        *pszCntCanYear1[]  = { szCountersB, szBeta, szCntCanOnEnd,   "" },
                        *pszCntCanYear10[] = { szCountersB, szBeta, szCntCanOnBegin, "" },
                        *pszCntCanYear2[]  = { szCountersB, szBeta, szCntCanOnEnd,   szCntCanBuff, szCntCanType1, "" },
                        *pszCntCanYear20[] = { szCountersB, szBeta, szCntCanOnBegin, szCntCanBuff, szCntCanType1, "" },
                        *pszCntCanYear3[]  = { szCountersB, szBeta, szCntCanOnEnd,   szCntCanBuff, szCntCanType2, "" };


uchar   GetMaxItem(item  it);
void    ShowItemName(item  it);


static uchar            ibCan, ibMon, ibZ;



void    ShowGrpFullYearEng(uchar  bMask)
{
  LoadImpMon( ibMon );
  ShowDouble(GetGrpImp2DoubleEng(mpimMonCan[ PrevSoftMon() ],ibCan,bMask));
}



void    ShowCntCanMon(void)   
{
  switch (wProgram)
  {
    case bGET_ENGGRPYEAR_ABCD:  ShowGrpFullYearEng(0x0F);  break;
    case bGET_ENGGRPYEAR_CD:    ShowGrpFullYearEng(0x0C);  break;
    case bGET_ENGGRPYEAR_B:     ShowGrpFullYearEng(0x02);  break;
    case bGET_ENGGRPYEAR_A:     ShowGrpFullYearEng(0x01);  break;

    case bGET_CNTCANYEAR1:     
      if (GetDigitalDevice(ibCan) == 0)
      {
        double2 db2 = ReadCntMonCan(ibMon,ibCan);
        (db2.fValid) ? ShowDouble(db2.dbValue) : Error();
      }
      else if (CheckDirectCnt2(ibCan,ibMon)) {
        ShowDirectCnt(ibCan);
      }
      else
      {
        LoadCurrDigital(ibCan);
        ibPort = diCurr.ibPort;

        if (LoadConnect(ibCan) == 0) break;
        Clear();

        LoadSlide(pszCntCanYear1);

        if (mpboEnblCan[ibCan] == FALSE)
          ShowLo(szBlocked); 
        else 
        {
          if (GetDigitalDevice(ibCan) != 6)
          {
            double2 db2 = ReadCntMonCan(ibMon,ibCan);
            (db2.fValid) ? ShowDouble(db2.dbValue) : Error();
          }
          else
          {
            (ReadCntMonCanF_Curr(ibMon,ibCan) == true) ? ShowCntMonCanF(ibZ == 0) : Error();
          }
        }

        SaveConnect();
      }
      break;

    case bGET_CNTCANYEAR10:     
      ibZ = (12+ibMon-1)%12;
      if (ibMon == tiCurr.bMonth)
        ShowLo(szCntCanNoData);
      else if (GetDigitalDevice(ibCan) == 0)
      {
        double2 db2 = ReadCntMonCan(ibZ,ibCan);
        (db2.fValid) ? ShowDouble(db2.dbValue) : Error();
      }
      else if (CheckDirectCnt2(ibCan,ibMon)) {
        ShowDirectCnt(ibCan);
      }
      else
      {
        LoadCurrDigital(ibCan);
        ibPort = diCurr.ibPort;

        if (LoadConnect(ibCan) == 0) break;
        Clear();

        LoadSlide(pszCntCanYear10);

        if (mpboEnblCan[ibCan] == FALSE)
          ShowLo(szBlocked); 
        else 
        {
          if (GetDigitalDevice(ibCan) != 6)
          {
            double2 db2 = ReadCntMonCan(ibZ,ibCan);
            (db2.fValid) ? ShowDouble(db2.dbValue) : Error();
          }
          else
            (ReadCntMonCanF_Curr(ibZ,ibCan) == true) ? ShowCntMonCanF(ibZ == 0) : Error();
        }

        SaveConnect();
      }
      break;

    case bGET_CNTCANYEAR2:  
      ShowExtended4(ibCan,ibMon,ibZ == 0);
      break;

    case bGET_CNTCANYEAR20:     
      ibZ = (12+ibMon-1)%12;
      if (ibMon == tiCurr.bMonth)
        ShowLo(szCntCanNoData);
      else
        ShowExtended4(ibCan,ibMon,ibZ == 0);
      break;
  }

  sprintf(szLo+14,"%2u",ibCan+1);
}



void    key_GetValuesYear(item  it)
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

      switch (wProgram)
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

      ibMon = ibHardMon;

      LoadBetaMonth(ibMon);
      ShowSlide(szBeta);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibMon = GetCharLo(10,11)-1) < 12)
      {
        enKeyboard = KBD_INPUT2;
        ShowItemName(it);

        LoadBetaMonth(ibMon);
        ShowSlide(szBeta);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT2)
    {
      enKeyboard = KBD_POSTENTER;

      ibCan = 0;
      ShowCntCanMon();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibCan = GetCharLo(10,11)-1) < GetMaxItem(it))
      {
        enKeyboard = KBD_POSTENTER;

        ShowCntCanMon();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      ibZ = 0;
      if (++ibCan >= GetMaxItem(it)) ibCan = 0;

      ShowCntCanMon();
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
      ShowCntCanMon();
    }
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)  
    {
      ibZ = 0;
      if (ibMon > 0) ibMon--; else ibMon = 12-1;

      LoadBetaMonth(ibMon);
      ShowCntCanMon();
      ShowSlide(szBeta);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)  
    {
      ibZ = 0;
      if (ibCan > 0) ibCan--; else ibCan = GetMaxItem(it)-1;

      ShowCntCanMon();
    }
  }
}



void    ShowCntCanMon6(void)
{
  if (GetDigitalDevice(ibCan) == 6)
    ShowLo(szBadMode);
  else
    ShowCntMonCan6(ibCan,ibMon);

  sprintf(szLo+14,"%2u",ibCan+1);
}



void    key_GetCntCanYear6(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;

      Month();
      strcpy(szBeta, szOn12Months);

      ibZ = 0;
      LoadSlide(pszCntCanYear3);
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_INPUT2;
      Canal();

      ibMon = ibHardMon;

      LoadBetaMonth(ibMon);
      ShowSlide(szBeta);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibMon = GetCharLo(10,11)-1) < 12)
      {
        enKeyboard = KBD_INPUT2;
        Canal();

        LoadBetaMonth(ibMon);
        ShowSlide(szBeta);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT2)
    {
      enKeyboard = KBD_POSTENTER;

      ibCan = 0;
      ShowCntCanMon6();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibCan = GetCharLo(10,11)-1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;

        ShowCntCanMon6();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      ibZ = 0;
      if (++ibCan >= bCANALS) ibCan = 0;

      ShowCntCanMon6();
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
      ibZ = ++ibZ % 2;
      ShowCntCanMon6();
    }
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      ibZ = 0;
      if (ibMon > 0) ibMon--; else ibMon = 12-1;

      LoadBetaMonth(ibMon);
      ShowCntCanMon6();
      ShowSlide(szBeta);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      ibZ = 0;
      if (ibCan > 0) ibCan--; else ibCan = bCANALS-1;

      ShowCntCanMon6();
    }
  }
}

