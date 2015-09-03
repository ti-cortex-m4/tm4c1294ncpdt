/*------------------------------------------------------------------------------
KEY_HEALTH,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../flash/flash.h"
#include "../nvram/23x1024.h"



//                                         0123456789ABCDEF
static char const       szHealth[]      = "Состояние       ",
                        szFlash1[]      = "FLASH1:         ",
                        szFlash2[]      = "FLASH2:         ",
                        szNvram[]       = "NVRAM:          ",
                        szOK[]          = "OK",
                        szError[]       = "ошибка";



static void Show(uchar  i)
{
  switch (i)
  {
    case 0: 
      ShowLo(szFlash1);
      GetFlashStatus1() == 0 ? strcpy(szLo+8, szOK) : strcpy(szLo+8, szError);
      break;

    case 1: 
      ShowLo(szFlash2);
      GetFlashStatus2() == 0 ? strcpy(szLo+8, szOK) : strcpy(szLo+8, szError);
      break;

    case 2: 
      ShowLo(szNvram);
      GetNvramStatus() == 0 ? strcpy(szLo+7, szOK) : strcpy(szLo+7, szError);
      break;
  }
}



void    key_GetHealth(void)
{
static uchar i;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      ShowHi(szHealth);

      i = 0;
      Show(i);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++i > 2) i = 0;
      Show(i);
    }
    else Beep();
  }
  else Beep();
}
