/*------------------------------------------------------------------------------
_CORRECT32.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_correct3.h"
#include "../../time/correct3.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "   Состояние    ",
                        szMessage2[]    = " при коррекции  ",
                        szMessage3[]    = "    времени     ";
                        
static char const      *pszMessages[]   = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetCorrect3Status(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      if (boCorrect3Flag == true)
      {
        enKeyboard = KBD_INPUT1;
        Clear();
      
        LoadSlide(pszMessages);    
        
        Clear();
        sprintf(szLo,"%lu:%lu:%u", dwCorrect3Total, dwCorrect3Success, bCorrect3SuccessMax);
        szLo[15] = (Correct3Disabled() ? '-' : '+');
      }
      else BlockProgram(bSET_CORRECT3_FLAG);
    } 
    else Beep();
  }
  else Beep(); 
}
