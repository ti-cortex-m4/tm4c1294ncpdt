/*------------------------------------------------------------------------------
KEY_BLOCK_ESC.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_esc.h"
#include "../../output/esc/esc.h"
#include "../console.h"



//                                         0123456789ABCDEF
static char const       szBlockEsc[]     = "Запрет для Esc ?",
                        szDsblNone[]    = " нет            ",
                        szDsblPartly[]  = " частичный      ",
                        szDsblFull[]    = " полный         ";



static void Show(void)
{
  if (boBlockEsc == boFalse)
    ShowLo(szDsblNone);
  else if (boBlockEsc == boTrue)
    ShowLo(szDsblPartly);
  else
    ShowLo(szDsblFull);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}



void    key_SetBlockEsc(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      ShowHi(szBlockEsc);
      Show();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {
        if (boBlockEsc == boFalse)
          boBlockEsc = boTrue;
        else if (boBlockEsc == boTrue)
          boBlockEsc = (boolean)1;
        else
          boBlockEsc = boFalse;

        SaveFile(flDsblEsc);
        Show();
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
