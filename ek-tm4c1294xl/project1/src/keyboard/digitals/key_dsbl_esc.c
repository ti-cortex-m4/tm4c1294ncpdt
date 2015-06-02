/*------------------------------------------------------------------------------
KEY_DSBL_ESC,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../digitals/extended/extended_1.h"
#include "key_dsbl_esc.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "   Разрешение   ",
                        szMessage2[]    = " опроса базовых ",
                        szMessage3[]    = "  данных 1,2,3  ";
                        
static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



static void Show(void)
{
  Clear();

  (boDsblEscU == true) ? strcpy(szLo+1,szNo)  : strcpy(szLo+1,szYes);
  (boDsblEscV == true) ? strcpy(szLo+6,szNo)  : strcpy(szLo+6,szYes);
  (boDsblEscS == true) ? strcpy(szLo+11,szNo) : strcpy(szLo+11,szYes);
}


void    key_SetDsblEsc(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      LoadSlide(pszMessages); 
      Show();
    } 
    else Beep();
  }


  else if ((bKey == 1) && (enGlobal != GLB_WORK))
  {
    boDsblEscU = InvertBoolean(boDsblEscU);

    SaveFile(&flDsblEscU);
    Show();
  }
  else if ((bKey == 2) && (enGlobal != GLB_WORK))
  {
    boDsblEscV = InvertBoolean(boDsblEscV);
    SaveFile(&flDsblEscV);

    Show();
  }
  else if ((bKey == 3) && (enGlobal != GLB_WORK))
  {
    boDsblEscS = InvertBoolean(boDsblEscS);
    SaveFile(&flDsblEscS);

    Show();
  }
  else Beep();
}
