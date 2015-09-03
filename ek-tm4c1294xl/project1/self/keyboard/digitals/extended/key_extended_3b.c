/*------------------------------------------------------------------------------
KEY_EXTENDED_3B.H

 
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../memory/mem_extended_3.h"
#include "../../../digitals/extended/extended_3_b.h"



//                                         0123456789ABCDEF
static char const       szEventsAllB[]  = "События счетчика",
                        szForDeviceB[]  = "  Меркурий-230  ";



static void Show(uchar ibX)
{
  Clear();
  switch (ibX) 
  {
    case 0: ShowEventsB(1); break;
    case 1: ShowEventsB(3); break;
    case 2: ShowEventsB(4); break;
    case 3: ShowEventsB(5); break;
    default: Error(); break;
  }

  if (mpboEventB[ibX] == false) 
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetExtended3B(void)
{
static uchar ibX;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boExt3Flag == true) 
      {
        enKeyboard = KBD_POSTENTER;

        ShowHi(szEventsAllB);
        ShowLo(szForDeviceB);
        DelayMsg();

        ibX = 0;
        Show(ibX);
      }
      else BlockProgram(bSET_EXT3_FLAG);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= 4) ibX = 0;
      Show(ibX);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {           
      mpboEventB[ibX] = ~mpboEventB[ibX];      
      Show(ibX);
    }
    else Beep();
  }
  else Beep();
}
