/*------------------------------------------------------------------------------
DISPLAY.C


------------------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../main.h"
#include "../memory/mem_program.h"
#include "../keyboard/keyboard.h"
#include "../keyboard/key_reset.h"
#include "../hardware/watchdog.h"
#include "../flash/records.h"
#include "messages.h"
#include "slides.h"
#include "lcd.h"



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
  Delay(500);

  if (IsResetWatchdog() == true)
  {
    ShowLo(szIsResetWDT);
    cwWrnResetWDT++;

    AddSysRecord(EVE_WATCHDOG);
  }
  else Clear();

  if (enGlobal == GLB_WORK)
    ShowHi(szWork);
  else 
  {
    ShowHi(szSetting);
    Delay(500);

    if (boFirstReset == true)
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
  sprintf(szLo, "%13.5f", db);
}


void    ShowBool(bool  bo)
{
  if (bo)
    strcpy(szLo+1,szYes);
  else
    strcpy(szLo+1,szNo);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    ShowAnswer(void)
{
  ShowBool(enKeyboard != KBD_INPUT1);
}


void    ShowPercent(uchar  bT)
{
  sprintf(szLo+5,"%3u%c",bT,'%'); ResetWatchdog();
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

