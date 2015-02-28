/*------------------------------------------------------------------------------
KEY_TARIFFS_MODE.С

 Правила обработки тарифов в нерабочие дни (старый вариант)
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../memory/mem_program.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../access.h"
#include        "../../tariffs/zones.h"
#include        "../../tariffs/tariffs.h"
#include        "../../tariffs/oldtariffs.h"
#include        "../../tariffs/relaxs.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szWorkMode[]    = "  Режим работы  ",
                        szHolidays[]    = " по праздникам  ",   
                        szMaskOldMode[] = "      ___       ";

static char const      *pszTariffsMode[]= { szWorkMode, szHolidays, "" };



void    key_SetTariffsMode(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      LoadSlide(pszTariffsMode);
      Clear();
      ShowChar(bTariffsMode);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      if ((ibX = GetCharLo(6,8)) <= bTARIFFSMODES)
      {
      	bTariffsMode = ibX;
      	SaveFile(&flTariffsMode);
        ShowChar(bTariffsMode);

        MakeTariffsMode();

        if (bTariffsMode == 0)
          ResetRelaxs();
        else
          DefaultRelaxs();
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskOldMode);        
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskOldMode);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}
