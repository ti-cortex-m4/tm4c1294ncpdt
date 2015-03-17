/*------------------------------------------------------------------------------
KEY_ENBL_CANALS.С


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../../memory/mem_ports.h"
#include        "../../display/display.h"
#include        "../keyboard.h"
#include        "../../flash/files.h"
#include        "../../digitals/profile_core.h"



//                                         0123456789ABCDEF
static char const       szGraphic[]     = " График опроса  ",
                        szByCanals[]    = "   по каналам   ";
                     
static char const       *pszEnblCan[]   = { szGraphic, szByCanals, "" };



void    ShowEnblCanals(void)
{
  Clear();
  sprintf(szLo+14,"%2u",ibX+1);

  if (mpboEnblCan[ibX] == FALSE)
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetEnblCanals(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      LoadSlide(pszEnblCan);

      Canal();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowEnblCanals();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowEnblCanals();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;

      ShowEnblCanals();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      mpboEnblCan[ibX] = (mpboEnblCan[ibX] == TRUE ? FALSE : TRUE);
      ShowEnblCanals();
      SaveFile(&flEnblCan);
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
