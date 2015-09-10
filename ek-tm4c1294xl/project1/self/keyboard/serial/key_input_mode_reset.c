/*------------------------------------------------------------------------------
KEY_INPUT_MODE_RESET.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_ports.h"
#include "../../serial/input_mode_reset.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = " Автоматическое ",
                        szMessage2[]    = "  переключение  ",
                        szMessage3[]    = "на прием ведомых",
                        szMessage4[]    = "   портов 3,4   ";
                        
static char const      *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    ShowInputModeReset(void)
{
  Clear();
  switch (bInputModeReset)
  {
    case 0:  strcpy(szLo+1,"нет");      break;
    case 1:  strcpy(szLo+1,"30 минут"); break;
    case 6:  strcpy(szLo+1,"3 часа");   break;
    case 12: strcpy(szLo+1,"6 часов");  break;
    case 24: strcpy(szLo+1,"12 часов"); break;
    case 48: strcpy(szLo+1,"24 часа");  break;
    default: strcpy(szLo+1,"?");        break;
  }

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetInputModeReset(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_POSTENTER;
      Clear();
      
      LoadSlide(pszMessages);
      ShowInputModeReset();  
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if (enKeyboard == KBD_POSTENTER)
      {           
        switch (bInputModeReset)
        {
          case 0:  bInputModeReset = 1;  break;
          case 1:  bInputModeReset = 6;  break;
          case 6:  bInputModeReset = 12; break;
          case 12: bInputModeReset = 24; break;
          case 24: bInputModeReset = 48; break;
          case 48: bInputModeReset = 0;  break;
          default: bInputModeReset = 0;  break;
        }
        
        SaveCache(&chInputModeReset);

        ShowInputModeReset();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
