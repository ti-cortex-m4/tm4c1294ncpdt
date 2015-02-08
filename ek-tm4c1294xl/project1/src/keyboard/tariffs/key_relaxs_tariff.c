/*------------------------------------------------------------------------------
KEY_RELAXS_TARIFF.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../display/display.h"
#include        "../../keyboard.h"
#include        "../../tariffs/tariffs.h"
#include        "../../tariffs/zones.h"
#include        "../../tariffs/relaxs.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szTariffsFor[]  = "   Тариф для    ",
                        szHoliday[]     = " выходных дней  ",
                        szCelebration[] = "  и праздников  ",
                        szMaskRelaxs[]  = "      ___       ";

static char const      *pszRelaxs[]     = { szTariffsFor, szHoliday, szCelebration, "" };



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

        LoadSlide(pszRelaxs);
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

        SaveFile(&flRelaxsTariff);
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskRelaxs);
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskRelaxs);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}

