/*------------------------------------------------------------------------------
LABEL.C    
                    

------------------------------------------------------------------------------*/

#include        "main.h"



static uchar            mpbLabel[0x20];



void    SetLabel(void) {
uchar   i;

  for (i=0; i<sizeof(mpbLabel); i++)  
    mpbLabel[i] = i;
}



bool    GetLabel(void) {
uchar   i;

  for (i=0; i<sizeof(mpbLabel); i++) {
    if (mpbLabel[i] != i)
      return false;
  }

  return true;
}



void    BreakLabel(void) {
  mpbLabel[0] = 0xFF;
}
