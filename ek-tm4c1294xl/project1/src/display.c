/*------------------------------------------------------------------------------
DISPLAY.C


------------------------------------------------------------------------------*/

#include        <string.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        "main.h"
#include        "mem_program.h"
#include        "beep.h"
#include        "delay.h"
#include        "keyboard.h"
#include        "keyboard/key_reset.h"
#include        "messages.h"
#include        "slide.h"



char                    szHi[bDISPLAY + bMARGIN],
                        szLo[bDISPLAY + bMARGIN];




void    ShowHi(char const  *szT)
{
  strcpy(szHi, szT);
}


void    ShowLo(char const  *szT)
{
  strcpy(szLo, szT);
}



void    InitDisplay(void)
{
  DelayMsg();
  Clear();

  if (enGlobal == GLB_WORK)
    ShowHi(szWork);
  else 
  {
    ShowHi(szSetting);
    DelayMsg();

    if (boReset == boTrue)
    {
      enKeyboard = KBD_ENTER;
      bKey = bKEY_ENTER;

      bProgram = bSET_RESETFULL;
      key_SetReset();
    }
  }
}



void    ShowChar(uchar  bT)
{
  sprintf(szLo+6,"%3u",bT);
}


void    ShowInt(uint  wT)
{
  sprintf(szLo,"    %5u",wT);
}


void    ShowLong(ulong  *pdwT)
{
  sprintf(szLo,"%9lu", *pdwT);
}


void    ShowReal(real  *preT)
{
  sprintf(szLo,"%13.3f",  *preT);
}


void    ShowBoolean(boolean  boT)
{
  if (boT == boFalse) 
    strcpy(szLo+1,szNo);
  else         
    strcpy(szLo+1,szYes);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    ShowAnswer(void)
{
  ShowBoolean(enKeyboard != KBD_INPUT1 ? boTrue : boFalse);
}







