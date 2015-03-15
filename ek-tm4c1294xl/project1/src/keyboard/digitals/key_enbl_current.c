/*------------------------------------------------------------------------------
KEY_ENBL_CURRENT.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../digitals/profile_core.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szEnbl[]        = "   Загружать    ",
                        szCurrent[]     = " 3-мин. данные ?";

static char const       *pszEnblCurrent[] = { szEnbl, szCurrent, "" };



void    key_SetEnblCurrent(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      LoadSlide(pszEnblCurrent);
      ShowBoolean(boEnblCurrent);
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boEnblCurrent = (boEnblCurrent == TRUE ? FALSE : TRUE);
        SaveFile(&flEnblCurrent);

        ShowBoolean(boEnblCurrent);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
