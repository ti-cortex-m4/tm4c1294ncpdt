/*------------------------------------------------------------------------------
_EXTENDED_4T_RESET1.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "keyboard.h"
#include        "keyboard2.h"
#include        "programs2.h"
#include        "extended_4t.h"



//                                          0123456789ABCDEF
message         code    szExt4TReset1    = "  —брос данных  ",
                        szExt4TReset2    = "знач. счетчиков ",
                        szExt4TReset3    = "на начало мес€ца",
                        szExt4TReset4    = "  по тарифам    ";

uchar           *code   pszExt4TReset[] = { szExt4TReset1, szExt4TReset2, szExt4TReset3, szExt4TReset4,  "" };



void    key_SetExtended4TReset1(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      if (boExt4TFlag == boTrue)
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
      ResetExtended4T1();
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

*/
