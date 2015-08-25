/*------------------------------------------------------------------------------
KEY_BOOL_BLOCKED,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "key_bool_blocked.h"



void    key_SetBoolBlocked(cache const  *pch, char const  *pszMessages[], bool  fBlocked, uint  wProgram)
{
  bool *pboValue = (bool *) pch->pbBuff;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      LoadSlide(pszMessages);
      ShowBool(*pboValue);
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        *pboValue = InvertBoolean(*pboValue);
        SaveCache(pch);

        ShowBool(*pboValue);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
