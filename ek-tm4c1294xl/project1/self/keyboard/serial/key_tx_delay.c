/*------------------------------------------------------------------------------
KEY_TX_DELAY,H


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../serial/ports.h"
#include "key_tx_delay.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "  Таймауты на   ",
                        szMessage2[]     = "передачу пакета ",
                        szMask[]         = "     ____ мс  ";

static char const      *pszMessages[] = { szMessage1, szMessage2, "" };



static void Show(uchar  ibPrt)
{
  Clear();
  sprintf(szLo+5,"%4u",mpwTxDelay[ibPrt]);
  sprintf(szLo+10,"мс  %2u",ibPrt+1);
}



void    key_SetTxDelay(void)
{
static uchar ibPrt;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      LoadSlide(pszMessages);

      ibPrt = 2;
      Show(ibPrt);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      uint w = GetIntLo(5,8);
      if (w <= 1000)
      {
        enKeyboard = KBD_POSTENTER;
        mpwTxDelay[ibPrt] = w;

        if (++ibPrt >= bPORTS) ibPrt = 2;
        Show(ibPrt);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibPrt >= bPORTS) ibPrt = 2;
      Show(ibPrt);
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

