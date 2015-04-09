/*------------------------------------------------------------------------------
KEY_EXT_4T_MONTHS.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "display.h"
#include        "keyboard.h"
#include        "keyboard2.h"
#include        "programs2.h"



//                                          0123456789ABCDEF
message         code    szExt4TMonths1   = " „исло мес€цев  ",
                        szExt4TMonths2   = "  дл€ загрузки  ",
                        szExt4TMonths3   = "знач. счетчиков ",
                        szExt4TMonths4   = "на начало мес€ца",
                        szExt4TMonths5   = "  по тарифам    ",
                        szMaskExt4T      = "      ___       ";

uchar           *code   pszExt4TMonths[] = { szExt4TMonths1, szExt4TMonths2, szExt4TMonths3, szExt4TMonths4, szExt4TMonths4,  "" };



void    key_SetExt4TMonths(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boExt4TFlag == TRUE)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        LoadSlide(pszExt4TMonths); 
        ShowChar(bExt4TMonths); 
      }
      else BlockProgram2(wSET_EXT4T_FLAG, 0);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetChar(6,8);
      if ((ibX != 0) && (ibX <= 12))
      {
        bExt4TMonths = ibX;
        ShowChar(bExt4TMonths); 
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskExt4T);
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskExt4T);        
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}

*/
