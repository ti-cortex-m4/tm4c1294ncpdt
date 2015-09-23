/*------------------------------------------------------------------------------
KEY_CORRECT3_VALUE!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_correct3.h"
#include "../../time/correct3.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "    Счетчик     ",
                        szMessage2[]    = " при коррекции  ",
                        szMessage3[]    = "    времени     ",
                        szMask[]        = "      ___       ";
                        
static char const      *pszMessages[]   = { szMessage1, szMessage2, szMessage3, "" };



static void Show(void)
{
  ShowChar(bCorrect3SuccessMax);
}


void    key_SetCorrect3Value(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boCorrect3Flag == true)
      {
        enKeyboard = KBD_POSTENTER;

        LoadSlide(pszMessages);
        Clear();

        Show();
      } 
      else BlockProgram(bSET_CORRECT3_FLAG);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      uchar b = GetCharLo(6,8);
      if ((b >= 1) && (b <= 100))
      {
        bCorrect3SuccessMax = b;
        SaveCache(&chCorrect3SuccessMax);

        Show();
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMask);
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMask);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}
