/*------------------------------------------------------------------------------
LCD!H


------------------------------------------------------------------------------*/

#include 		"../main.h"

#ifndef NO_DISPLAY
void    ShowMsgLCD(uchar  bT, const uchar  *szT);
void    ShowMsgLCD2(uchar  bT, char  *szT);
#endif

void    InitLCD(void);

#ifndef NO_DISPLAY
void    LCD_Timer0();
#endif

void    TestOK(void);
void    TestError(const char  *szT);

