/*------------------------------------------------------------------------------
_EXTENDED_3A.H

 
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
message         code    szEventsAllA    = "События счетчика",
                        szForDeviceA    = "   СЭТ-4ТМ.02   ";


void    ShowExtended3A(void)
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

  if (mpboEventA[ibX] == boFalse) 
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetExtended3A(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boExt3Flag == boTrue) 
      {
        enKeyboard = KBD_POSTENTER;

        ShowHi(szEventsAllA);
        ShowLo(szForDeviceA);
        DelayMsg();

        ibX = 0;
        ShowExtended3A();
      }
      else BlockProgram(bSET_EXT3_FLAG);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= 4) ibX = 0;
      ShowExtended3A();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {           
      mpboEventA[ibX] = ~mpboEventA[ibX];      
      ShowExtended3A();
    }
    else Beep();
  }
  else Beep();
}

*/
