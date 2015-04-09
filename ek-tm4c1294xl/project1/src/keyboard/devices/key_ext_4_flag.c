/*------------------------------------------------------------------------------
_EXTENDED_4T_FLAG.CS


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "timer0.h"
#include        "keyboard.h"



//                                          0123456789ABCDEF
message         code    szExt4TFlag1     = "   Загружать    ",
                        szExt4TFlag2     = "знач. счетчиков ",
                        szExt4TFlag3     = "на начало месяца",
                        szExt4TFlag4     = "  по тарифам ?  ";

uchar           *code   pszExt4TFlag[] = { szExt4TFlag1, szExt4TFlag2, szExt4TFlag3, szExt4TFlag4,  "" };



void    key_SetExtended4TFlag(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      LoadSlide(pszExt4TFlag);    
      ShowBoolean(boExt4TFlag);  
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boExt4TFlag = ~boExt4TFlag;
        ShowBoolean(boExt4TFlag);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
*/
