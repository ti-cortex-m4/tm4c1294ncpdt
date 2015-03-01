/*------------------------------------------------------------------------------
KEY_SEASON.C

 Установка и просмотр дат переходов на сезонное время
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../time/rtc.h"
#include        "../time/timedate.h"



//                                         0123456789ABCDEF
static char const       szMaskSeason[]  = "     __ __      ",
                        szWinter[]      = "Зимнее время    ",
                        szSummer[]      = "Летнее время    ";



void    ShowSummer(void)
{
  sprintf(szLo+5,"%02u.%02u",
                 tiSummer.bDay,   
                 tiSummer.bMonth);
}



void    ShowWinter(void)
{
  sprintf(szLo+5,"%02u.%02u",
                 tiWinter.bDay,   
                 tiWinter.bMonth);
}



void    key_SetSeason(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      switch (bProgram)
      {
        case bSET_SUMMER:  ShowHi(szSummer); 
                           ShowSummer();  break;
        case bSET_WINTER:  ShowHi(szWinter); 
                           ShowWinter();  break;
      }
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      tiKey.bDay = GetCharLo(5,6);

      if ((tiKey.bDay > 0) && (tiKey.bDay <= 31))
      {
        enKeyboard = KBD_INPUT2;
        szLo[7] = '.';
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      tiKey.bMonth = GetCharLo(8,9);
      tiKey.bYear  = GetCurrTimeDate()->bYear;

      if ((tiKey.bMonth >= 1) && (tiKey.bMonth <= 12))
      {
        if (tiKey.bDay <= GetDaysInMonthYM(tiKey.bYear, tiKey.bMonth))
        {
          enKeyboard = KBD_POSTENTER;

          switch (bProgram)
          {
            case bSET_SUMMER:  tiSummer = tiKey;
                               ShowSummer();  break;
            case bSET_WINTER:  tiWinter = tiKey;
                               ShowWinter();  break;
          }
        }
        else
        {  
          enKeyboard = KBD_INPUT1;
          LongBeep();

          ShowLo(szMaskSeason);
        }
      }
      else Beep();
    }
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
      {
        if (deDecret != DEC_CUSTOM)        
          NeedProgram(bSET_DECRET); 
        else  
        {
          enKeyboard = KBD_INPUT1;
          ShowLo(szMaskSeason);
        }
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(5,6);
    }
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(8,9);
    }
  }
  else Beep();
}
