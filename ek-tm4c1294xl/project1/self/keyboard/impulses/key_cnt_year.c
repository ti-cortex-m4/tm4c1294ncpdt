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
static char const       szCounters[]      = "    —четчики    ",
                        szAtBegin[]       = "на начало мес€ца",
                        szAtEnd[]         = "на конец мес€ца ",
                        szNoData[]        = "  нет данных !  ",
                        szNotSupported[]  = "*  нет данных   ",
                        szBuffer[]        = "   из буфера    ",
                        szType1[]         = "  с дозапросом  ",
                        szType2[]         = " пр€мого опроса ";

static char const       *pszCntCanYear1[]  = { szCounters, szBeta, szAtEnd,   "" },
                        *pszCntCanYear10[] = { szCounters, szBeta, szAtBegin, "" },
                        *pszCntCanYear2[]  = { szCounters, szBeta, szAtEnd,   szBuffer, szType1, "" },
                        *pszCntCanYear20[] = { szCounters, szBeta, szAtBegin, szBuffer, szType1, "" },
                        *pszCntCanYear3[]  = { szCounters, szBeta, szAtEnd,   szBuffer, szType2, "" };


static uchar            ibCan, ibMon, ibVal;



static void Show(void)
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
            (ReadCntMonCanF_Curr(ibMon,ibCan) == true) ? ShowCntMonCanF(ibVal == 0) : Error();
          }
        }

        SaveConnect();
      }
      break;

    case bGET_CNTCANYEAR10:     
      if (ibMon == tiCurr.bMonth)
        ShowLo(szNoData);
      else
      {
        ibMon = (12+ibMon-1)%12;

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

          LoadSlide(pszCntCanYear10);

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
              (ReadCntMonCanF_Curr(ibMon,ibCan) == true) ? ShowCntMonCanF(ibVal == 0) : Error();
            }
          }

          SaveConnect();
        }
      }
      break;

    case bGET_CNTCANYEAR2:  
      ShowExtended4(ibCan,ibMon,ibVal == 0);
      break;

    case bGET_CNTCANYEAR20:     
      if (ibMon == tiCurr.bMonth)
        ShowLo(szNoData);
      else
      {
        ibMon = (12+ibMon-1)%12;
        ShowExtended4(ibCan,ibMon,ibVal == 0);
      }
      break;

    case wGET_CNTCANYEAR3:
      if (GetDigitalDevice(ibCan) == 6)
        ShowLo(szNotSupported);
      else
        ShowCntMonCan6(ibCan,ibMon,ibVal == 0);
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
      ibVal = 0;

      switch (wProgram)
      {
        case bGET_CNTCANYEAR1:  LoadSlide(pszCntCanYear1);  break;
        case bGET_CNTCANYEAR10: LoadSlide(pszCntCanYear10); break;
        case bGET_CNTCANYEAR2:  LoadSlide(pszCntCanYear2);  break;
        case bGET_CNTCANYEAR20: LoadSlide(pszCntCanYear20); break;
        case wGET_CNTCANYEAR3:  LoadSlide(pszCntCanYear3);  break;
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
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibCan = GetCharLo(10,11)-1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;

        Show();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      ibVal = 0;
      if (++ibCan >= bCANALS) ibCan = 0;

      Show();
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
      ibVal = (ibVal + 1) % 2;
      Show();
    }
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)  
    {
      ibVal = 0;
      if (ibMon > 0) ibMon--; else ibMon = 12-1;

      LoadBetaMonth(ibMon);
      Show();
      ShowSlide(szBeta);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)  
    {
      ibVal = 0;
      if (ibCan > 0) ibCan--; else ibCan = bCANALS-1;

      Show();
    }
  }
}
