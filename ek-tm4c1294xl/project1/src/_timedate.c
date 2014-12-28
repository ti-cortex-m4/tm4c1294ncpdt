/*------------------------------------------------------------------------------
_TIMEDATE.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory_program.h"
#include        "keyboard.h"
#include        "display.h"
#include        "slides.h"
#include        "delay.h"
#include        "beep.h"
#include        "rtc.h"
#include        "timedate.h"
#include        "decret.h"



//                                         0123456789ABCDEF
char const              szMaskTime[]    = "    __ __ __    ",
                        szMaskDate[]    = "    __ __ __    ",
                        szTime[]        = "Текущее время   ",
                        szDate[]        = "Текущая дата    ",
                        szStartDate[]   = "Дата запуска    ",
                        szStartTime[]   = "Время запуска   ";



// установка и просмотр текущего времени
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
      if ((tiKey.bSecond = GetChar(10,11)) < 60)
      {
        enKeyboard = KBD_POSTENTER;
        ibZ = 60;

        memcpy(&tiSetRTC, &tiKey, sizeof(time));
        SetCurrTime();

        boSetTime = boTrue;
      }
      else Beep();
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((tiKey.bHour = GetChar(4,5)) < 24)
      {
        enKeyboard = KBD_INPUT2;
        szLo[6] = ':';
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((tiKey.bMinute = GetChar(7,8)) < 60)
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



// установка и просмотр текущей даты
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
      tiKey.bYear = GetChar(10,11);
      memcpy(&tiAlt, &tiKey, sizeof(time));

      if ((tiKey.bYear <= 100) && (tiKey.bDay <= DaysInMonth()))
      {
        enKeyboard = KBD_POSTENTER;
        ibZ = 60;

        memcpy(&tiSetRTC, &tiKey, sizeof(time));
        SetCurrDate();

        boSetDate = boTrue;

        // рассчёт дат перехода на сезонное время
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
      tiKey.bDay = GetChar(4,5);

      if ((tiKey.bDay > 0) && (tiKey.bDay <= 31))
      {
        enKeyboard = KBD_INPUT2;
        szLo[6] = '.';
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      tiKey.bMonth = GetChar(7,8);

      if ((tiKey.bMonth > 0) && (tiKey.bMonth <= 12))
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



// обновление текущего времени раз в секунду
void   auto_GetCurrTime(void)
{
  if ((enKeyboard == KBD_POSTENTER) || (enKeyboard == KBD_SHOW))
  {
    ibY = (*PGetCurrTimeDate()).bSecond;
    if (ibY != ibZ)
    {
      ibZ = ibY;

      tiAlt = *PGetCurrTimeDate();
      ShowTime();
    }
  }
}



// обновление текущей даты раз в секунду
void   auto_GetCurrDate(void)
{
  if ((enKeyboard == KBD_POSTENTER) || (enKeyboard == KBD_SHOW))
  {
    ibY = (*PGetCurrTimeDate()).bSecond;
    if (ibY != ibZ)
    {
      ibZ = ibY;

      tiAlt = *PGetCurrTimeDate();
      ShowDate();
    }
  }
}



// включение просмотра текущего времени при бездействии пользователя
void    ShowTimeNow(void)
{
  bProgram = bGET_CURRTIME;
  fSlide = 0; 

  enKeyboard = KBD_POSTENTER;
  ibZ = 60;

  ShowHi(szTime);     
  Clear();
}



// выключение просмотра текущего времени
void    NoShowTime(bool  fClear)
{
  cbShowTime = 0;
  fSlide = false;

  if (fClear == true)
  {
    enKeyboard = KBD_BEGIN;
    bProgram = 0;
    wProgram = 0;
  }
}
