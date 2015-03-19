/*------------------------------------------------------------------------------
KEY_CUSTOM_MODEM.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_phones.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../digitals/phones.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szSendModem[]   = "Выдавать модему ",
                        szCustomModem[] = " настройки 2 ?  ";

static char const       *pszCustomModem[] = { szSendModem, szCustomModem, "" };



void    key_SetCustomModem(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      LoadSlide(pszCustomModem);
      ShowBoolean(boCustomModem);
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boCustomModem = (boCustomModem == TRUE ? FALSE : TRUE);
        SaveFile(&flCustomModem);

        ShowBoolean(boCustomModem);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
