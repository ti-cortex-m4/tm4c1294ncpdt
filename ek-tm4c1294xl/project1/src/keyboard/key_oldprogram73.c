/*------------------------------------------------------------------------------
KEY_OLDPROGRAM73.C

 �������� ����������� �������� �� ����� �� �������
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../realtime/realtime.h"
#include        "../energy.h"



static char const      *pszPowCanAlfa[] = { szPower, szAlfa, szBeta, ""};



void    ShowPowCanHou(void)
{
  if (LoadImpHou( (PrevDayIndex(ibY)+ibZ)%wHOURS ) == 1)
  {
    if ((ibY == 0) && (ibZ > GetHouIndex()))
      sprintf(szLo,"         -    ");
    else
    {
      reBuffA = GetCanHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], ibX, 2);
      ShowReal(&reBuffA);   
    }
  }
  else Error();

  sprintf(szLo+14, "%2u", ibZ);
}



void    LoadBetaCan(void)
{
  sprintf(szBeta, "  �� ������ %-2u   ", ibX+1);
}


void    LoadAlfaDayCan(void)
{
  sprintf(szAlfa, "   �� ����� %-2u   ", ibY);
}



void    key_GetOldProgram73(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Canal();

      LoadSlide(pszPowCanAlfa);   

      strcpy(szAlfa,szOnDay);  
      strcpy(szBeta,szOnCanals);  
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_INPUT2;
      Day();
 
      ibX = 0;                          // ������

      LoadBetaCan();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11)-1) < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        Day();
        
        LoadBetaCan();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT2)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();
      
      ibY = 0;                          // ����
      LoadAlfaDayCan();

      ibZ = 0;                          // ������� 
      ShowPowCanHou(); 
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibY = GetCharLo(10,11)) < wHOURS/48)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        LoadAlfaDayCan();

        ibZ = 0;                        // ������� 
        ShowPowCanHou(); 
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibZ >= 48)         
        ibZ = 0;
     
      ShowPowCanHou();
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

      ShowPowCanHou();
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



void    auto_GetOldProgram73(void)
{
  if (enKeyboard == KBD_POSTENTER)
    ShowPowCanHou();
}

