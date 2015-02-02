/*------------------------------------------------------------------------------
KEY_RELAXS_TARIFF.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../display.h"
#include        "../../slide.h"
#include        "../../keyboard.h"
#include        "../../tariffs/tariffs.h"
#include        "../../tariffs/zones.h"



//                                         0123456789ABCDEF
static char const       szTariffsFor[]  = "   Тариф для    ",
                        szHoliday[]     = " выходных дней  ",
                        szCelebration[] = "  и праздников  ",
                        szMaskRelaxs2[] = "      ___       ";

static char const      *pszRelaxs2[] = { szTariffsFor, szHoliday, szCelebration, "" };



void    key_SetRelaxsTariff(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boRelaxsFlag == true)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        LoadSlide(pszRelaxs2); 
        ShowChar(ibRelaxsTariff+1); 
      }
      else BlockProgram(bSET_RELAXS_FLAG);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetChar(6,8);
      if ((ibX > 0) && (ibX <= bTARIFFS))
      {
        ibRelaxsTariff = ibX-1;
        ShowChar(ibRelaxsTariff+1); 
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskRelaxs2);        
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskRelaxs2);        
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}

