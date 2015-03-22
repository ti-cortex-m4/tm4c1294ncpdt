/*------------------------------------------------------------------------------
OUT_DELAY.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../serial/ports.h"
#include        "../time/delay.h"



void    OutDelay1(void) {
  Delay(1000);
  LongResult(bRES_OK);
}


void    OutDelay10(void) {
  Delay(10000);
  LongResult(bRES_OK);
}
