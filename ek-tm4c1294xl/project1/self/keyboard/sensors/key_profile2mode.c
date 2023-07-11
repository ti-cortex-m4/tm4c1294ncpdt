/*------------------------------------------------------------------------------
KEY_MNT_ESC_S!C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_extended_1.h"
#include "../../display/display.h"
#include "../keyboard.h"
#include "../../devices/devices_init.h"
#include "key_profile2mode.h"



//                                         0123456789ABCDEF
static char const       szMntEscS1[]    = "Время обновления",
                        szMntEscS2[]    = "    значений    ",
                        szMntEscS3[]    = "   счетчиков    ",
                        szMntEscS4[]    = "    в буфере    ",
                        szMinute30[]    = " 30 минут       ",
                        szMinute3[]     = " 3 минуты       ";

static char const       *pszMntEscS[]  = { szMntEscS1, szMntEscS2, szMntEscS3, szMntEscS4, "" };



static void Show(bool  bo)
{
  if (bo == false)
    strcpy(szLo,szMinute30);
  else
    strcpy(szLo,szMinute3);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetProfile2Mode(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      LoadSlide(pszMntEscS);
      Show(enProfile2Mode);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {
        enProfile2Mode = enProfile2Mode;
        Show(enProfile2Mode);
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
