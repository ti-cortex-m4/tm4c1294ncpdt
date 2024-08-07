/*------------------------------------------------------------------------------
KEY_PARAMS_DIV,C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../digitals/params/params.h"
#include "../../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = " �����. ������� ",
                        szMessage2[]    = " ��� ���������� ",
                        szMask[]        = "________ ___";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



static void  Show(uint  iwPrm)
{
  Clear();
  sprintf(szLo,"%12.3f", mpreParamsDiv[iwPrm]);
  sprintf(szLo+13,"%3u",iwPrm+1);
}


void    key_SetParamsDiv(void)
{
static uint iwPrm;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Param();

      LoadSlide(pszMessages);
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      iwPrm = 0;
      Show(iwPrm);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((iwPrm = GetIntLo(10,12) - 1) < wPARAMS)
      {
        enKeyboard = KBD_POSTENTER;
        Show(iwPrm);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++iwPrm >= wPARAMS) iwPrm = 0;

      Show(iwPrm);
    }
    else if ((enKeyboard == KBD_POSTINPUT2) || (enKeyboard == KBD_POSTINPUT3))
    {
      float fl = (float)GetIntLo(0,7) + (float)GetIntLo(9,11)/1000;
      if (fl >= 0)
      {
        enKeyboard = KBD_POSTENTER;

        mpreParamsDiv[iwPrm] = fl;
        SaveCache(&flParamsDiv);
      }
      else Beep();

      if (enKeyboard == KBD_POSTENTER)
      {
        if (++iwPrm >= wPARAMS) iwPrm = 0;

        Show(iwPrm);
      }
      else
      {
        enKeyboard = KBD_INPUT2;
        LongBeep();

        ShowLo(szMask);
      }
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (iwPrm > 0) iwPrm--; else iwPrm = wPARAMS-1;

      Show(iwPrm);
    }
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT3;
      szLo[8] = '.';
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT2;
      ShowLo(szMask);
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
      ShiftLo(0,7);
    }
    else
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(9,11);
    }
  }
  else Beep();
}

