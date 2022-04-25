/*------------------------------------------------------------------------------
KEY_DEVICE19.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../sensors/sensor19/automatic19.h"



//                                         0123456789ABCDEF
static char const       szDevicesInt[]  = "»мпульсы спец.  ",
                        szDevicesReal[] = "—четчики спец.  ",
                        szNoDevices[]   = "      нет       ";



static void ShowLong(void)
{
  if (GetDigitalDevice(c) != 19)
    ShowLo(szNoDevices); 
  else
  {
    ibDig = c;

    LoadCurrDigital(c);
    ibPort = diCurr.ibPort;

    if (mpboEnblCan[c] == boFalse)
      ShowLo(szBlocking); 
    else 
    {
      long2 dw2 = ReadSensorN();
      (dw2.fValid) ? ShowLong(dw2.dbValue) : Error();
    }
  }

  sprintf(szLo+14,"%2bu",c+1);
}


void    key_GetDevice19Long(void)
{
static uchar c;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Canal();

      ShowHi(szDevicesInt);
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      c = 0;
      ShowLong();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((c = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowLong();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++c >= bCANALS) c = 0;
      ShowLong();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (c > 0) c--; else c = bCANALS-1;
      ShowLong();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      ShowLong();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}



static void ShowDouble(void)
{
  if (GetDigitalDevice(c) != 19)
    ShowLo(szNoDevices); 
  else
  {
    ibDig = c;

    LoadCurrDigital(c);
    ibPort = diCurr.ibPort;

    if (mpboEnblCan[c] == boFalse)
      ShowLo(szBlocking); 
    else 
    {
      long2 dw2 = ReadSensorN();
      (dw2.fValid) ? ShowDouble((dw2.dwValue * mpdbValueCntHou[c]) + mpdbCount[c]) : Error();
    }
  }

  sprintf(szLo+14,"%2bu",c+1);
}


void    key_GetDevice19Double(void)
{
static uchar c;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Canal();

      ShowHi(szDevicesReal);
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      c = 0;
      ShowDouble();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((c = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowDouble();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++c >= bCANALS) c = 0;
      ShowDouble();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (c > 0) c--; else c = bCANALS-1;
      ShowDouble();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      ShowDouble();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}

