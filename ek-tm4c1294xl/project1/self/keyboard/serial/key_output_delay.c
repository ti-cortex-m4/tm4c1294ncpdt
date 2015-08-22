/*------------------------------------------------------------------------------
KEY_OUTPUT_DELAY.H

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../serial/ports.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "  Таймауты при  ",
                        szMessage2[]     = " переключении в ",
                        szMessage3[]     = " режим передачи ",
                        szMask[]         = "     ____ мс  ";

static char const      *pszMessages[] = { szMessage1, szMessage2, szMessage3, "" };



static void Show(uchar  ibPrt)
{
  Clear();
  sprintf(szLo+5,"%4u",wOutputDelay[ibPrt]);
  sprintf(szLo+10,"мс  %2bu",ibPrt+1);
}



void    key_SetOutputDelay(void)
{
static uchar ibPrt;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      LoadSlide(pszMessages);

      ibPrt = 2;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {            
      wBuffD = GetInt(5,8);
      if (wBuffD <= 1000)
      {
        enKeyboard = KBD_POSTENTER;
        wOutputDelay[ibPrt] = wBuffD;

        if (++ibPrt >= bPORTS) ibPrt = 2;
        Show();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibPrt >= bPORTS) ibPrt = 2;
      Show();
    }
    else Beep();
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
      ShiftLo(5,8);
    }
    else Beep(); 
  }
  else Beep();
}

