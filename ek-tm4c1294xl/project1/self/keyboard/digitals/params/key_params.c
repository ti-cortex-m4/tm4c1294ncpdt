/*------------------------------------------------------------------------------
KEY_PARAMS,C

 Задание и просмотр мгновенных параметров
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../digitals/params/params.h"
#include "../../../digitals/params/params_div.h"
#include "../../../serial/speeds_display.h"
#include "../../../flash/files.h"



//                                          0123456789ABCDEF
static char const       szParams[]       = "Параметры       ",
                        szPort[]         = "Порт...         ",
                        szPhone[]        = "Телефон...      ",
                        szDevice[]       = "Тип счетчика... ",
                        szAddress[]      = "Адрес...        ",
                        szLine[]         = "Вид параметра...",
                        szMask[]         = "_ __ __ ___ __";



void    key_SetParams(void)
{
static digital di;
static uint iwPrm;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szParams);

      Param();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      iwPrm = 0;
      ShowParam(iwPrm);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((iwPrm = GetIntLo(10,12) - 1) < wPARAMS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowParam(iwPrm);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++iwPrm >= wPARAMS) iwPrm = 0;

      ShowParam(iwPrm);
    }
    else if (enKeyboard == KBD_POSTINPUT6)
    {
      di.ibLine = GetCharLo(12,13);
      if (ValidParamLine(di.ibLine) == true)
      {
        enKeyboard = KBD_POSTENTER;
        ShowHi(szParams);

        SetParam(iwPrm, &di);

        MakeParamDiv(iwPrm);
        SaveCache(&flParamsDiv);

        if (++iwPrm >= wPARAMS) iwPrm = 0;

        ShowParam(iwPrm);
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
      { 
        mpboEnblParams[iwPrm] = InvertBoolean(mpboEnblParams[iwPrm]);

        SaveCache(&flEnblParams);
        ShowParam(iwPrm);
      } 
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (iwPrm > 0) iwPrm--; else iwPrm = wPARAMS-1;

      ShowParam(iwPrm);
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((di.ibPort = GetCharLo(0,0) - 1) < bPORTS)
      {
        if (StreamPortCan(di.ibPort,iwPrm) == 1) 
        {
          enKeyboard = KBD_INPUT3;
          ShowHi(szPhone);
          szLo[1] = '.';
        }
        else Beep();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if ((di.ibPhone = GetCharLo(2,3)) < bCANALS)
      { 
        if (StreamPortPhoneCan(di.ibPort,di.ibPhone,iwPrm) == 1) 
        {
          enKeyboard = KBD_INPUT4;
          ShowHi(szDevice);
          szLo[4] = '.';
        }
        else Beep();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      di.bDevice = GetCharLo(5,6);
      if ((di.bDevice <= bDEVICES) || (di.bDevice == 99))
      {
        if (di.bDevice == 0)
        {
          enKeyboard = KBD_POSTENTER;
          ShowHi(szParams);

          di.bAddress = 0;
          di.ibLine = 0;

          SetParam(iwPrm, &di);

          ShowParam(iwPrm);
        }
        else
        {
          enKeyboard = KBD_INPUT5;
          ShowHi(szAddress);
          szLo[7] = '.';
        }
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      if ((di.bAddress = GetCharLo(8,10)) < 255)
      {
        if (((di.bDevice == 9) || (di.bDevice == 10)) && (di.bAddress == 0))
          Beep();
        else
        {
          enKeyboard = KBD_INPUT6;
          ShowHi(szLine);

          szLo[11] = '.';
        }
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
      {
        enKeyboard = KBD_INPUT2;
        ShowHi(szPort);
        ShowLo(szMask);
      }
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,12);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(0,0);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(2,3);
    }
    else 
    if ((enKeyboard == KBD_INPUT4) || (enKeyboard == KBD_POSTINPUT4))
    {
      enKeyboard = KBD_POSTINPUT4;
      ShiftLo(5,6);
    }
    else 
    if ((enKeyboard == KBD_INPUT5) || (enKeyboard == KBD_POSTINPUT5))
    {
      enKeyboard = KBD_POSTINPUT5;
      ShiftLo(8,10);
    }
    else 
    if ((enKeyboard == KBD_INPUT6) || (enKeyboard == KBD_POSTINPUT6))
    {
      enKeyboard = KBD_POSTINPUT6;
      ShiftLo(12,13);
    }
    else Beep(); 
  }
  else Beep();
}
