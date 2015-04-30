/*------------------------------------------------------------------------------
KEY_TIMEDATE.C

 ”становка и просмотр текущего времени и даты
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_program.h"
#include        "../memory/mem_realtime.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../time/rtc.h"
#include        "../time/timedate.h"
#include        "../time/timedate_display.h"
#include        "../time/decret.h"



//                                         0123456789ABCDEF
static char const       szMaskTime[]    = "    __ __ __    ",
                        szMaskDate[]    = "    __ __ __    ",
                        szTime[]        = "“екущее врем€   ",
                        szDate[]        = "“екуща€ дата    ";



void    key_SetCurrTime(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      ibZ = 60;

      ShowHi(szTime);
      Clear();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if ((tiKey.bSecond = GetCharLo(10,11)) < 60)
      {
        enKeyboard = KBD_POSTENTER;
        ibZ = 60;

        SetCurrTime(tiKey);

        boSetTime = TRUE;
      }
      else Beep();
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((tiKey.bHour = GetCharLo(4,5)) < 24)
      {
        enKeyboard = KBD_INPUT2;
        szLo[6] = ':';
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((tiKey.bMinute = GetCharLo(7,8)) < 60)
      {
        enKeyboard = KBD_INPUT3;
        szLo[9] = ':';
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal == GLB_PROGRAM)
      {
        enKeyboard = KBD_INPUT1;
        ShowLo(szMaskTime);
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(4,5);
    }
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(7,8);
    }
    else if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}



void    key_SetCurrDate(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      ibZ = 60;

      ShowHi(szDate);
      Clear();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      tiKey.bYear = GetCharLo(10,11);

      if ((tiKey.bYear >= bMINYEAR) &&
          (tiKey.bYear <= bMAXYEAR) &&
          (tiKey.bDay <= GetDaysInMonthYM(tiKey.bYear, tiKey.bMonth)))
      {
        enKeyboard = KBD_POSTENTER;
        ibZ = 60;

        SetCurrDate(tiKey);

        boSetDate = TRUE;
        MakeDecret();
      }
      else
      {  
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskDate);
      }
    }
    else Beep();
  }   


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTINPUT1)
    {
      tiKey.bDay = GetCharLo(4,5);

      if ((tiKey.bDay > 0) && (tiKey.bDay <= 31))
      {
        enKeyboard = KBD_INPUT2;
        szLo[6] = '.';
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      tiKey.bMonth = GetCharLo(7,8);

      if ((tiKey.bMonth >= 1) && (tiKey.bMonth <= 12))
      {
        enKeyboard = KBD_INPUT3;
        szLo[9] = '.';
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal == GLB_PROGRAM)
      {
        enKeyboard = KBD_INPUT1;
        ShowLo(szMaskDate);
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(4,5);
    }
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(7,8);
    }
    else if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}



void   auto_GetCurrTime(void)
{
  if ((enKeyboard == KBD_POSTENTER) || (enKeyboard == KBD_SHOW))
  {
    ibY = GetCurrTimeDate()->bSecond;
    if (ibY != ibZ)
    {
      ibZ = ibY;
      ShowTime(*GetCurrTimeDate());
    }
  }
}



void   auto_GetCurrDate(void)
{
  if ((enKeyboard == KBD_POSTENTER) || (enKeyboard == KBD_SHOW))
  {
    ibY = GetCurrTimeDate()->bSecond;
    if (ibY != ibZ)
    {
      ibZ = ibY;
      ShowDate(*GetCurrTimeDate());
    }
  }
}



// включение просмотра текущего времени при бездействии пользовател€
void    ShowCurrentTime(void)
{
  wProgram = bGET_CURRTIME;
  fSlide = 0;

  enKeyboard = KBD_POSTENTER;
  ibZ = 60;

  ShowHi(szTime);
  Clear();
}


// выключение просмотра текущего времени
void    HideCurrentTime(bool  fClearProgram)
{
  cbShowCurrentTime = 0;
  fSlide = false;

  if (fClearProgram == true)
  {
    enKeyboard = KBD_BEGIN;
    wProgram = 0;
  }
}
