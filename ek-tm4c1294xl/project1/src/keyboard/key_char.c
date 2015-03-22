/*------------------------------------------------------------------------------
KEY_CHAR.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../flash/files.h"
#include        "key_char.h"



//                                            0123456789ABCDEF
static char const       szMaskChar[]       = "      ___       ";

char                    szCharLimits[bDISPLAY + bMARGIN];



void    key_SetChar(file const  *pflFile, char const  *pszSlide[], uchar const  bMin, uchar const  bMax)
{
  uchar *pbValue = (uchar *) pflFile->pbBuff;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      strcpy(szCharLimits, szClear);
      sprintf(szCharLimits+4, "%3u..%-3u", bMin, bMax);

      LoadSlide(pszSlide);
      ShowChar(*pbValue);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      uchar b = GetCharLo(6,8);
      if ((b >= bMin) && (b <= bMax))
      {
        *pbValue = b;
        SaveFile(pflFile);

        ShowChar(*pbValue);
      }
      else
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskChar);
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskChar);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}
