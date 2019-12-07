/*------------------------------------------------------------------------------
key_auto_flow.c


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../serial/auto_flow.h"
#include "key_auto_flow.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "    Интервал    ",
                        szMessage2[]     = " авто-транзита  ",
                        szMessage3[]     = "     0..30      ",
                        szMask[]         = "     __ __      ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, "" };



static void Show()
{
  sprintf(szLo+5,"%02u.%02u",stAutoFlow.bMinuteStart,stAutoFlow.bMinuteStop);
}


void    key_SetAutoFlow(void)
{
static auto_flow af;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      LoadSlide(pszMessages);
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      af.bMinuteStart = GetCharLo(5,6);

      if ((af.bMinuteStart > 0) && (af.bMinuteStart <= 31))
      {
        enKeyboard = KBD_INPUT2;
        szLo[7] = '.';
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      af.bMinuteStop = GetCharLo(8,9);

      if (IsValidAutoFlow(af))
      {
        enKeyboard = KBD_POSTENTER;

        stAutoFlow = af;
        SaveCache(&chAutoFlow);
        Show();
      }
      else Beep();
    }
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
      {
        enKeyboard = KBD_INPUT1;
        ShowLo(szMask);
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(5,6);
    }
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(8,9);
    }
  }
  else Beep();
}

