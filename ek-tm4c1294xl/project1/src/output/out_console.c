/*------------------------------------------------------------------------------
OUT_CONSOLE,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../access.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"



void    OutSetKey(void)
{
  if (TrueKey(bInBuff5) == true)
  {
    bKey = mpbKeys[bInBuff5];
    fKey = true;

    LongResult(bRES_OK);
  }
  else Result(bRES_BADDATA);
}



void    OutGetDisplay(void)
{
  InitPushCRC();

  Push(&szHi, bDISPLAY);
  Push(&szLo, bDISPLAY);

  Output(2*bDISPLAY);
}
