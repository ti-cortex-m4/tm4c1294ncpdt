/*------------------------------------------------------------------------------
DISPLAY.C

 Доступ к буферу дисплея
------------------------------------------------------------------------------*/

#include        <string.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        "main.h"
//#include        "xdata.h"
//#include        "timer0.h"
#include        "label.h"
#include        "beep.h"
#include        "delay.h"
#include        "keyboard.h"
#include        "messages.h"
#include        "slide.h"
//#include        "record.h"
//#include        "at45d081.h"
//#include        "_yesno.h"


char                    szHi[bDISPLAY + bMARGIN],
                        szLo[bDISPLAY + bMARGIN];




// загрузка сообщения в буфер верхней строки
void    ShowHi(char  const  *szT)
{
  strcpy(szHi, szT);
}


// загрузка сообщения в буфер нижней строки
void    ShowLo(char  const  *szT)
{
  strcpy(szLo, szT);
}



// подпрограммы для вывода часто встречающихся сообщений


// инициализация слайдов



// инициализация буфера дисплея 
void    InitDisplay(void)
{
  DelayMsg();
  Clear();

  if (GetLabelXDATA() == true)
    ShowHi(szWork);
  else 
    ShowHi(szSetting);
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







