/*------------------------------------------------------------------------------
KEY_OLDPROGRAM74.C

 Просмотр получасовой мощности за сутки по группам
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_realtime.h"
#include        "../../memory/mem_energy.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../realtime/realtime.h"
#include        "../../energy.h"
#include        "../../energy2.h"




static char const      *pszPowGrpAlfa[] = { szPower, szAlfa, szBeta, ""};



static void ShowPowGrpHou(void)
{
  if (LoadImpHou( (GetDayHouIndex(ibY)+ibZ)%wHOURS ) == TRUE)
  {
    if ((ibY == 0) && (ibZ > GetCurrHouIndex()))
      sprintf(szLo,"         -    ");
    else
    {
      ShowFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibX, 2));
    }
  }
  else Error();

  sprintf(szLo+14, "%2u", ibZ);
}



static void LoadBetaGrp(void)
{
  sprintf(szBeta, "  по группе %-2u  ", ibX+1);
}


static void LoadAlfaDay(void)
{
  sprintf(szAlfa, "  за сутки %-2u   ", ibY);
}



void    key_GetOldProgram74(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Group();

      LoadSlide(pszPowGrpAlfa);   

      strcpy(szAlfa,szOnDay);  
      strcpy(szBeta,szOnGroups);  
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_INPUT2;
      Day();
 
      ibX = 0;                          // группа

      LoadBetaGrp();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11)-1) < bGROUPS)
      {
        enKeyboard = KBD_INPUT2;
        Day();
        
        LoadBetaGrp();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT2)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();
      
      ibY = 0;                          // день
      LoadAlfaDay();

      ibZ = 0;                          // получас
      ShowPowGrpHou(); 
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibY = GetCharLo(10,11)) < wHOURS/48)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        LoadAlfaDay();

        ibZ = 0;                        // получас
        ShowPowGrpHou(); 
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibZ >= 48)         
        ibZ = 0;
     
      ShowPowGrpHou();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)  
    {
      if (ibZ > 0)
        ibZ--;
      else 
        ibZ = 48-1; 

      ShowPowGrpHou();
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
    else
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}



void    auto_GetOldProgram74(void)
{
  if (enKeyboard == KBD_POSTENTER)
    ShowPowGrpHou();
}

