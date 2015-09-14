/*------------------------------------------------------------------------------
_ENABLE_BULK.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "timer0.h"
#include        "keyboard.h"
#include        "bulk.h"



#ifdef  BULK

//                                         0123456789ABCDEF
message         code    szEnableBulk1   = "   Разрешение   ",
                        szEnableBulk2   = "    пакетной    ",
                        szEnableBulk3   = "   передачи ?   ";
                        
uchar           *code   pszEnableBulk[] = { szEnableBulk1, szEnableBulk2, szEnableBulk3, "" };



void    ShowEnableBulk(boolean  boT)
{
  ShowBoolean(boT);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetEnableBulk(void) 
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      LoadSlide(pszEnableBulk);    
      ShowEnableBulk(boEnableBulk);  
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boEnableBulk = ~boEnableBulk;
        ShowEnableBulk(boEnableBulk);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}

#endif
*/
