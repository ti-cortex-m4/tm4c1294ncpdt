/*------------------------------------------------------------------------------
KEY_DEVICE19.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../console.h"
#include "../../sensors/sensor19/automatic19.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_messages.h"
#include "key_device19.h"



//                                         0123456789ABCDEF
static char const       szDevicesInt[]  = "Импульсы ПИ-1   ",
                        szDevicesReal[] = "Счетчики ПИ-1   ",
                        szNoDevices[]   = "      нет       ";



static void ShowDevice19Long(uchar c)
{
  if (GetDigitalDevice(c) != 19)
    ShowLo(szNoDevices); 
  else
  {
    ibDig = c;

    LoadCurrDigital(c);
    ibPort = diCurr.ibPort;

    if (mpboEnblCan[c] == false)
      ShowLo(szBlocked);
    else 
    {
      ulong2 dw2 = ReadSensorN();
      (dw2.fValid) ? ShowDevice19Long(dw2.dwValue) : Error();
    }
  }

  sprintf(szLo+14,"%2u",c+1);
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
      ShowDevice19Long(c);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((c = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowDevice19Long(c);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++c >= bCANALS) c = 0;
      ShowDevice19Long(c);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (c > 0) c--; else c = bCANALS-1;
      ShowDevice19Long(c);
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      ShowDevice19Long(c);
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



static void ShowDevice19Double(uchar c)
{
  if (GetDigitalDevice(c) != 19)
    ShowLo(szNoDevices); 
  else
  {
    ibDig = c;

    LoadCurrDigital(c);
    ibPort = diCurr.ibPort;

    if (mpboEnblCan[c] == false)
      ShowLo(szBlocked);
    else 
    {
      ulong2 dw2 = ReadSensorN();
      (dw2.fValid) ? ShowDevice19Double(c(dw2.dwValue * mpdbValueCntHou[c]) + mpdbCount[c]) : Error();
    }
  }

  sprintf(szLo+14,"%2u",c+1);
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
      ShowDevice19Double(c);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((c = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowDevice19Double(c);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++c >= bCANALS) c = 0;
      ShowDevice19Double(c);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (c > 0) c--; else c = bCANALS-1;
      ShowDevice19Double(c);
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      ShowDevice19Double(c);
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

