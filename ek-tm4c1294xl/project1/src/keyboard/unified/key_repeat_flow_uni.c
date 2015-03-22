/*------------------------------------------------------------------------------
KEY_REPEAT_FLOW_UNI.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "timer0.h"
#include        "keyboard.h"



//                                             0123456789ABCDEF
message         code    szRepeatFlowUni1    = "  Возобновлять  ",
                        szRepeatFlowUni2    = "транзит УПИО при",
                        szRepeatFlowUni3    = "каждом запросе ?";
                        
uchar           *code   pszRepeatFlowUni[]  = { szRepeatFlowUni1, szRepeatFlowUni2, szRepeatFlowUni3, "" };



void    key_SetRepeatFlowUni(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      LoadSlide(pszRepeatFlowUni);    
      ShowBoolean(boRepeatFlowUni);  
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boRepeatFlowUni = ~boRepeatFlowUni;
        ShowBoolean(boRepeatFlowUni);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
*/
