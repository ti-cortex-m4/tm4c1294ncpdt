/*------------------------------------------------------------------------------
_PHONES22.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "display.h"
#include        "keyboard.h"
#include        "programs.h"
#include        "phones2.h"



//                                         0123456789ABCDEF
message         code    szUse22         = "    Телефоны    ",
                code    szUsePhones22   = "для СМС-контроля",
                code    szMaskPhones22  = "_____________";


uchar           *code   pszPhones22[]   = { szUse22, szUsePhones22, "" };


void    ShowPhones2(void)
{
  Clear();
  strcpy(szLo, mpphPhones2[ibX].szNumber);

  sprintf(szLo+14,"%2bu",ibX+1);
}



void    ShowMaskPhones2(void)
{
  enKeyboard = KBD_INPUT2;
  ShowLo(szMaskPhones22);

  ibY = 0;
}



void    key_SetPhones22(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (UsePhones2())
      {
        enKeyboard = KBD_INPUT1;
        Number();

        LoadSlide(pszPhones22);
      }
      else BlockProgram(bSET_PHONES20);
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowPhones2();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetChar(10,11) - 1) < bPHONES2)
      {
        enKeyboard = KBD_POSTENTER;
        ShowPhones2();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bPHONES2)
        ibX = 0;

      ShowPhones2();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if (ibY > 0)
      {
        enKeyboard = KBD_POSTENTER;

        szLo[ibY] = 0;
        strcpy(&mpphPhones2[ibX].szNumber,szLo);
      }

      if (enKeyboard == KBD_POSTENTER)
      {
        if (++ibX >= bPHONES2)
          ibX = 0;

        ShowPhones2();
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if ((enKeyboard == KBD_POSTENTER) || (enKeyboard == KBD_POSTINPUT2))
    {
      if (enGlobal != GLB_WORK)
        ShowMaskPhones2();
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTINPUT2)
    {
      if (ibY == 1)
        szLo[ibY++] = 'W';
      else Beep();
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
        ShowMaskPhones2();
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;

      if (ibY < bPHONENUMBER)
        szLo[ibY++] = szDigits[bKey];
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
*/
