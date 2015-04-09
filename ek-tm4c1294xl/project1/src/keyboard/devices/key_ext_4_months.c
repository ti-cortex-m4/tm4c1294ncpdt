/*------------------------------------------------------------------------------
KEY_EXT_4.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "display.h"
#include        "keyboard.h"
#include        "programs.h"



//                                         0123456789ABCDEF
message         code    szExt4Months    = " „исло мес€цев  ",
                        szExt4Load      = "  дл€ загрузки  ",
                        szExt4Values    = "знач. счетчиков ",
                        szMaskExt4      = "      ___       ";

uchar           *code   pszExt4Months[] = { szExt4Months, szExt4Load, szExt4Values, "" };



void    key_SetExt4(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boExt4Flag == boTrue)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        LoadSlide(pszExt4Months); 
        ShowChar(bExt4Months); 
      }
      else BlockProgram(bSET_EXT4_FLAG);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetChar(6,8);
      if ((ibX != 0) && (ibX <= 12))
      {
        bExt4Months = ibX;
        ShowChar(bExt4Months); 
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskExt4);        
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskExt4);        
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
