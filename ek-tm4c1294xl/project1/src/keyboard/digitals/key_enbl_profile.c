/*------------------------------------------------------------------------------
KEY_ENBL_PROFILE.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../digitals/profile_core.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
//                                         0123456789ABCDEF
static char const       szLoad[]        = "   Загружать    ",
                        szProfile[]     = "30-мин. данные ?";

static char const       *pszEnblProfile[]   = { szLoad, szProfile, "" };



void    key_SetEnblProfile(void)
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
        ShowBoolean(boEnblProfile);

        SaveFile(&flEnblProfile);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
