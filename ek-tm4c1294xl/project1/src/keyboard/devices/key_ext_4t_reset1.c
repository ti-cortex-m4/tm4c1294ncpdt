/*------------------------------------------------------------------------------
KEY_EXT_4T_RESET1.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/extended_4t.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "     —брос      ",
                        szMessage2[]     = "знач. счетчиков ",
                        szMessage3[]     = "   на начало    ",
                        szMessage4[]     = "    мес€цев     ",
                        szMessage5[]     = "   по тарифам   ";

char const             *pszExt4TReset[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, "" };



void    key_SetExt4TReset1(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      if (boExt4TFlag == TRUE)
      {
        enKeyboard = KBD_INPUT1;
        Clear();
      
        LoadSlide(pszExt4TReset);   
        ShowAnswer();
      }
      else BlockProgram2(wSET_EXT4T_FLAG, 0);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ResetExtended4T_Full();
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
