/*------------------------------------------------------------------------------
KEY_MAX_REPEATS.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../display/display.h"
#include        "../keyboard.h"
#include        "../../digitals/max_repeats.h"
#include        "../../flash/files.h"



//                                            0123456789ABCDEF
static char const       szMaxRepeats1[]    = "  Повторы при   ",
                        szMaxRepeats2[]    = "опросе счетчиков",
                        szMaxRepeats3[]    = "      1..20     ",
                        szMaskMaxRepeats[] = "       __       ";

static char const       *pszMaxRepeats[]   = { szMaxRepeats1, szMaxRepeats2, szMaxRepeats3, "" };



void    ShowMaxRepeats(void)
{
  Clear();
  sprintf(szLo+7,"%2u",bMaxRepeats);
}


void    key_SetMaxRepeats(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      LoadSlide(pszMaxRepeats); 
      ShowMaxRepeats();
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetCharLo(7,8);
      if ((ibX > 0) && (ibX <= 20))
      {
        bMaxRepeats = ibX;

        SaveFile(&flMaxRepeats);
        ShowMaxRepeats();
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskMaxRepeats);        
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskMaxRepeats);        
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(7,8);
    }
  }
  else Beep();
}

