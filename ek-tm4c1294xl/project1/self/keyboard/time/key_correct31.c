/*------------------------------------------------------------------------------
_CORRECT31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_correct3.h"
#include "../../time/correct3.h"



//                                         0123456789ABCDEF
static char const       szCounter31[]   = "    Счетчик     ",
                        szCorrect31[]   = " при коррекции  ",
                        szTime31[]      = "    времени     ",
                        szMaskCorrect31[] = "      ___       ";
                        
static char const      *pszCorrect31[]  = { szCounter31, szCorrect31, szTime31, "" };



void    ShowCorrect31(void)
{
  ShowChar(bMaxCorrect3);
}


void    key_SetCorrect31(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boCorrect3Flag == true)
      {
        enKeyboard = KBD_POSTENTER;

        LoadSlide(pszCorrect31);
        Clear();

        ShowCorrect31();
      } 
      else BlockProgram(bSET_CORRECT30);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetCharLo(6,8);
      if ((ibX > 0) && (ibX <= 100))
      {
        bMaxCorrect3 = ibX;
        ShowCorrect31();   
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskCorrect31);        
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskCorrect31);        
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}

