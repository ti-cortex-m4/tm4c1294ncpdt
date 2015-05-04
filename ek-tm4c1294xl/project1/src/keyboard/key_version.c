/*------------------------------------------------------------------------------
KEY_VERSION,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../hardware/memory.h"



//                                         0123456789ABCDEF
static char const       szVersion[]     = "Версия          ",
                        szParameters[]  = "Параметры       ",
                        szBuild[]       = "Сборка          ",
                        szDevices[]     = "Счетчики        ";



static void Show(void)
{
  switch (ibX)
  {
    case 0: 
      ShowHi(szVersion);
      Clear();
      sprintf(szLo+0,"%02u.%02u.%u.%04X",
              bMAXVERSION, bMINVERSION, GetBuildNumber(), GetRomChecksum());
      break;

    case 1: 
      ShowHi(szParameters);
      Clear();
      sprintf(szLo+0,"%02u.%02u.%03u.%lu",
              bCANALS, bGROUPS, (uchar)(wHOURS/48), GetFileSize());
      break;

    case 2: 
      ShowHi(szBuild);
      sprintf(szHi+12,"%4u",GetBuildNumber());
      Clear();
      sprintf(szLo+1,"%02u:%02u %02u.%02u.%02u",
                     GetBuildDate_Hour(),
                     GetBuildDate_Minute(),
                     GetBuildDate_Day(),   
                     GetBuildDate_Month(),
                     GetBuildDate_Year());
      break;

    case 3: 
      ShowHi(szDevices);
      Clear();
      sprintf(szLo+3,"типов: %u", bDEVICES);
      break;
  }
}



void    key_GetVersion(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      Show();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= 4) ibX = 0;
      Show();
    }
    else Beep();
  }
  else Beep();
}
