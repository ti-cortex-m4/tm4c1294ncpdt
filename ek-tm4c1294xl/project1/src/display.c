/*------------------------------------------------------------------------------
DISPLAY.C


------------------------------------------------------------------------------*/

#include        <string.h>
#include        "main.h"



char                    szHi[bDISPLAY + bMARGIN],
                        szLo[bDISPLAY + bMARGIN];



void    InitDisplay(void) {
  strcpy(szHi, "     ÑÝÌ+2      ");
  strcpy(szLo, "  [---------]   ");
}
