/*------------------------------------------------------------------------------
_DEVICE19.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "display.h"
#include        "keyboard.h"
#include        "programs.h"
#include        "energy.h"
#include        "engine.h"
#include        "ports.h"
#include        "sensors.h"
#include        "_automatic1.h"



//                                         0123456789ABCDEF
uchar           code    szDevicesInt[]  = "»мпульсы спец.  ",
                        szDevicesReal[] = "—четчики спец.  ",
                        szNoDevices[]   = "      нет       ";



void    ShowDevicesInt(void)
{
  if (GetDigitalDevice(ibX) != 19)
    ShowLo(szNoDevices); 
  else
  {
    ibDig = ibX;

    LoadCurrDigital(ibX);
    ibPort = diCurr.ibPort;

    if (mpboEnblCan[ibX] == boFalse)
      ShowLo(szBlocking); 
    else 
      (ReadSensorN() == 1) ? ShowLong(PGetCanLong(mpdwChannelsA,0)) : Error();   
  }

  sprintf(szLo+14,"%2bu",ibX+1);
}


void    key_GetDevicesInt(void)
{
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

      ibX = 0;
      ShowDevicesInt();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetChar(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowDevicesInt();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;
      ShowDevicesInt();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibX > 0) ibX--; else ibX = bCANALS-1;
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
  if (GetDigitalDevice(ibX) != 19)
    ShowLo(szNoDevices); 
  else
  {
    ibDig = ibX;

    LoadCurrDigital(ibX);
    ibPort = diCurr.ibPort;

    if (mpboEnblCan[ibX] == boFalse)
      ShowLo(szBlocking); 
    else 
      (ReadSensorN() == 1) ? ShowReal(&reBuffA) : Error();   
  }

  sprintf(szLo+14,"%2bu",ibX+1);
}


void    key_GetDevicesReal(void)
{
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

      ibX = 0;
      ShowDevicesReal();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetChar(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowDevicesReal();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;
      ShowDevicesReal();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibX > 0) ibX--; else ibX = bCANALS-1;
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

