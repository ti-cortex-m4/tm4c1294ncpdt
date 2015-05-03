/*------------------------------------------------------------------------------
KEY_RELAXS_FLAG.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_tariffs.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "../../tariffs/tariffs.h"
#include "../../tariffs/relaxs.h"
#include "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szRelaxsFlag[]  = "Праздники ?     ";



void    key_SetRelaxsFlag(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      ShowHi(szRelaxsFlag);
      ShowBoolean(boRelaxsFlag);
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boRelaxsFlag = InvertBoolean(boRelaxsFlag);
        SaveFile(&flRelaxsFlag);

        ShowBoolean(boRelaxsFlag);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
