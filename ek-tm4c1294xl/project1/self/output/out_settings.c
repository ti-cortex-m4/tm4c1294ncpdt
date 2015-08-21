/*------------------------------------------------------------------------------
 OUT_SETTINGS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../serial/ports.h"
#include "out_settings.h"



void    OutStart(void)
{
  InitPushCRC();
  Push(&tiStart, sizeof(time));
  Push(&tiPowerOff, sizeof(time));
  Push(&tiPowerOn,  sizeof(time));
  PushChar(cbPowerOn);
  Output(6+6+6+1);
}
