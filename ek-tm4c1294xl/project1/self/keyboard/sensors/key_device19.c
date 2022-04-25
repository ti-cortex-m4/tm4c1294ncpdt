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



void    ShowDevicesInt(void)
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
      (ReadSensorN() == 1) ? ShowLong(PGetCanLong(mpdwChannelsA,0)) : Error();   
  }

  sprintf(szLo+14,"%2bu",c+1);
}


void    key_GetDevicesInt(void)
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
      ShowDevicesInt();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((c = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowDevicesInt();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++c >= bCANALS) c = 0;
      ShowDevicesInt();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (c > 0) c--; else c = bCANALS-1;
      ShowDevicesInt();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      ShowDevicesInt();
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



void    ShowDevicesReal(void)
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
      (ReadSensorN() == 1) ? ShowReal(&reBuffA) : Error();   
  }

  sprintf(szLo+14,"%2bu",c+1);
}


void    key_GetDevicesReal(void)
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
      ShowDevicesReal();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((c = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowDevicesReal();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++c >= bCANALS) c = 0;
      ShowDevicesReal();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (c > 0) c--; else c = bCANALS-1;
      ShowDevicesReal();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      ShowDevicesReal();
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

