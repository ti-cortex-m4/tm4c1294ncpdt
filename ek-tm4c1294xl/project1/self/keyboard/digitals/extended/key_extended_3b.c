/*------------------------------------------------------------------------------
_EXTENDED_3B.H

 
------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "delay.h"
#include        "display.h"
#include        "programs.h"
#include        "extended_3.h"
#include        "keyboard.h"



//                                         0123456789ABCDEF
message         code    szEventsAllB    = "События счетчика",
                        szForDeviceB    = "  Меркурий-230  ";


void    ShowExtended3B(void)
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

  if (mpboEventB[ibX] == boFalse) 
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetExtended3B(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boExt3Flag == boTrue) 
      {
        enKeyboard = KBD_POSTENTER;

        ShowHi(szEventsAllB);
        ShowLo(szForDeviceB);
        DelayMsg();

        ibX = 0;
        ShowExtended3B();
      }
      else BlockProgram(bSET_EXT3_FLAG);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= 4) ibX = 0;
      ShowExtended3B();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {           
      mpboEventB[ibX] = ~mpboEventB[ibX];      
      ShowExtended3B();
    }
    else Beep();
  }
  else Beep();
}

*/
