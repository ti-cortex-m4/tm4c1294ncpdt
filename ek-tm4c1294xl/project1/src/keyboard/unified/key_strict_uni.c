/*------------------------------------------------------------------------------
KEY_STRICT_UNI.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "timer0.h"
#include        "keyboard.h"



//                                          0123456789ABCDEF
message         code    szStrictUni1 =     "   Расширение   ",
                        szStrictUni2 =     "протокола УПИО ?";

uchar           *code   pszStrictUni[] = { szStrictUni1, szStrictUni2, "" };



void    key_SetStrictUni(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      LoadSlide(pszStrictUni);    
      ShowBoolean(boStrictUni);  
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boStrictUni = ~boStrictUni;
        ShowBoolean(boStrictUni);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
*/
