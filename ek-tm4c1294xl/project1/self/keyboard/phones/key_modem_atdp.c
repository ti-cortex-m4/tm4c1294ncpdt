/*------------------------------------------------------------------------------
KEY_MODEM_ATDP,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/phones.h"
#include "../../console.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "    Команда     ",
                        szMessage2[]    = "   соединения   ",
                        szMessage3[]    = "    модема ?    ",
                        szATDP[]        = " ATDP           ",
                        szATD[]         = " ATD            ";


static char const       *pszMessages[] = { szMessage1, szMessage2, szMessage3, "" };



static void Show(void)
{
  if (fModemATDP == false)
    ShowLo(szATD);
  else
    ShowLo(szATDP);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}



void    key_SetModemATDP(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      LoadSlide(pszMessages);
      Show();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {
        if (fModemATDP == false)
          fModemATDP = true;
        else
          fModemATDP = false;

        SaveCache(&chModemATDP);
        Show();
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
