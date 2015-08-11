/*------------------------------------------------------------------------------
KEY_ENG_YEAR.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../realtime/realtime.h"
#include "../../energy.h"
#include "../../energy2.h"
#include "../../time/timedate_display.h"
#include "key_eng_year.h"



static char const       *pszEngFull[]    = { szEnergy, szBeta, szFull,   "" },
                        *pszEngTops[]    = { szEnergy, szBeta, szTops,   "" },
                        *pszEngMid[]     = { szEnergy, szBeta, szMid,    "" },
                        *pszEngBottom[]  = { szEnergy, szBeta, szBottom, "" };


static uchar            ibGrp, ibMon;



static void ShowEngYear(uchar  bMask)
{
  LoadImpMon(ibMon);
  ShowDouble(GetGrpImp2DoubleEng(mpimMonCan[ PrevSoftMon() ],ibGrp,bMask));
}


static void Show(void)
{
  switch (wProgram)
  {
    case bGET_ENGGRPYEAR_ABCD:  ShowEngYear(0x0F);  break;
    case bGET_ENGGRPYEAR_CD:    ShowEngYear(0x0C);  break;
    case bGET_ENGGRPYEAR_B:     ShowEngYear(0x02);  break;
    case bGET_ENGGRPYEAR_A:     ShowEngYear(0x01);  break;
  }

  sprintf(szLo+14,"%2u",ibGrp+1);
}


void    key_GetEngYear(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;

      Month();
      strcpy(szBeta, szOn12Months); 

      switch (wProgram)
      {
        case bGET_ENGGRPYEAR_ABCD:  LoadSlide(pszEngFull);    break;
        case bGET_ENGGRPYEAR_CD:    LoadSlide(pszEngTops);    break;
        case bGET_ENGGRPYEAR_B:     LoadSlide(pszEngMid);     break;
        case bGET_ENGGRPYEAR_A:     LoadSlide(pszEngBottom);  break;
      }
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_INPUT2;
      Group();

      ibMon = ibHardMon;

      LoadBetaMonth(ibMon);
      ShowSlide(szBeta);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibMon = GetCharLo(10,11)-1) < 12)
      {
        enKeyboard = KBD_INPUT2;
        Group();

        LoadBetaMonth(ibMon);
        ShowSlide(szBeta);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT2)
    {
      enKeyboard = KBD_POSTENTER;

      ibGrp = 0;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibGrp = GetCharLo(10,11)-1) < bGROUPS)
      {
        enKeyboard = KBD_POSTENTER;

        Show();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibGrp >= bGROUPS) ibGrp = 0;

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
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)  
    {
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
      if (ibGrp > 0) ibGrp--; else ibGrp = bGROUPS-1;

      Show();
    }
  }
}
