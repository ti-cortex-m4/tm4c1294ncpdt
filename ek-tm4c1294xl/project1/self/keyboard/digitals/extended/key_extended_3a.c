/*------------------------------------------------------------------------------
KEY_EXTENDED_3A.H

 
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../memory/mem_extended_3.h"
#include "../../../digitals/extended/extended_3_a.h"



//                                         0123456789ABCDEF
static char const       szEventsAllA[]  = "События счетчика",
                        szForDeviceA[]  = "   СЭТ-4ТМ.02   ";



static void Show(uchar ibX)
{
  Clear();
  switch (ibX) 
  {
    case 0: ShowEventsA(1); break;
    case 1: ShowEventsA(7); break;
    case 2: ShowEventsA(8); break;
    case 3: ShowEventsA(9); break;
    default: Error(); break;
  }

  if (mpboEventA[ibX] == false) 
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetExtended3A(void)
{
static uchar ibX;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boExt3Flag == true) 
      {
        enKeyboard = KBD_POSTENTER;

        ShowHi(szEventsAllA);
        ShowLo(szForDeviceA);
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
      mpboEventA[ibX] = ~mpboEventA[ibX];      
      Show(ibX);
    }
    else Beep();
  }
  else Beep();
}
