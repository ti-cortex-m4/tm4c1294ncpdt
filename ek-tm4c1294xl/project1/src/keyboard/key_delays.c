/*------------------------------------------------------------------------------
_DELAYS.C

 
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../keyboard.h"
#include        "../display.h"
#include        "../delay.h"
#include        "../beep.h"
#include        "../engine.h"
#include        "../sensors.h"



//                                          0123456789ABCDEF
static char const       szDelays[]       = "Таймауты        ",
                        szMajorDelays[]  = "  расширенные   ",
                        szMinorDelays[]  = "    базовые     ",
                        szMaskDelays[]   = "   ______ мс  ";
                      


void    ShowDelaysName(void)
{
  ShowHi(szDelays);
  switch (bProgram)
  {
    case bSET_MAJORDELAYS:  ShowLo(szMajorDelays);  break;
    case bSET_MINORDELAYS:  ShowLo(szMinorDelays);  break;
  }

  DelayInf();
}


void    ShowDelays(void)
{
  Clear();
  switch (bProgram)
  {
    case bSET_MAJORDELAYS:  dwBuffC = GetMajDelay(ibX);  break;
    case bSET_MINORDELAYS:  dwBuffC = GetMinDelay(ibX);  break;
  }

  ShowLong(&dwBuffC);
  sprintf(szLo+10,"мс  %2u",ibX+1);
}


void    SetDelays(void)
{
  wBuffD = (ulong)dwBuffC*wFREQUENCY_T0/1000;

  switch (bProgram)
  {
    case bSET_MAJORDELAYS:  mpwMajInDelay[ibX] = wBuffD;  break;
    case bSET_MINORDELAYS:  mpwMinInDelay[ibX] = wBuffD;  break;
  }
}



void    key_SetDelays(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      ShowDelaysName();

      ibX = 0;
      ShowDelays();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {            
      dwBuffC = GetLong(3,8);

      if (( (ulong)wFREQUENCY_T0*dwBuffC/1000 ) <= 0xFFFF)
      {
        enKeyboard = KBD_POSTENTER;
        SetDelays();

        if (++ibX >= bPORTS) ibX = 0;
        ShowDelays();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bPORTS) ibX = 0;
      ShowDelays();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
      {
        enKeyboard = KBD_INPUT1;
        ShowLo(szMaskDelays);
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(3,8);
    }
    else Beep(); 
  }
  else Beep();
}
