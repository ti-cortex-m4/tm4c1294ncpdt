/*------------------------------------------------------------------------------
KEY_MNT_ESC_S.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_extended_1.h"
#include "../../display/display.h"
#include "../keyboard.h"
#include "../../digitals/extended/extended_1.h"



//                                         0123456789ABCDEF
static char const       szMntEscS1[]    = "Время обновления",
                        szMntEscS2[]    = "    значений    ",
                        szMntEscS3[]    = "   счетчиков    ",
                        szMntEscS4[]    = "    в буфере    ",
                        szMinute30[]    = " 30 минут       ",
                        szMinute3[]     = " 3 минуты       ";

static char const       *pszMntEscS[]  = { szMntEscS1, szMntEscS2, szMntEscS3, szMntEscS4, "" };



void    ShowMntEscS(boolean  bo)
{
  if (bo == FALSE)
    strcpy(szLo,szMinute30);
  else
    strcpy(szLo,szMinute3);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetMntEscS(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      LoadSlide(pszMntEscS);
      ShowMntEscS(boMntEscS);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {
        boMntEscS = InvertBoolean(boMntEscS);
        ShowMntEscS(boMntEscS);
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
