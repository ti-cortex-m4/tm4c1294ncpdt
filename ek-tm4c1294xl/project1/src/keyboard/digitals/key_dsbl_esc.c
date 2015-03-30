/*------------------------------------------------------------------------------
KEY_DSBL_ESC.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_extended_1.h"
#include        "../../devices/extended_1.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szDisableEsc1[] = "   Разрешение   ",
                        szDisableEsc2[] = " опроса базовых ",
                        szDisableEsc3[] = "  данных 1,2,3  ";
                        
static char const       *pszDisableEsc[] = { szDisableEsc1, szDisableEsc2, szDisableEsc3, "" };



void    ShowDsblEsc(void)
{
  Clear();

  (boDsblEscU == TRUE) ? strcpy(szLo+1,szNo)  : strcpy(szLo+1,szYes);
  (boDsblEscV == TRUE) ? strcpy(szLo+6,szNo)  : strcpy(szLo+6,szYes);
  (boDsblEscS == TRUE) ? strcpy(szLo+11,szNo) : strcpy(szLo+11,szYes);
}


void    key_SetDsblEsc(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      LoadSlide(pszDisableEsc); 
      ShowDsblEsc();
    } 
    else Beep();
  }


  else if ((bKey == 1) && (enGlobal != GLB_WORK))
  {
    boDsblEscU = InvertBoolean(boDsblEscU);

    SaveFile(&flDsblEscU);
    ShowDsblEsc();
  }
  else if ((bKey == 2) && (enGlobal != GLB_WORK))
  {
    boDsblEscV = InvertBoolean(boDsblEscV);
    SaveFile(&flDsblEscV);

    ShowDsblEsc();
  }
  else if ((bKey == 3) && (enGlobal != GLB_WORK))
  {
    boDsblEscS = InvertBoolean(boDsblEscS);
    SaveFile(&flDsblEscS);

    ShowDsblEsc();
  }
  else Beep();
}
