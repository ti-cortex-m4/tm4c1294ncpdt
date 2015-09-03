/*------------------------------------------------------------------------------
KEY_EXT_3_A.H

 
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../memory/mem_extended_3.h"
#include "../../../digitals/extended/extended_3_a.h"



//                                         0123456789ABCDEF
static char const       szEvents[]      = "События счетчика",
                        szDeviceA[]     = "   СЭТ-4ТМ.02   ";



static void Show(uchar  i)
{
  Clear();
  switch (i)
  {
    case 0: ShowEventsA(1); break;
    case 1: ShowEventsA(7); break;
    case 2: ShowEventsA(8); break;
    case 3: ShowEventsA(9); break;
    default: Error(); break;
  }

  if (mpboEventA[i] == false)
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetExtended3A(void)
{
static uchar i;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boExt3Flag == true) 
      {
        enKeyboard = KBD_POSTENTER;

        ShowHi(szEvents);
        ShowLo(szDeviceA);
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
      mpboEventA[i] = InvertBoolean(mpboEventA[i]);
      Show(i);
    }
    else Beep();
  }
  else Beep();
}
