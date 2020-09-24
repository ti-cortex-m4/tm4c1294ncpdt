/*------------------------------------------------------------------------------
KEY_SHORT_PROFILE_B!C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../../sensors/sensor2/profile2x16.h"
#include "../common/key_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Размер блока  ",
                        szMessage2[]    = "   при опросе   ",
                        szMessage3[]    = "  Меркурий-230  ",
                        szBlock1[]      = " 1 получас      ",
                        szBlock16[]     = " 16 получасов   ",
                        szBlockAuto[]   = " автоматически  ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



static void ShowValue(uchar  b)
{
  if (b == PROFILE2X16_16)
    strcpy(szLo, szBlock16);
  else if (b == PROFILE2X16_AUTO)
    strcpy(szLo, szBlockAuto);
  else
    strcpy(szLo, szBlock1);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}



void    key_SetShortProfileB(void)
{
  cache const *pch = &chShortProfileB;
  uchar *pbValue = (uchar *) pch->pbBuff;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      LoadSlide(pszMessages);
      ShowValue(*pbValue);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {
        uchar b = *pbValue;

        if (b == 2)
          b = 0;
        else if (b == 1)
          b = 2;
        else
          b = 1;

        *pbValue = b;
        SaveCache(pch);

        ShowValue(*pbValue);
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
