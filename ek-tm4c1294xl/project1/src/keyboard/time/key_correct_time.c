/*------------------------------------------------------------------------------
KEY_CORRECT_TIME.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../time/correct1.h"
#include "../../time/correct3.h"



//                                         0123456789ABCDEF
static char const       szCorrectTime[] = "Коррекция секунд";



void    key_CorrectTime(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (Correct3Disabled())
      {
        Correct3(EVE_PROGRAM_2);
        BlockPrograms(bSET_CORRECT30, bSET_CORRECT32);
      }
      else
      {
        enKeyboard = KBD_POSTENTER;
        ibZ = 60;

        ShowHi(szCorrectTime);
        Clear();
      }
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (CorrectTime(EVE_PROGRAM_2) == true)
        enKeyboard = KBD_SHOW;
      else
        LongBeep();
    }
    else Beep();
  }
  else Beep();
}
