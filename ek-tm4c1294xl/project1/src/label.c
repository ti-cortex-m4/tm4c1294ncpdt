/*------------------------------------------------------------------------------
LABEL.C    
                    

------------------------------------------------------------------------------*/

#include        "main.h"



uchar                   mpbLabel[0x20];



void    SetLabelXDATA(void) {
uchar   i;

  for (i=0; i<sizeof(mpbLabel); i++)  
    mpbLabel[i] = i;
}



bool    GetLabelXDATA(void) {
uchar   i;

  for (i=0; i<sizeof(mpbLabel); i++) {
    if (mpbLabel[i] != i)
      return false;
  }

  return true;
}



void    BreakLabelXDATA(void) {
  mpbLabel[0] = 0xFF;
}











