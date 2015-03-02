/*------------------------------------------------------------------------------
_OLDPROGRAM74.C

 Просмотр получасовой мощности за сутки по группам
------------------------------------------------------------------------------*/

#include        "main.h"                 
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "display.h"
#include        "tariffs.h"
#include        "keyboard.h"
#include        "programs.h"
#include        "energy.h"
#include        "engine.h"
#include        "general.h"
#include        "nexttime.h"



uchar           *code   pszPowGrpAlfa[] = { szPower, szAlfa, szBeta, ""};                            



void    ShowPowGrpHou(void)
{
  if (LoadImpHou( (PrevDayIndex(ibY)+ibZ)%wHOURS ) == 1)
  {
    if ((ibY == 0) && (ibZ > GetHouIndex()))
      sprintf(szLo,"         -    ");
    else
    {
      reBuffA = *PGetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibX, 2);
      ShowReal(&reBuffA);   
    }
  }
  else Error();

  sprintf(szLo+14, "%2bu", ibZ);
}



void    LoadBetaGrp(void)
{
  sprintf(szBeta, "  по группе %-2bu   ", ibX+1);
}


void    LoadAlfaDayGrp(void)
{
  sprintf(szAlfa, "   за сутки %-2bu   ", ibY);
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
      if ((ibX = GetChar(10,11)-1) < bGROUPS)
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
      LoadAlfaDayGrp();

      ibZ = 0;                          // получас 
      ShowPowGrpHou(); 
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibY = GetChar(10,11)) < wHOURS/48)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        LoadAlfaDayGrp();

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

