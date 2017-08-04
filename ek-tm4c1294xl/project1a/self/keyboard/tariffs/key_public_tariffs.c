/*------------------------------------------------------------------------------
KEY_PUBLIC_TARIFFS!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_tariffs.h"
#include "../../tariffs/tariffs.h"
#include "../../nvram/cache.h"



//                                         0123456789ABCDEF
static char const       szPublicTrf[]     = "Тарифы ?        ",
                        szTrue[]          = " совмещенные    ",
                        szFalse[]         = " раздельные     ";


static void Show(void)
{
  if (fPublicTrf == false) 
    ShowLo(szFalse);
  else 
    ShowLo(szTrue);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetPublicTariffs(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      ShowHi(szPublicTrf);
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
        fPublicTrf = InvertBool(fPublicTrf);
        SaveCache(&chPublicTrf);
        Show();

        DefaultTariffs();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
