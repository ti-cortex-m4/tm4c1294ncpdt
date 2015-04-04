/*------------------------------------------------------------------------------
_PARAMS.C


------------------------------------------------------------------------------*/

#include        "../../../main.h"
#include        "../../../console.h"
#include        "../../../digitals/params/params.h"
#include        "../../../flash/files.h"



//                                          0123456789ABCDEF
static char const       szParams[]       = "Параметры       ",
                        szParPort[]      = "Порт...         ",
                        szParPhone[]     = "Телефон...      ",
                        szParDevice[]    = "Тип счетчика... ",
                        szParAddress[]   = "Адрес...        ",
                        szParLine[]      = "Вид параметра...",
                        szMaskParams[]   = "_ __ __ ___ __";


static uint             iwA;

static digital          diT;



void    key_SetParams(void)
{
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

      iwA = 0;
      ShowParam(iwA);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((iwA = GetIntLo(10,12) - 1) < wPARAMS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowParam(iwA);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++iwA >= wPARAMS) iwA = 0;

      ShowParam(iwA);
    }
    else if (enKeyboard == KBD_POSTINPUT6)
    {
      diT.ibLine = GetChar(12,13);
      if (TrueParamLine(diT.ibLine) == 1)
      {
        enKeyboard = KBD_POSTENTER;
        ShowHi(szParams);

        SetParam(iwA);
        MakeDividers(iwA);

        if (++iwA >= wPARAMS) iwA = 0;

        ShowParam(iwA);
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
        mpboEnblPar[iwA] = ~mpboEnblPar[iwA];      
        ShowParam(iwA);
      } 
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (iwA > 0) iwA--; else iwA = wPARAMS-1;

      ShowParam(iwA);
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((diT.ibPort = GetChar(0,0) - 1) < bPORTS)
      {
        if (StreamPortCan(diT.ibPort,iwA) == 1) 
        {
          enKeyboard = KBD_INPUT3;
          ShowHi(szParPhone);
          szLo[1] = '.';
        }
        else Beep();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if ((diT.ibPhone = GetChar(2,3)) < bCANALS)
      { 
        if (StreamPortPhoneCan(diT.ibPort,diT.ibPhone,iwA) == 1) 
        {
          enKeyboard = KBD_INPUT4;
          ShowHi(szParDevice);
          szLo[4] = '.';
        }
        else Beep();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      diT.bDevice = GetChar(5,6);
      if ((diT.bDevice <= bDEVICES) || (diT.bDevice == 99))
      {
        if (diT.bDevice == 0)
        {
          enKeyboard = KBD_POSTENTER;
          ShowHi(szParams);

          diT.bAddress = 0;
          diT.ibLine = 0;

          SetParam(iwA);

          ShowParam(iwA);
        }
        else
        {
          enKeyboard = KBD_INPUT5;
          ShowHi(szParAddress);
          szLo[7] = '.';
        }
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      if ((diT.bAddress = GetChar(8,10)) < 255)
      {
        if (((diT.bDevice == 9) || (diT.bDevice == 10)) && (diT.bAddress == 0))
          Beep();
        else
        {
          enKeyboard = KBD_INPUT6;
          ShowHi(szParLine);

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
        ShowHi(szParPort);
        ShowLo(szMaskParams);
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
