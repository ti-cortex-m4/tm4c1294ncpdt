/*------------------------------------------------------------------------------
KEY_ENBL_KEYS.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "../../digitals/digitals.h"
#include "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szEnblKeys[]    = "Пароли ?        ";



void    key_SetEnblKeys(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      ShowHi(szEnblKeys);
      ShowBoolean(boEnblKeys);
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boEnblKeys = InvertBoolean(boEnblKeys);
        SaveFile(&flEnblKeys);

        ShowBoolean(boEnblKeys);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
