/*------------------------------------------------------------------------------
OUT_CONSOLE.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../mem_ports.h"
#include        "../queries.h"
#include        "../ports.h"
#include        "../access.h"
#include        "../display.h"
#include        "../keyboard.h"



void    OutSetKey(void)
{
  if (TrueKey(bInBuff5) == 1)
  {
    bKey = mpbKeys[bInBuff5];
    fKey = 1;

    LongResult(bRES_OK);
  }
  else Result(bRES_BADDATA);
}


void    OutGetDisplay(void)
{
  InitPushCRC();
  Push(&szHi,bDISPLAY);
  Push(&szLo,bDISPLAY);
  Output(2*bDISPLAY);
}
