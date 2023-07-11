/*------------------------------------------------------------------------------
KEY_ENBL_CANALS,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_ports.h"
#include "../../digitals/digitals.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = " График опроса  ",
                        szMessage2[]    = "   по каналам   ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



static void Show(uchar  ibCan)
{
  Clear();
  sprintf(szLo+14,"%2u",ibCan+1);

  if (mpboEnblCan[ibCan] == false)
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetProfile2ModeCan(void)
{
static uchar ibCan;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      LoadSlide(pszMessages);

      Canal();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibCan = 0;
      Show(ibCan);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibCan = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Show(ibCan);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibCan >= bCANALS) ibCan = 0;

      Show(ibCan);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      mpboEnblCan[ibCan] = InvertBool(mpboEnblCan[ibCan]);

      SaveCache(&chEnblCan);

      Show(ibCan);
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
