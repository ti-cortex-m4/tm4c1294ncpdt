/*------------------------------------------------------------------------------
KEY_TRANSIT_HOURS.С

 
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../memory/mem_schedule.h"
#include "../../../digitals/digitals.h"
#include "../../../digitals/schedule/schedule.h"
#include "../../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szControl[]     = "График коррекции",
                        szPort3[]       = "порт 3 ",
                        szPort4[]       = "порт 4 ",
                        szPortNo[]      = "нет    ";


static void Show(void)
{
  Clear();
  sprintf(szLo+1,"%02u:%02u", ibX/2, (ibX%2)*30);

  if (mpibTransitHou[ibX] == 3-1)
    strcpy(szLo+5,szPort3);
  else if (mpibTransitHou[ibX] == 4-1)
    strcpy(szLo+5,szPort4);
  else         
    strcpy(szLo+5,szPortNo);

  if (enGlobal != GLB_WORK)
    szLo[4] = '.';

  sprintf(szLo+14,"%2u",ibX+1);
}



void    key_SetTransitHours(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szControl);

      HalfHour();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < 48)
      {
        enKeyboard = KBD_POSTENTER;
        Show();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= 48) 
        ibX = 0;

      Show();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      mpibTransitHou[ibX] = InvertBool(mpibTransitHou[ibX]);

      SaveCache(&chTransitHou);

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

