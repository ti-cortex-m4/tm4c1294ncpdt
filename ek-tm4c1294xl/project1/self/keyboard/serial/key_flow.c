/*------------------------------------------------------------------------------
_FLOW!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_flow.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "../../serial/flow.h"
#include "../../nvram/cache.h"



//                                          0123456789ABCDEF
static char const       szPortFrom[]     = "Транзит: запуск ",
                        szPortTo[]       = "Транзит: порт   ",
                        szMaskPortTo[]   = "      ___       ";



void    key_FlowPortFrom(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szPortFrom);

      Port();
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bPORTS)
      {
        if (ibX == 0)
        { RunFlow0(); OK(); }
        else
        if (ibX == 1)
        { RunFlow1(); OK(); }
        else
        { Error(); LongBeep(); }
      } 
      else Beep(); 
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep(); 
  }
  else Beep();
}



void    key_FlowPortTo(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ShowHi(szPortTo); 
      ShowChar(ibFlowPortTo);  
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetCharLo(6,8);
      if ((ibX == 3) || (ibX == 4))
      {
        ibFlowPortTo = ibX;

        SaveCache(&chFlowPortTo);
        ShowChar(ibFlowPortTo);  
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskPortTo);        
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskPortTo);        
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}
