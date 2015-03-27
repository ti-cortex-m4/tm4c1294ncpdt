/*------------------------------------------------------------------------------
_LIMITS30.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "timer0.h"
#include        "keyboard.h"



//                                         0123456789ABCDEF
message         code    szUse30         = "  Использовать  ",
                        szStartCan30    = "нижнюю границу ?";

                        
uchar           *code   pszStartCan[]   = { szUse30, szStartCan30, "" };



void    key_SetLimits30(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      LoadSlide(pszStartCan);    
      ShowBoolean(boStartCan);  
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boStartCan = ~boStartCan;
        ShowBoolean(boStartCan);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
*/
