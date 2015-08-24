/*------------------------------------------------------------------------------
KEY_GPS_SCHEDULE.С

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../time/gps.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "Коррекция GPS   ";
                     


static void Show(uchar  ibHhr)
{
  Clear();
  sprintf(szLo+1,"%02bu:%02bu",ibHhr/2,(ibHhr%2)*30);

  if (mpboGPSRun[ibHhr] == boFalse)
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';

  sprintf(szLo+14,"%2bu",ibHhr+1);
}



void    key_SetGpsSchedule(void)
{
static uchar ibHhr;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szMessage);

      Hour();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibHhr = 0;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibHhr = GetChar(10,11) - 1) < 48)
      {
        enKeyboard = KBD_POSTENTER;
        Show();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibHhr >= 48) ibHhr = 0;
      Show();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      mpboGPSRun[ibHhr] = ~mpboGPSRun[ibHhr];
      Show();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      (ibHhr > 0) ? (ibHhr--) : (ibHhr = 48-1);
      Show();
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
