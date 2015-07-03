/*------------------------------------------------------------------------------
KEY_KEYS_LEVEL_B.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../../nvram/cache.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Уровень доступа ",
                        szMessage2[]    = "для Меркурий-230",
                        szMessage3[]    = "      1..2      ",
                        szMask[]        = "       _        ";
                        
static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



static void Show(void)
{
  Clear();
  sprintf(szLo+7,"%1u",bKeysLevelB);
}


void    key_SetKeysLevelB(void)
{
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
      enKeyboard = KBD_POSTENTER;

      ibX = ToChar(szLo[7]);
      if ((ibX >= 1) && (ibX <= 2))
      {
        bKeysLevelB = ibX;

        SaveCache(&chKeysLevelB);
        Show();
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMask);
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMask);        
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      szLo[7] = szDigits[bKey];
    }
  }
  else Beep();
}

