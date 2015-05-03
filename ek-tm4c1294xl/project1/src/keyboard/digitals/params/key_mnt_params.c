/*------------------------------------------------------------------------------
KEY_MNT_PARAMS.C


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/params/params.h"
#include "../../key_flag.h"



//                                         0123456789ABCDEF
static char const       szMntParams[]   = "Параметры: время",
                        szMinute30[]    = " 30 минут       ",
                        szMinute3[]     = " 3 минуты       ";



static void Show(boolean  bo)
{
  if (bo == FALSE)
    strcpy(szLo,szMinute30);
  else
    strcpy(szLo,szMinute3);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetMntParams(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      ShowHi(szMntParams);
      Show(boMntParams);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {
        boMntParams = InvertBoolean(boMntParams);
        Show(boMntParams);
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
