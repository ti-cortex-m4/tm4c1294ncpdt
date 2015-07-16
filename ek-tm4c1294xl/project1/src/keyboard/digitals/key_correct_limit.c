/*------------------------------------------------------------------------------
KEY_CORRECT_LIMIT.C

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_ports.h"



//                                          0123456789ABCDEF
static char const       szCorrectLimit1[]  = "  Максимальная  ",
                        szCorrectLimit2[]  = "разница времени ",
                        szCorrectLimit3[]  = "   счетчиков    ",
                        szCorrectLimit4[]  = "  и сумматора   ",
                        szCorrectLimit5[]  = " без коррекции  ",
                        szCorrectLimitM[]  = "1..20   __ с  ";
                      
static char const      *pszCorrectLimit[] = { szCorrectLimit1, szCorrectLimit2, szCorrectLimit3, szCorrectLimit4, szCorrectLimit5, "" };



void    ShowCorrectLimit(void)
{
  Clear();
  sprintf(szLo+8,"%2bu c",mpbCorrectLimit[ibX]);
  sprintf(szLo+15,"%1bu",ibX+1);
}


void    key_SetCorrectLimit(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      LoadSlide(pszCorrectLimit);    

      ibX = 0;
      ShowCorrectLimit();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {            
      wBuffD = GetInt(8,9);

      if ((wBuffD >= bCORRECT_MINIMUM) && (wBuffD <= bCORRECT_MAXIMUM))
      {
        enKeyboard = KBD_POSTENTER;
        mpbCorrectLimit[ibX] = wBuffD;

        if (++ibX >= bPORTS) ibX = 0;
        ShowCorrectLimit();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bPORTS) ibX = 0;
      ShowCorrectLimit();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
      {
        enKeyboard = KBD_INPUT1;
        ShowLo(szCorrectLimitM);
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(8,9);
    }
    else Beep(); 
  }
  else Beep();
}
