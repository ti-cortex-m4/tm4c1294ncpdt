/*------------------------------------------------------------------------------
KEY_PUBLIC_TARIFFS.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../tariffs/tariffs.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szTariffs[]     = "Тарифы ?        ",
                        szPublic[]      = " совмещенные    ",
                        szPrivate[]     = " раздельные     ";


void    ShowPublicTariffs(void)
{
  if (fPublicTariffs == false) 
    ShowLo(szPrivate);
  else 
    ShowLo(szPublic);

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
      
      ShowHi(szTariffs);
      ShowPublicTariffs();
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        fPublicTariffs = (fPublicTariffs == TRUE ? FALSE : TRUE);
        SaveFile(&flPublicTariffs);
        ShowPublicTariffs();

        DefaultTariffs();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
