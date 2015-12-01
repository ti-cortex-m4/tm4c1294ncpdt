/*------------------------------------------------------------------------------
KEY_BOOL_BLOCKED.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "key_bool_blocked.h"



//                                          0123456789ABCDEF
static char const       szBlocked[]      = "Запрещено:      ";



void    key_SetBoolBlocked(cache const  *pch, char const  *pszMessages[], bool  fNonBlocked, uint  wProgram)
{
  bool *pf = (bool *) pch->pbBuff;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (fNonBlocked)
      {
        enKeyboard = KBD_INPUT1;
        Clear();

        LoadSlide(pszMessages);
        ShowBool(*pf);
      }
      else
      {
        ShowHi(szBlocked);
        Clear();
        sprintf(szLo+1,"программой %u",wProgram);
      }
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {
        *pf = InvertBool(*pf);
        SaveCache(pch);

        ShowBool(*pf);
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
