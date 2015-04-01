/*------------------------------------------------------------------------------
DISPLAY.C


------------------------------------------------------------------------------*/

#include        <string.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        "../main.h"
#include        "../memory/mem_program.h"
#include        "../keyboard/keyboard.h"
#include        "../keyboard/key_reset.h"
#include        "../hardware/watchdog.h"
#include        "messages.h"
#include        "slides.h"
#include        "lcd.h"



char                    szHi[bDISPLAY + bMARGIN],
                        szLo[bDISPLAY + bMARGIN];

char                    szHiSave[bDISPLAY + bMARGIN],
                        szLoSave[bDISPLAY + bMARGIN];

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



void    ShowHiDirect(char const  *szT)
{
  ShowMsgLCD(0x80, (const uchar *)szT);
}


void    ShowLoDirect(char const  *szT)
{
  ShowMsgLCD(0xC0, (const uchar *)szT);
}


void    InitDisplay(void)
{
  Delay(1000);
  Clear();

  if (enGlobal == GLB_WORK)
    ShowHi(szWork);
  else 
  {
    ShowHi(szSetting);
    Delay(1000);

    if (boFirstReset == TRUE)
    {
      enKeyboard = KBD_ENTER;
      bKey = bKEY_ENTER;

      wProgram = bSET_RESETFULL;
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


void    ShowFloat(float  fl)
{
  sprintf(szLo, "%13.3f", fl);
}


void    ShowDouble(double  db)
{
  sprintf(szLo, "%13.3f", db);
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


void    ShowProgress(uchar  ibPos, uchar  bT)
{
  if (ibPos < 16)
    sprintf(szHi+ibPos,"%3u%c",bT,'%');
  else
    sprintf(szLo+(ibPos-16),"%3u%c",bT,'%');
}



void    SaveDisplay(void)
{
  memcpy(szHiSave, szHi, bDISPLAY);
  memcpy(szLoSave, szLo, bDISPLAY);

  fSlideSave = fSlide;
  fSlide = 0;
}


void    LoadDisplay(void)
{
  memcpy(szHi, szHiSave, bDISPLAY);
  memcpy(szLo, szLoSave, bDISPLAY);

  fSlide = fSlideSave;
}

