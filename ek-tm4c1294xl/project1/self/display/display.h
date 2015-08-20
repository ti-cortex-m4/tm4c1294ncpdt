/*------------------------------------------------------------------------------
DISPLAY.H


------------------------------------------------------------------------------*/

#include        <string.h>
#include        <stdio.h>
#include        <stdlib.h>
#include "../main.h"
#include "lines.h"
#include "slides.h"
#include "messages.h"



extern  char                    szHi[bDISPLAY + bMARGIN],
                                szLo[bDISPLAY + bMARGIN];

extern  char                    szAlfa[bDISPLAY + bMARGIN],
                                szBeta[bDISPLAY + bMARGIN];



void    ShowHi(char const  *szT);
void    ShowLo(char const  *szT);

void    ShowHiDirect(char const  *szT);
void    ShowLoDirect(char const  *szT);

void    InitDisplay(void);

void    ShowChar(uchar  bT);
void    ShowInt(uint  wT);
void    ShowLong(ulong  dwT);
void    ShowFloat(float  fl);
void    ShowDouble(double  db);

void    ShowBool(bool  bo);
void    ShowAnswer(void);
void    ShowPercent(uchar  bT);
void    ShowProgress(uchar  ibPos, uchar  bT);

void    SaveDisplay(void);
void    LoadDisplay(void);
