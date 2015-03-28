/*------------------------------------------------------------------------------
KEY_DECRET.C

 «адание и просмотр правила перехода на сезонное врем€
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../time/decret.h"
#include        "../time/rtc.h"



//                                         0123456789ABCDEF
static char const       szDecret[]      = "—езонное врем€  ",
                        szDecNone[]     = " нет            ",
                        szDecAuto[]     = " автоматическое ",
                        szDecCustom[]   = " специальное    ";



void    ShowDecret(void)
{
  if (deDecret == DEC_NONE) 
    ShowLo(szDecNone);
  else
  if (deDecret == DEC_AUTO) 
    ShowLo(szDecAuto);
  else                      
    ShowLo(szDecCustom);

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

      ShowDecret();
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    { 
      if (deDecret == DEC_NONE) 
        deDecret = DEC_AUTO; 
      else
      if (deDecret == DEC_AUTO) 
        deDecret = DEC_CUSTOM; 
      else                      
        deDecret = DEC_NONE; 

      MakeDecret();
      ShowDecret();
    }
    else Beep();
  } 
  else Beep(); 
}
