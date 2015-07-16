/*------------------------------------------------------------------------------
KEY_CORRECT_LIMIT.C

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_ports.h"
#include "../../digitals/correct_limit.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "  Максимальная  ",
                        szMessage2[]     = "разница времени ",
                        szMessage3[]     = "   счетчиков    ",
                        szMessage4[]     = "  и сумматора   ",
                        szMessage5[]     = " без коррекции  ",
                        szMessage6[]     = "     1..20      ",
                        szMask[]         = "       __       ";
                      
static char const      *pszMessages[]    = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szMessage6, "" };



static void Show(uchar  ibPrt)
{
  Clear();
  sprintf(szLo+8,"%2u c",mpbCorrectLimit[ibPrt]);
  sprintf(szLo+15,"%1u",ibPrt+1);
}


void    key_SetCorrectLimit(void)
{
static uchar ibPrt;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      LoadSlide(pszMessages);

      ibPrt = 0;
      Show(ibPrt);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {            
      uchar b = GetCharLo(7,8);

      if ((b >= bCORRECT_MINIMUM) && (b <= bCORRECT_MAXIMUM))
      {
        enKeyboard = KBD_POSTENTER;

        mpbCorrectLimit[ibPrt] = b;
        SaveCache(&chCorrectLimit);

        if (++ibPrt >= bPORTS) ibPrt = 0;
        Show(ibPrt);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibPrt >= bPORTS) ibPrt = 0;
      Show(ibPrt);
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
      {
        enKeyboard = KBD_INPUT1;
        ShowLo(szMask);
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(7,8);
    }
    else Beep(); 
  }
  else Beep();
}
