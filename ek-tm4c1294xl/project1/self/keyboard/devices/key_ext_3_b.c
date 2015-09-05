/*------------------------------------------------------------------------------
KEY_EXT_3_B.H

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_extended_3.h"
#include "../../digitals/extended/extended_3_b.h"
#include "../../digitals/extended/extended_3.h"



//                                         0123456789ABCDEF
static char const       szEvents[]      = "События счетчика",
                        szDeviceB[]     = "  Меркурий-230  ";



static void Show(uchar  i)
{
  Clear();
  switch (i)
  {
    case 0: ShowEventsB(1); break;
    case 1: ShowEventsB(3); break;
    case 2: ShowEventsB(4); break;
    case 3: ShowEventsB(5); break;
    default: Error(); break;
  }

  if (mpfEventFlagB[i] == false)
    strcpy(szLo+1,szNo);
  else         
    strcpy(szLo+1,szYes);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}



void    key_SetExt3B(void)
{
static uchar i;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (fExt3Flag == true) 
      {
        enKeyboard = KBD_POSTENTER;

        ShowHi(szEvents);
        ShowLo(szDeviceB);
        DelayMsg();

        i = 0;
        Show(i);
      }
      else BlockProgram(bSET_EXT3_FLAG);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++i >= 4) i = 0;
      Show(i);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {           
      mpfEventFlagB[i] = InvertBoolean(mpfEventFlagB[i]);
      SaveCache(&chEventFlagB);

      Show(i);
    }
    else Beep();
  }
  else Beep();
}
