/*------------------------------------------------------------------------------
LCD.H


------------------------------------------------------------------------------*/

#include 		"../main.h"

#define NATIVE_LCD

void    ShowMsgLCD2(uchar  bT, char  *szT);

void    InitLCD(void);
void    LCD_Timer0();

void    TestOK(void);
void    TestError(const uchar  *szT);

