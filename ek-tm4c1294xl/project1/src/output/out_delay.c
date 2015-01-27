/*------------------------------------------------------------------------------
OUT_DELAY.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../mem_ports.h"
#include        "../ports.h"
#include        "../delay.h"



void    OutSetDelay(void) {
uchar  i;

  if ((bInBuff5 > 0) && (bInBuff5 <= 10)) {

	for (i=0; i<bInBuff5; i++)
      Delay(1000);

	LongResult(bRES_OK);
  } else
    LongResult(bRES_BADDATA);
}
