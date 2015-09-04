/*------------------------------------------------------------------------------
KEY_EXT_3_RESET.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../digitals/extended/extended_3.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "    Очистить    ",
                        szMessage2[]     = "журналы событий ",
                        szMessage3[]     = " со счетчиков ? ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetExt3Reset(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;

      LoadSlide(pszMessages);

      Clear();
      ShowAnswer();
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ResetExtended3_Manual();
      OK();
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        if (enKeyboard == KBD_INPUT1)
          enKeyboard = KBD_POSTINPUT1;
        else
          enKeyboard = KBD_INPUT1;

        ShowAnswer();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
