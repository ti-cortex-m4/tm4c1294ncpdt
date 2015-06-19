/*------------------------------------------------------------------------------
KEY_CNT_YEAR.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_realtime.h"
#include "../../sensors/automatic2.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_messages.h"
#include "../../serial/ports.h"
#include "../../digitals/extended/extended_4.h"
#include "../../digitals/extended/extended_4_in.h"
#include "../../digitals/extended/extended_4_show.h"
#include "../../digitals/extended/extended_6.h"
#include "../../digitals/extended/extended_6_show.h"
#include "../../serial/modems.h"
#include "../../time/timedate_display.h"
#include "key_cnt_year.h"



//                                           0123456789ABCDEF
static char const       szCntCanOnBegin[] = "на начало мес€ца",
                        szCntCanOnEnd[]   = "на конец мес€ца ",
                        szCntCanNoData[]  = "  нет данных !  ",
                        szCntCanBuff[]    = "   из буфера    ",
                        szCntCanType1[]   = "  с дозапросом  ",
                        szCntCanType2[]   = " пр€мого опроса ",
                        szBadMode[]       = "*  нет данных   ";

static char const       *pszCntCanYear1[]  = { szCountersB, szBeta, szCntCanOnEnd,   "" },
                        *pszCntCanYear10[] = { szCountersB, szBeta, szCntCanOnBegin, "" },
                        *pszCntCanYear2[]  = { szCountersB, szBeta, szCntCanOnEnd,   szCntCanBuff, szCntCanType1, "" },
                        *pszCntCanYear20[] = { szCountersB, szBeta, szCntCanOnBegin, szCntCanBuff, szCntCanType1, "" },
                        *pszCntCanYear3[]  = { szCountersB, szBeta, szCntCanOnEnd,   szCntCanBuff, szCntCanType2, "" };


static uchar            ibCan, ibMon, ibZ;



static void ShowCntCanMon(void)
{
  switch (wProgram)
  {
    case bGET_CNTCANYEAR1:     
      if (GetDigitalDevice(ibCan) == 0)
      {
        double2 db2 = ReadCntMonCan(ibMon,ibCan);
        (db2.fValid) ? ShowDouble(db2.dbValue) : Error();
      }
      else if (SupportedExtended6_CurrMon(ibCan,ibMon))
      {
        ShowExtended6(ibCan);
      }
      else
      {
        LoadCurrDigital(ibCan);
        ibPort = diCurr.ibPort;

        if (LoadConnect(ibCan) == 0) break;
        Clear();

        LoadSlide(pszCntCanYear1);

        if (mpboEnblCan[ibCan] == false)
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
      else if (SupportedExtended6_CurrMon(ibCan,ibMon))
      {
        ShowExtended6(ibCan);
      }
      else
      {
        LoadCurrDigital(ibCan);
        ibPort = diCurr.ibPort;

        if (LoadConnect(ibCan) == 0) break;
        Clear();

        LoadSlide(pszCntCanYear10);

        if (mpboEnblCan[ibCan] == false)
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



void    key_GetCntYear(void)
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
        case bGET_CNTCANYEAR1:      LoadSlide(pszCntCanYear1);  break;
        case bGET_CNTCANYEAR10:     LoadSlide(pszCntCanYear10); break;
        case bGET_CNTCANYEAR2:      LoadSlide(pszCntCanYear2);  break;
        case bGET_CNTCANYEAR20:     LoadSlide(pszCntCanYear20); break;
      }
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
      ShowCntCanMon();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibCan = GetCharLo(10,11)-1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;

        ShowCntCanMon();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      ibZ = 0;
      if (++ibCan >= bCANALS) ibCan = 0;

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
      if (ibCan > 0) ibCan--; else ibCan = bCANALS-1;

      ShowCntCanMon();
    }
  }
}



static void ShowCntCanMon6(void)
{
  if (GetDigitalDevice(ibCan) == 6)
    ShowLo(szBadMode);
  else
    ShowCntMonCan6(ibCan,ibMon,ibZ == 0);

  sprintf(szLo+14,"%2u",ibCan+1);
}


void    key_GetCntYear6(void)
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

