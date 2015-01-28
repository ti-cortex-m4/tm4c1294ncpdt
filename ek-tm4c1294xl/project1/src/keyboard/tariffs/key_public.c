/*------------------------------------------------------------------------------
KEY_PUBLIC.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../keyboard.h"
#include        "../../display.h"
#include        "../../tariffs/tariffs.h"



//                                         0123456789ABCDEF
static char const       szPublic[]      = "Тарифы ?        ",
                        szTarCommon[]   = " совмещенные    ",
                        szTarCustom[]   = " раздельные     ";


void    ShowPublic(void)
{
  if (boPublicCurr == boFalse) 
    ShowLo(szTarCustom);
  else 
    ShowLo(szTarCommon);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetPublic(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      ShowHi(szPublic);
      ShowPublic();
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boPublicCurr = ~boPublicCurr;
        SetTariffsDefault();
        ShowPublic();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
