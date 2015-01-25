/*------------------------------------------------------------------------------
DISPLAY.H


------------------------------------------------------------------------------*/

#include        <string.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        "main.h"
#include        "lines.h"
#include        "messages.h"



extern  char                    szHi[bDISPLAY + bMARGIN],
                                szLo[bDISPLAY + bMARGIN];



void    ShowHi(char const  *szT);
void    ShowLo(char const  *szT);

void    InitDisplay(void);

void    ShowChar(uchar  bT);
void    ShowInt(uint  wT);
void    ShowLong(ulong  *pdwT);
void    ShowReal(real  *preT);

void    ShowBoolean(boolean  boT);
void    ShowAnswer(void);



