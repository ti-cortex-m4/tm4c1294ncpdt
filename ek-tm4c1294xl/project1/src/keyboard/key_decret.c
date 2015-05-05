/*------------------------------------------------------------------------------
KEY_DECRET,C

 «адание и просмотр правила перехода на сезонное врем€
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../console.h"
#include "../time/decret.h"



//                                         0123456789ABCDEF
static char const       szDecret[]      = "—езонное врем€  ",
                        szNone[]        = " нет            ",
                        szAuto[]        = " автоматическое ",
                        szCustom[]      = " специальное    ";



static void Show(void)
{
  if (deDecret == DEC_NONE) 
    ShowLo(szNone);
  else if (deDecret == DEC_AUTO)
    ShowLo(szAuto);
  else                      
    ShowLo(szCustom);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}



void    key_SetDecret(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szDecret);     
      Clear();

      Show();
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    { 
      if (deDecret == DEC_NONE) 
        deDecret = DEC_AUTO; 
      else if (deDecret == DEC_AUTO)
        deDecret = DEC_CUSTOM; 
      else                      
        deDecret = DEC_NONE; 

      MakeDecret();
      Show();
    }
    else Beep();
  } 
  else Beep(); 
}
