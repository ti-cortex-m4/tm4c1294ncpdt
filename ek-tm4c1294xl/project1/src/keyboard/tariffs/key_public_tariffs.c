/*------------------------------------------------------------------------------
KEY_PUBLIC_TARIFFS.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../keyboard.h"
#include        "../../display/display.h"
#include        "../../tariffs/tariffs.h"



//                                         0123456789ABCDEF
static char const       szTariffs[]     = "Тарифы ?        ",
                        szCommon[]      = " совмещенные    ",
                        szCustom[]      = " раздельные     ";


void    ShowPublicTariffs(void)
{
  if (fPublicTariffsCurr == false) 
    ShowLo(szCustom);
  else 
    ShowLo(szCommon);

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
        fPublicTariffsCurr = ~fPublicTariffsCurr;
        ShowPublicTariffs();

        SetDefaultTariffs();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
