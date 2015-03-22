/*------------------------------------------------------------------------------
KEY_MAX_DELAY_UNI.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "display.h"
#include        "keyboard.h"



//                                           0123456789ABCDEF
message         code    szMaxDelayUni1    = "  Òàéìàóò ÓÏÈÎ  ",
                        szMaxDelayUni2    = "    10..250     ",
                        szMaskMaxDelayUni = "      ___       ";
                        
uchar           *code   pszMaxDelayUni[] = { szMaxDelayUni1, szMaxDelayUni2, "" };



void    ShowMaxDelayUni(void)
{
  Clear();
  sprintf(szLo+6,"%3bu",bMaxDelayUni);
}


void    key_SetMaxDelayUni(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      LoadSlide(pszMaxDelayUni); 
      ShowMaxDelayUni();
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetChar(6,8);
      if ((ibX >= 10) && (ibX <= 250))
      {
        bMaxDelayUni = ibX;

        ShowMaxDelayUni();
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskMaxDelayUni);        
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskMaxDelayUni);        
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
