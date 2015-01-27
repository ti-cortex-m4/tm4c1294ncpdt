/*------------------------------------------------------------------------------
KEY_TIMEDATE.C

 Установка и просмотр текущего времени и даты
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_program.h"
#include        "../keyboard.h"
#include        "../display.h"
#include        "../slide.h"
#include        "../delay.h"
#include        "../beep.h"
#include        "../rtc.h"
#include        "../timedate.h"
#include        "../decret.h"



//                                         0123456789ABCDEF
char const              szMaskTime[]    = "    __ __ __    ",
                        szMaskDate[]    = "    __ __ __    ",
                        szTime[]        = "Текущее время   ",
                        szDate[]        = "Текущая дата    ";



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
