/*------------------------------------------------------------------------------
KEY_ENBL_KEYS.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../digitals/profile_core.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szEnbl[]        = "   Загружать    ",
                        szProfile[]     = "30-мин. данные ?";

static char const       *pszEnblProfile[] = { szEnbl, szProfile, "" };



void    key_SetEnblKeys(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      LoadSlide(pszEnblProfile);
      ShowBoolean(boEnblProfile);
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boEnblProfile = (boEnblProfile == TRUE ? FALSE : TRUE);
        SaveFile(&flEnblProfile);

        ShowBoolean(boEnblProfile);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
