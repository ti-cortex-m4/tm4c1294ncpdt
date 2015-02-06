/*------------------------------------------------------------------------------
KEY_OLD_TARIFFS_MODE.С

 Задание и просмотр правила обработки тарифов в нерабочие дни (старый вариант)
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../memory/mem_program.h"
#include        "../../keyboard.h"
#include        "../../display/display.h"
#include        "../../access.h"
#include        "../../tariffs/zones.h"
#include        "../../tariffs/tariffs.h"
#include        "../../tariffs/oldtariffs.h"
#include        "../../tariffs/relaxs.h"



//                                         0123456789ABCDEF
static char const       szWorkMode[]    = "  Режим работы  ",
                        szHolidays[]    = " по праздникам  ",   
                        szMaskOldMode[] = "      ___       ";

static char const      *pszOldMode[]    = { szWorkMode, szHolidays, "" };



void    key_SetOldTariffsMode(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      LoadSlide(pszOldMode);
      Clear();
      ShowChar(bOldTariffsMode);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      if ((ibX = GetChar(6,8)) <= bOLDTARIFFSMODES)
      {
      	bOldTariffsMode = ibX;
        ShowChar(bOldTariffsMode);
        MakeOldTariffsMode();

        if (bOldTariffsMode == 0)
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
