/*------------------------------------------------------------------------------
KEY_RECALC!C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../special/recalc.h"



//                                          0123456789ABCDEF
static char const       szRecalcFull[]   = "Расчет полный   ",
                        szRecalcMaxPow[] = "Расчет мощности ",
                        szRecalcEng[]    = "Расчет ~нергии  ";



void    key_SetRecalc(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      switch (wProgram)
      { 
        case bSET_RECALC_FULL:   ShowHi(szRecalcFull);   ShowAnswer(); break;
        case bSET_RECALC_MAXPOW: ShowHi(szRecalcMaxPow); ShowAnswer(); break;
        case bSET_RECALC_ENG:    ShowHi(szRecalcEng);    ShowAnswer(); break;
      }
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      switch (wProgram)
      {
        case bSET_RECALC_FULL:   if (Recalc(1,1) == 1) OK(); else Error(); break;
        case bSET_RECALC_MAXPOW: if (Recalc(0,1) == 1) OK(); else Error(); break;
        case bSET_RECALC_ENG:    if (Recalc(1,0) == 1) OK(); else Error(); break;
      }
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        if (enKeyboard == KBD_INPUT1)
          enKeyboard = KBD_POSTINPUT1;
        else
          enKeyboard = KBD_INPUT1;

        ShowAnswer();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
