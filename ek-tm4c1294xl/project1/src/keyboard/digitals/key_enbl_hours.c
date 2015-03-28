/*------------------------------------------------------------------------------
KEY_ENBL_HOURS.С

 Задание и просмотр графика опроса
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../digitals/digitals.h"
#include        "../../digitals/digitals_display.h"
#include        "../../digitals/profile/profile_core.h"
#include        "../../digitals/enbl_hours.h"
#include        "../../serial/speeds_display.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szGraphic[]     = " График опроса  ",
                        szByHours[]     = "  по получасам  ";
                     
static char const       *pszEnblHours[] = { szGraphic, szByHours, "" };


static void ShowHours(void)
{
  Clear();
  sprintf(szLo+1,"%02u:%02u", ibY/2, (ibY%2)*30);

  if (GetEnblPrtHou(ibX,ibY) == FALSE)
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';

  sprintf(szLo+14,"%2u",ibY+1);
}



void    key_SetEnblHours(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      LoadSlide(pszEnblHours);

      Port();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      ibX = 0;
      if (StreamPort(ibX) == 1)
      {
        ShowPort(ibX);

        enKeyboard = KBD_INPUT2;
        Hour();
      }
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bPORTS)
      {
        if (StreamPort(ibX) == 1)
        {
          ShowPort(ibX);

          enKeyboard = KBD_INPUT2;
          Hour();
        }        
      } else Beep(); 
    }
    else if (enKeyboard == KBD_INPUT2)
    {
      enKeyboard = KBD_POSTENTER;

      ibY = 0;
      ShowHours();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibY = GetCharLo(10,11) - 1) < 48)
      {
        enKeyboard = KBD_POSTENTER;
        ShowHours();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibY >= 48) 
        ibY = 0;

      ShowHours();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      boolean bo = (GetEnblPrtHou(ibX,ibY) == TRUE ? FALSE : TRUE);
      SetEnblPrtHou(ibX,ibY,bo);

      SaveFile(&flEnblPrtHou);

      ShowHours();
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
    else
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(10,11);
    }
    else Beep(); 
  }
  else Beep();
}
