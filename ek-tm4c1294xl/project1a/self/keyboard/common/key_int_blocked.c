/*------------------------------------------------------------------------------
KEY_INT_BLOCKED,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "key_int_blocked.h"



//                                            0123456789ABCDEF
static char const       szMaskInt[]        = "    _____       ",
                        szBlocked[]        = "Запрещено:      ";

extern  char                    szNumberLimits[bDISPLAY + bMARGIN];



void    key_SetIntBlocked(cache const  *pch, char const  *pszSlide[], uint  wMin, uint  wMax, bool  fNonBlocked, uint  wProgram)
{
  uint *pwVal = (uint *) pch->pbBuff;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (fNonBlocked)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        strcpy(szNumberLimits, szClear);
        sprintf(szNumberLimits+4, "%3u..%-3u", wMin, wMax);

        LoadSlide(pszSlide);
        ShowInt(*pwVal);
      }
      else
      {
        ShowHi(szBlocked);
        Clear();
        sprintf(szLo+1,"программой %u",wProgram);
      }
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      uint w = GetIntLo(4,8);
      if ((w >= wMin) && (w <= wMax))
      {
        *pwVal = w;
        SaveCache(pch);

        ShowInt(*pwVal);
      }
      else
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskInt);
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskInt);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(4,8);
    }
  }
  else Beep();
}
