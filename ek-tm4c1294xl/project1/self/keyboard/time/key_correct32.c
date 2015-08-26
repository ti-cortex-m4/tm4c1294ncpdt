/*------------------------------------------------------------------------------
_CORRECT32.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_correct3.h"
#include "../../time/correct3.h"



//                                         0123456789ABCDEF
static char const       szStatus32[]    = "   Состояние    ",
                        szCorrect32[]   = " при коррекции  ",
                        szTime32[]      = "    времени     ";
                        
static char const      *pszCorrect32[]  = { szStatus32, szCorrect32, szTime32, "" };



void    key_SetCorrect32(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      if (boCorrect3 == true)
      {
        enKeyboard = KBD_INPUT1;
        Clear();
      
        LoadSlide(pszCorrect32);    
        
        Clear();
        sprintf(szLo,"%lu:%lu:%u", cdwAbsCorrect3, cdwPosCorrect3, bMaxCorrect3);
        szLo[15] = (Correct3Disabled() ? '-' : '+');
      }
      else BlockProgram(bSET_CORRECT30);
    } 
    else Beep();
  }
  else Beep(); 
}

