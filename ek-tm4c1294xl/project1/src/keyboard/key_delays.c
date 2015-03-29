/*------------------------------------------------------------------------------
KEY_DELAYS.C

 
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../engine.h"
#include        "../digitals/sensors.h"
#include        "../serial/speeds_storage.h"



//                                          0123456789ABCDEF
static char const       szDelays[]       = "Таймауты        ",
                        szMajorDelays[]  = "  расширенные   ",
                        szMinorDelays[]  = "    базовые     ",
                        szMaskDelays[]   = "   ______ мс  ";



static void ShowDelaysName(void)
{
  ShowHi(szDelays);
  switch (wProgram)
  {
    case bSET_MAJOR_DELAYS:  ShowLo(szMajorDelays);  break;
    case bSET_MINOR_DELAYS:  ShowLo(szMinorDelays);  break;
  }

  DelayInf();
}


static void ShowDelays(void)
{
ulong   dw;

  Clear();
  switch (wProgram)
  {
    case bSET_MAJOR_DELAYS:  dw = GetMajorDelay(ibX); SaveMajorInDelay();  break;
    case bSET_MINOR_DELAYS:  dw = GetMinorDelay(ibX); SaveMinorInDelay();  break;
  }

  ShowLong(dw);
  sprintf(szLo+10,"мс  %2u",ibX+1);
}


static void SetDelays(ulong  dw)
{
uint  w;

  w = (ulong)dw*wFREQUENCY_T0/1000;

  switch (wProgram)
  {
    case bSET_MAJOR_DELAYS:  mpwMajorInDelay[ibX] = w;  break;
    case bSET_MINOR_DELAYS:  mpwMinorInDelay[ibX] = w;  break;
  }
}



void    key_SetDelays(void)
{
ulong   dw;

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
      dw = GetLongLo(3,8);

      if (((ulong)wFREQUENCY_T0*dw/1000 ) <= 0xFFFF)
      {
        enKeyboard = KBD_POSTENTER;
        SetDelays(dw);

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
