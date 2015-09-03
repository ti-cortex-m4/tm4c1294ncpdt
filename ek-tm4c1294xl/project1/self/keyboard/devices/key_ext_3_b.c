/*------------------------------------------------------------------------------
KEY_EXT_3_B.H

 
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../memory/mem_extended_3.h"
#include "../../../digitals/extended/extended_3_b.h"



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

  if (mpboEventB[i] == false)
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetExtended3B(void)
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
      mpboEventB[i] = InvertBoolean(mpboEventB[i]);
      Show(i);
    }
    else Beep();
  }
  else Beep();
}
