/*------------------------------------------------------------------------------
DISPLAY.C


------------------------------------------------------------------------------*/

#include        <string.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        "../main.h"
#include        "../memory/mem_program.h"
#include        "../keyboard.h"
#include        "../keyboard/key_reset.h"
#include        "../hardware/watchdog.h"
#include        "messages.h"
#include        "slides.h"



char                    szHi[bDISPLAY + bMARGIN],
                        szLo[bDISPLAY + bMARGIN];

char                    szAlfa[bDISPLAY + bMARGIN],
                        szBeta[bDISPLAY + bMARGIN];



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

    if (boReset == true)
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
  sprintf(szLo+4,"%5u",wT);
}


void    ShowLong(ulong  dwT)
{
  sprintf(szLo,"%9lu", dwT);
}


void    ShowReal(real  reT)
{
  sprintf(szLo,"%13.3f",  reT);
}


void    ShowBoolean(boolean  boT)
{
  if (boT == FALSE)
    strcpy(szLo+1,szNo);
  else         
    strcpy(szLo+1,szYes);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    ShowAnswer(void)
{
  ShowBoolean(enKeyboard != KBD_INPUT1 ? TRUE : FALSE);
}


void    ShowPercent(uchar  bT)
{
  sprintf(szLo+5,"%3u%c",bT,'%'); ResetWDT();
}




