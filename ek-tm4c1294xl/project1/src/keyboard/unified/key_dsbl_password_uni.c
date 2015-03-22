/*------------------------------------------------------------------------------
KEY_DSBL_PASSWORD_UNI.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "timer0.h"
#include        "keyboard.h"



//                                          0123456789ABCDEF
message         code    szPasswordUni1 =   "   Пароль для   ",
                        szPasswordUni2 =   "протокола УПИО ?";

uchar           *code   pszPasswordUni[] = { szPasswordUni1, szPasswordUni2, "" };



void    key_SetDsblPasswordUni(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      LoadSlide(pszPasswordUni);    
      ShowBoolean((boDisablePasswordUni == boFalse) ? boTrue : boFalse);  
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boDisablePasswordUni = ~boDisablePasswordUni;
        ShowBoolean((boDisablePasswordUni == boFalse) ? boTrue : boFalse);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
*/
