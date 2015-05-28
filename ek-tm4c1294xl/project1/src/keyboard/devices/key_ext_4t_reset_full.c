/*------------------------------------------------------------------------------
KEY_EXT_4T_RESET_FULL,C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../digitals/extended/extended_4t.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "     —брос      ",
                        szMessage2[]     = "знач. счетчиков ",
                        szMessage3[]     = "   на начало    ",
                        szMessage4[]     = "    мес€цев     ",
                        szMessage5[]     = "   по тарифам   ";

char const             *pszExt4TReset[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, "" };



static void Show(void)
{
  ShowBool(enKeyboard != KBD_INPUT1);
}


void    key_SetExt4TResetFull(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      if (boExt4TFlag == true)
      {
        enKeyboard = KBD_INPUT1;
        Clear();
      
        LoadSlide(pszExt4TReset);
        Show();
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

        Show();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
